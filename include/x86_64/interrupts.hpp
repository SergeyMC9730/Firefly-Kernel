#pragma once

#define cli() asm volatile("cli")
#define sti() asm volatile("sti")