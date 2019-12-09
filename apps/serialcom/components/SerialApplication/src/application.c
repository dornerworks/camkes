/*
 * Copyright 2019, DornerWorks
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DORNERWORKS_BSD)
 */

#include <autoconf.h>
#include <camkes.h>
#include <camkes/tls.h>
#include <camkes/dataport.h>
#include <stdio.h>

extern void *getchar_buf;
//this matches the size of the buffer in serial server
#define BUFSIZE 4088

void pre_init(void) {
    set_putchar(putchar_putchar);
}

void print_string(char* string, uint32_t len)
{
    for (uint32_t i=0; i<len; i++)
    {
        putchar_putchar(string[i]);
    }
}

char txbuf[BUFSIZE];

void handle_serial_console()
{
    struct {
        uint32_t head;
        uint32_t tail;
        char buf[BUFSIZE];
    } volatile *buffer = getchar_buf;
    int count = 0;
    char c;
    while (buffer->head != buffer->tail) {
        txbuf[count % BUFSIZE] = buffer->buf[buffer->head];
        c = buffer->buf[buffer->head];
        buffer->head = (buffer->head + 1) % BUFSIZE;
        count += 1 % BUFSIZE;
    }
    putchar_putchar(c);
}


void wait_callback(seL4_Word badge){
    handle_serial_console();
}

int run(void)
{

    print_string("Hello From The Application\n", 27);
    print_string("PROMPT> ", 8);
    while(1){
        seL4_Word badge;
        seL4_Wait(wait_notification(), &badge);
        wait_callback(badge);
    }
    return 0;
}
