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

// idk where to put write
uint32_t write(uint32_t fd, char *s, size_t len)
{
    // first argument must be SYS_write service ID
    // SVC call for SYS_write
    __asm volatile("MOV R1, %0"
                   :
                   : "r"(len)
                   :);
    // insert pointer s in register r1
    __asm volatile("MOVS R2, %0"
                   :
                   : "r"(s)
                   :);
    __asm volatile("MOV R3, %0"
                   :
                   : "r"(fd)
                   :);
    __asm volatile("SVC #0x37");
    return 0;
}

// printf function
void duprintf(int i)
{
    // temp placeholder
    if (i)
    {
        char *temp = "Hello World"; // TODO: where to take this address from?
        // kprintf("---------Pointer to Temp: %d\n", temp);
        // kprintf("duprintf - R13: %d, PSP: %d, MSP: %d\n", readR13(), readPSP(), readMSP());
        uint32_t return_code = write(STDOUT_FILENO, temp, 11);
    }
    else
    {
        char *temp = "Behho Korke"; // TODO: where to take this address from?
        // kprintf("---------Pointer to Temp: %d\n", temp);
        // kprintf("duprintf - R13: %d, PSP: %d, MSP: %d\n", readR13(), readPSP(), readMSP());
        uint32_t return_code = write(STDOUT_FILENO, temp, 11);
    }
    return;
}
