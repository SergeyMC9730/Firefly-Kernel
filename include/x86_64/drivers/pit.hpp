#pragma once

#include <stl/cstdlib/cstdint.h>
#include <x86_64/drivers/ports.hpp>
#include <x86_64/registers.hpp>
#include <x86_64/int/interrupt.hpp>
#include <x86_64/drivers/serial_legacy.hpp>
#include <stl/cstdlib/stdio.h>
#include <x86_64/interrupts.hpp>

namespace firefly::drivers::pit {
    #define PIC1		    0x20		/* IO base address for master PIC */
    #define PIC2		    0xA0		/* IO base address for slave PIC */
    #define PIC1_COMMAND	PIC1
    #define PIC1_DATA	    (PIC1+1)
    #define PIC2_COMMAND	PIC2
    #define PIC2_DATA	    (PIC2+1)

    #define ICW1_ICW4	    0x01		/* ICW4 (not) needed */
    #define ICW1_SINGLE	    0x02		/* Single (cascade) mode */
    #define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
    #define ICW1_LEVEL	    0x08		/* Level triggered (edge) mode */
    #define ICW1_INIT	    0x10		/* Initialization - required! */
    
    #define ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */
    #define ICW4_AUTO	    0x02		/* Auto (normal) EOI */
    #define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
    #define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
    #define ICW4_SFNM	    0x10		/* Special fully nested (not) */

    #define PIC_READ_IRR    0x0A
    #define PIC_READ_ISR    0x0B
    
    void send_eoi(uint8_t irq);
    void remap(int offset1, int offset2);
    void disable();
    void mask(uint8_t irq);
    void clear_mask(uint8_t irq);

    uint16_t get_irq(int ocw3);
    uint16_t get_irr();
    uint16_t get_isr();
    
    void init();
}