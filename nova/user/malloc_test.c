#include "mem_alloc.h"
#include <stdio.h>
#include <string.h>

int main()
{
    void *addr0 = my_malloc(0x8082);
    memset(addr0, 0x1, 0x8082);
    printf("%p\n", addr0);
    void *addr1 = my_malloc(0x442);
    memset(addr1, 0x2, 0x442);
    printf("%p\n", addr1);
    void *addr2 = my_malloc(0x9bcd);
    memset(addr2, 0x3, 0x9bcd);
    printf("%p\n", addr2);
    printf("%d\n", my_free(addr1));
    addr1 = addr2;
    addr2 = my_malloc(0xf996);
    printf("%p\n", addr2);
    memset(addr2, 0x4, 0xf996);
    void *addr3 = my_malloc(0xb8de);
    memset(addr3, 0x5, 0xb8de);
    my_free(addr3);
    addr3 = my_malloc(0x550);
    memset(addr3, 0x6, 0x550);
    void *addr4 = my_malloc(0xe861);
    memset(addr4, 0x7, 0xe861);
    my_free(addr2);
    addr2 = addr4;
    my_free(addr1);
    addr1 = addr3;
    addr3 = my_malloc(0xb6a1);
    memset(addr3, 0x8, 0xb6a1);
    addr4 = my_malloc(0xeb75);
    memset(addr4, 0x9, 0xeb75);
    void *addr5 = my_malloc(0x67cb);
    memset(addr5, 0xa, 0x67cb);
    my_free(addr4);
    addr4 = addr5;
    addr5 = my_malloc(0x4cc3);
    memset(addr5, 0xb, 0x4cc3);
    my_free(addr3);
    addr3 = addr5;
    addr5 = my_malloc(0x33fe);
    memset(addr5, 0xc, 0x33fe);
    return 0;
}
