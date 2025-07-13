#include "ec.h"
#include "ptab.h"
#include "bits.h"

#include <string.h>
#include <stdbool.h>

typedef enum {
    sys_print      = 1,
    sys_sum        = 2,
    sys_nbrk       = 3,
    sys_thr_create = 4,
    sys_thr_yield  = 5,
} Syscall_numbers;

// function to deallocate memory pages
void deallocate_memory(mword cur_break, mword new_break) {
    while (cur_break != new_break) {
        cur_break -= PAGE_SIZE;                                        // move the break down by one page size 
        
        mword phys = Ptab::get_mapping(cur_break);                     // get the current physical address
        void* virt = Kalloc::phys2virt(phys & ~PAGE_MASK);             // convert the current physical address to a virtual address 

        Ptab::insert_mapping(cur_break, 0, 0);                         // remove the mapping from the page table
        Kalloc::allocator.free_page(virt);                             // free page
    }
}

// function to allocate memory pages
bool allocate_memory(mword cur_break, mword new_break) {
    bool flag = false;
    mword attr = Ptab::PRESENT | Ptab::RW | Ptab::USER;
    mword tmp = cur_break;

    while (cur_break != new_break) {
        void* virt = Kalloc::allocator.alloc_page(1, Kalloc::FILL_0);  // allocate a new page and fill it 0 
        if (virt == NULL) {
            flag = true;
            break;
        }

        mword phys = Kalloc::virt2phys(virt);                          // convert the virtul address to physical
        if (!Ptab::insert_mapping(cur_break, phys, attr)) {            // insert the mapping into the page table
            Kalloc::allocator.free_page(virt);
            flag = true;
            break;
        }

        cur_break += PAGE_SIZE;                                        // move the break up by one page size
    }

    if (flag) {
        deallocate_memory(cur_break, tmp);                             // if an error occurred during allocation, rollback the changes
    }

    return !flag;
}

/**
 * System call handler
 *
 * @param[in] a Value of the `al` register before the system call
 */
void Ec::syscall_handler (uint8 a)
{
    // Get access to registers stored during entering the system - see
    // entry_sysenter in entry.S
    Sys_regs * r = current->sys_regs();
    Syscall_numbers number = static_cast<Syscall_numbers> (a);

    switch (number) {
        case sys_print: {
            // Tisk řetězce na sériovou linku
            char *data = reinterpret_cast<char*>(r->esi);
            unsigned len = r->edi;
            for (unsigned i = 0; i < len; i++)
                printf("%c", data[i]);
            break;
        }
        case sys_sum: {
            // Naprosto nepotřebné systémové volání na sečtení dvou čísel
            int first_number = r->esi;
            int second_number = r->edi;
            r->eax = first_number + second_number;
            break;
        }
        case sys_nbrk: {
            r->eax = Ec::break_current;

            mword address = r->esi;
            if (address == 0) {
                break;
            }
            else if (address < Ec::break_min || address > 0xC0000000) {
                r->eax = 0;
                break;
            }
            
            mword cur_break = align_up(Ec::break_current, PAGE_SIZE);
            mword new_break = align_up(address, PAGE_SIZE);

            if (address > Ec::break_current) {
                mword offset = Ec::break_current % PAGE_SIZE;                                                        // check if the last page is aligned
                if (offset != 0) {
                    mword phys = Ptab::get_mapping(cur_break - PAGE_SIZE);                                           // get last page physical address
                    void* virt = Kalloc::phys2virt(phys & ~PAGE_MASK);                                               // convert the physical address to virtual
                    memset(reinterpret_cast<void*>(reinterpret_cast<mword>(virt) + offset), 0, PAGE_SIZE - offset);  // fill it 0 to align it
                }

                if (!allocate_memory(cur_break, new_break)) {                                                        // if allocation failed --> return 0 
                    r->eax = 0;
                    break;
                } 

                Ec::break_current = address;
                break;
            }

            if (address < Ec::break_current) {
                deallocate_memory(cur_break, new_break);
                Ec::break_current = address;
            }

            break;
        }
        // TODO: Add your system calls here
        default:
            printf ("unknown syscall %d\n", number);
            break;
    };

    ret_user_sysexit();
}
