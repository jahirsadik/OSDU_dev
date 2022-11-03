/*
 * Copyright (c) 2022
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <unistd.h>
#include <kstdio.h>
#include <kunistd.h>
#include <syscall_def.h>
#include <stddef.h>
#include <kmain.h>
/* Write your highlevel I/O details */

void fu()
{
    int x = 41;
    // float y = 20.5;
    duprintf("OKAY %d %x %f \n\r", x, x, (float)x);
    duprintf("HELLO %d %x %f \n\r", x, x, x);
}

// idk where to put write
uint32_t write(uint32_t fd, char *s, size_t len)
{
    __asm volatile("MOV R1, %0"
                   :
                   : "r"(len)
                   :);
    // insert pointer s in register r1
    __asm volatile("MOVS R2, %0"
                   :
                   : "r"(s)
                   :);
    __asm volatile("MOV R12, %0"
                   :
                   : "r"(fd)
                   :);
    __asm volatile("SVC #0x37");
    return 0;
}

void duprintf(char *format, ...)
{
    char *tr;
    uint32_t i;
    uint8_t *str;
    va_list list;
    double dval;
    // uint32_t *intval;
    va_start(list, format);
    uint8_t result[100];
    int index = 0;
    for (tr = format; *tr != '\0'; tr++)
    {
        while (*tr != '%' && *tr != '\0')
        {
            // UART_SendChar(USART2,*tr);
            result[index++] = (uint8_t)*tr;
            tr++;
        }
        if (*tr == '\0')
            break;
        tr++;
        switch (*tr)
        {
        case 'c':
            i = va_arg(list, int);
            // UART_SendChar(USART2,i);
            result[index++] = (uint8_t)i;
            break;
        case 'd':
            i = va_arg(list, int);
            if (i < 0)
            {
                // UART_SendChar(USART2,'-');
                result[index++] = (uint8_t)'-';
                i = -i;
            }
            uint8_t *s1 = (uint8_t *)convert(i, 10);
            while (*s1)
            {
                result[index++] = *s1;
                // UART_SendChar(USART2,*s1);
                s1++;
            }

            // _USART_WRITE(USART2,(uint8_t*)convert(i,10));
            break;
        case 'o':
            i = va_arg(list, int);
            if (i < 0)
            {
                // UART_SendChar(USART2,'-');
                result[index++] = '-';
                i = -i;
            }
            // _USART_WRITE(USART2,(uint8_t*)convert(i,8));
            s1 = (uint8_t *)convert(i, 8);
            while (*s1)
            {
                result[index++] = *s1;
                // UART_SendChar(USART2,*s1);
                s1++;
            }
            break;
        case 'x':
            i = va_arg(list, int);
            if (i < 0)
            {
                // UART_SendChar(USART2,'-');
                result[index++] = '-';
                i = -i;
            }
            // _USART_WRITE(USART2,(uint8_t*)convert(i,16));
            s1 = (uint8_t *)convert(i, 16);
            while (*s1)
            {
                result[index++] = *s1;
                // UART_SendChar(USART2,*s1);
                s1++;
            }
            break;
        case 's':
            str = va_arg(list, uint8_t *);
            // _USART_WRITE(USART2,str);
            s1 = (uint8_t *)&str;
            while (*s1)
            {
                result[index++] = *s1;
                // UART_SendChar(USART2,*s1);
                s1++;
            }
            break;
        case 'f':
            dval = va_arg(list, double);
            // _USART_WRITE(USART2,(uint8_t*)float2str(dval));
            s1 = (uint8_t *)float2str(dval);
            while (*s1)
            {
                result[index++] = *s1;
                // UART_SendChar(USART2,*s1);
                s1++;
            }
            break;
        default:
            break;
        }
    }
    va_end(list);
    result[index] = '\0';
    // kprintf("ok = %s\n\r",result);
    write(STDOUT_FILENO, (char *)result, 10);
}