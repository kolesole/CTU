/*
 * Execution Context
 *
 * Copyright (C) 2009-2011 Udo Steinberg <udo@hypervisor.org>
 * Economic rights: Technische Universitaet Dresden (Germany)
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#pragma once

#include "compiler.h"
#include "regs.h"
#include "tss.h"
#include "kalloc.h"
#include "memory.h"
#include "stdio.h"

class Ec
{
    private:
        Exc_regs    regs;

        /* Minimal and current break address (shared by all execution contexts) */
        static mword break_min, break_current;

        REGPARM (1)
        static void handle_exc (Exc_regs *) asm ("exc_handler");

        NORETURN
        static void handle_tss() asm ("tss_handler");

        static bool handle_exc_ts (Exc_regs *);

        ALWAYS_INLINE
        inline Sys_regs *sys_regs() { return &regs; }

        ALWAYS_INLINE
        inline Exc_regs *exc_regs() { return &regs; }

    public:
        static Ec * current;	/* Currently running execution context  */
        Ec * next;

        Ec();

        /* Switch to this execution context. Execution will continue
         * with Ec::ret_user_sysexit(). */
        ALWAYS_INLINE NORETURN
        inline void make_current()
        {
            current = this;
            Tss::run.sp0 = reinterpret_cast<mword>(exc_regs() + 1);
            Ec::ret_user_sysexit();
            UNREACHED; // Tell the compiler to not generate function epilog
        }

        HOT NORETURN
        static void ret_user_sysexit();

        NORETURN
        static void ret_user_iret() asm ("ret_user_iret");

        NORETURN
        static void idle();

        static void root_setup (mword);

        HOT NORETURN REGPARM_1
        static void syscall_handler (uint8 a) asm ("syscall_handler");

        ALWAYS_INLINE
        static inline void *operator new (size_t) { return Kalloc::allocator.alloc(sizeof (Ec)); }

        ALWAYS_INLINE
        static inline void operator delete (void *) { /* nop */ }
};
