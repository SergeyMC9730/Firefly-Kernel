#include <x86_64/libk++/ios.h>
#include <x86_64/libk++/iostream.h>

#include <x86_64/int/interrupt.hpp>
#include <x86_64/drivers/serial_legacy.hpp>
#include <x86_64/settings.hpp>

#include <x86_64/drivers/ports.hpp>

#include <x86_64/applications/shell/main.hpp>
#include <x86_64/applications/application_manager.hpp>

#include <x86_64/kernel.hpp>

namespace firefly::kernel::core::interrupt {
struct __attribute__((packed)) idt_gate {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t rsv_0;
    uint8_t type;
    uint16_t offset_1;
    uint32_t offset_2;
    uint32_t rsv_1;
};

static_assert(16 == sizeof(idt_gate), "idt_gate size incorrect");

bool is_crashed = false;

__attribute__((interrupt)) void interrupt_wrapper([[maybe_unused]] iframe *iframe);
__attribute__((interrupt)) __attribute__((noreturn)) void exception_wrapper([[maybe_unused]] iframe *iframe);

static idt_gate idt[256];

namespace change {
void update(void (*handler)(iframe *), uint16_t cs, uint8_t type, uint8_t index) {
    idt[index].offset_0 = reinterpret_cast<size_t>(handler) & 0xffff;
    idt[index].selector = cs;
    idt[index].rsv_0 = 0;
    idt[index].type = type;
    idt[index].offset_1 = reinterpret_cast<size_t>(handler) >> 16 & 0xffff;
    idt[index].offset_2 = reinterpret_cast<size_t>(handler) >> 32 & 0xffffffff;
    idt[index].rsv_1 = 0;
}

//Hardcoded values as this is only meant for initialisation work by interrupt.cpp
//Use the non-static version of "update" to update the idt at a global level
static void initial_update(void (*handler)(iframe *), uint8_t index) {
    change::update(handler, 0x08, 0x8E, index);
}

}  // namespace change

struct __attribute__((packed)) idt_reg {
    /**
         *                  size of table in bytes - 1
         */
    uint16_t limit;
    /**
         *                  base address of idt
         */
    idt_gate *base;
} idtr = {
    .limit = (sizeof(struct idt_gate) * 256) - 1,
    .base = idt
};


void init() {
    int i = 0;
    for (; i <= 31; i++)
        change::initial_update(interrupt_wrapper, i);
    for (; i < 256; i++)
        change::initial_update(exception_wrapper, i);

    asm("lidt %0" ::"m"(idtr)
        : "memory");
}

void test_int() {
    asm volatile("int $0");
}
void keyboard_handle(){}
uint8_t current_key;

__attribute__((interrupt)) void interrupt_wrapper([[maybe_unused]] iframe *iframe) {
    printf("%d\n", firefly::applications::shell::is_ready);
    if(firefly::applications::shell::is_ready){
        if(firefly::kernel::settings::kernel_settings[5] == 1){
            firefly::kernel::io::legacy::writeTextSerial("\nCPU Exception caught\n CS: 0x%x\n", iframe->cs);
            firefly::kernel::io::legacy::writeTextSerial("EIP: %X\n", iframe->rip);
            firefly::kernel::io::legacy::writeTextSerial("ESP: %X\n", iframe->rsp);
        }
        firefly::kernel::shell::gui::make_rectangle(0, 0, 1024, 768, firefly::kernel::shell::GBAR(255, 0, 0, 0, 0), 0, 0, nullptr);
        firefly::kernel::shell::gui::make_text((char*)":(\nBlue Screen of Interrupt\n\nCPU Exception caught\nThis error was happened inside of the Shell Subsystem.\nIf you will get this error twice, make bug report on GitHub:\n              https://github.com/SergeyMC9730/Firefly-Kernel\n\nAditional info will be avaliable on the serial port\nPress Enter to close shell", 112, 126, 0xFFFFFFFF, 0);
        firefly::drivers::ps2::redirect_to_app(keyboard_handle, &current_key);
        while(current_key != 10){
            current_key = 0;
            firefly::drivers::ps2::app_input();
        }
        current_key = 0;
        firefly::kernel::shell::gui::make_text((char*)"Working on it...", 112, 126 + 256, 0xFFFFFFFF, 0);
        firefly::kernel::mp::clear();
        firefly::drivers::vbe::remove_shell();
        firefly::kernel::mp::turn_off();
        firefly::kernel::shell::gui::make_rectangle(0, 0, 1024, 768, firefly::kernel::shell::GBAR(0, 255, 0, 0, 0), 0, 0, nullptr);
        printf("WARNING: Doing this action for many times, system will softlock.\n");
        firefly::kernel::main::kernel_main();
    } else {
        if(firefly::kernel::settings::kernel_settings[5] == 1){
            firefly::kernel::io::legacy::writeTextSerial("\nCPU Exception caught\n CS: 0x%x\n", iframe->cs);
            firefly::kernel::io::legacy::writeTextSerial("EIP: %X\n", iframe->rip);
            firefly::kernel::io::legacy::writeTextSerial("ESP: %X\n", iframe->rsp);
        }
        if(firefly::applications::executing_from_app) printf("Application got closed by CPU Exception.\nAdditional info:\n");
        printf("CPU Exception caught\n CS: 0x%x\n", iframe->cs);
        printf("EIP: %X\n", iframe->rip);
        printf("ESP: %X\n", iframe->rsp);
        printf("INT NO: %X\n", iframe->int_no);

        if(!firefly::applications::executing_from_app) for (;;) asm("cli;hlt");
        is_crashed = true;
        firefly::kernel::main::kernel_main();
    }
}

__attribute__((interrupt)) __attribute__((noreturn)) void exception_wrapper([[maybe_unused]] iframe *iframe) {
    if(firefly::kernel::settings::kernel_settings[5] == 1){
        firefly::kernel::io::legacy::writeTextSerial("\nAn external interrupt has occured\n CS: 0x%x\n", iframe->cs);
        firefly::kernel::io::legacy::writeTextSerial("EIP: %X\n", iframe->rip);
        firefly::kernel::io::legacy::writeTextSerial("ESP: %X\n", iframe->rsp);
    }
    printf("An external interrupt has occured\n CS: 0x%x\n", iframe->cs);
    printf("EIP: %X\n", iframe->rip);
    printf("ESP: %X\n", iframe->rsp);

    for (;;)
        asm("cli;hlt");
}

void ack(int n){
    if(n >= 12) firefly::kernel::io::outb(0xA0, 0x20);
    firefly::kernel::io::outb(0x20, 20);
}
}  // namespace firefly::kernel::core::interrupt