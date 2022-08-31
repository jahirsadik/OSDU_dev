#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/dev/usart.h" // delete kore diyo
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
* first argument define the type of string to kprintf and kscanf,
* %c for charater
* %s for string,
* %d for integer
* %x hexadecimal
* %f for floating point number
*/

// function to copy the memory elements of src to dest
void my_memcpy(void *dest, void *src, size_t n)
{
    // Typecast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
     
    // Copy contents of src[] to dest[]
    for (int i=0; i<n; i++)
        cdest[i] = csrc[i];
}

// function to find the length of a string
unsigned int my_strlen(const char *s)
{
    unsigned int count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}



// Function to implement string copy
uint8_t* my_strcpy(uint8_t* destination, const uint8_t* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    uint8_t *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `my_strcpy()`
    return ptr;
}


// function to implement concatanation of two strings
uint8_t* my_strcat(uint8_t* dest_ptr,const uint8_t* src_ptr)
{

  uint8_t* strret = dest_ptr;
  if(dest_ptr && src_ptr)
  {
    /* Iterate till end of dest string */
    while(*dest_ptr)
    {
      dest_ptr++;
    }
    /* Copy src string starting from the end NULL of dest */
    while(*src_ptr)
    {
      *dest_ptr++ = *src_ptr++;
    }
    /* put NULL termination */
    *dest_ptr = '\0';
  }
  return strret;

}

// function to convert an integer to a string
void intToStr(uint8_t* dest, int src) {
    int bias = 0;
    if (src < 0) {
        src *= -1;
        dest[0] = '-';
        bias = 1;
    }
    int len = 0;
    uint8_t temp[10000];
    do
    {
        temp[len] = src % 10 + '0';
        src /= 10;
        len++;
    } while(src);
    for (int i = len - 1; i >= 0; i--)
    {
        dest[(len - 1) - i + bias] = temp[i];
    }
    dest[len + bias] = 0;
}

// function to convert an hexadecimal value to string
void hexToStr(uint8_t* dest, int src) {
    char map[] = "0123456789ABCDEF";
    int bias = 2;
    if (src < 0) {
        src *= -1;
        my_strcpy(dest, (uint8_t*)"-0x");
        bias += 1;
    } else {
        my_strcpy(dest, (uint8_t*)"0x");
    }
    int len = 0;
    uint8_t temp[10000];
    do
    {
        temp[len] = map[src % 16];
        src /= 16;
        len++;
    } while(src);
    for (int i = len - 1; i >= 0; i--)
    {
        dest[(len - 1) - i + bias] = temp[i];
    }
    dest[len + bias] = 0;
}


// function to computer base^exponent
int power(int base, int exponent)
{
    int result=1;
    for (int e = exponent; e>0; e--){
        result = result * base;
    }
    return result;
}

// function to convert floating-point number to string
void floatToString(uint8_t* dest, float src) {
    intToStr(dest, (int)src);
    uint8_t arrFrac[10000];
    uint8_t leadingString[8] = {0};

    float frac = src - (int)src;
    for (int leadingCount = 0; leadingCount < 7; leadingCount++)
    {
        float test = (frac * 10.0);
        if(test < 0) test = test * -1;
        if(test >= 1.00) break;
        leadingString[leadingCount] = '0';
        frac *= 10.0;
    }
    intToStr(arrFrac, abs((src - (int)src) * 1000000));
    my_strcat(dest, (uint8_t*)".");
    my_strcat(dest, leadingString);
    my_strcat(dest, arrFrac);
}




void kprintf(uint8_t *format, uint8_t* outvar)
{
    char c = format[1];
    uint8_t arr[10000];
    float tempF;
    switch (c) {
        case 'c':
        	_USART_WRITE(USART2,(uint8_t*)"kprintf: Character detected\n");
            arr[0] = *outvar;
            arr[1] = 0;
            break;
        case 's':
        	_USART_WRITE(USART2,(uint8_t*)"kprintf: String detected\n");
            my_strcpy(arr, outvar);
            break;
        case 'd':
        	_USART_WRITE(USART2,(uint8_t*)"kprintf: Integer detected\n");
            int temp;
            my_memcpy((char*)&temp, outvar, sizeof(int));
            intToStr(arr, temp);
            break;
        case 'x':
        	_USART_WRITE(USART2,(uint8_t*)"kprintf: Hex detected\n");
            int tempH;
            my_memcpy((char*)&tempH, outvar, sizeof(int));
            hexToStr(arr, tempH);
            break;
        case 'f':
            _USART_WRITE(USART2,(uint8_t*)"kprintf: Float detected\n");
            my_memcpy((char*)&tempF, outvar, sizeof(float));
            floatToString(arr, tempF);
            break;         
        default:
            break;
    }
    _USART_WRITE(USART2,(uint8_t*)"{");
    _USART_WRITE(USART2,(uint8_t*)arr);
    _USART_WRITE(USART2,(uint8_t*)"}\n");
}


void kscanf(uint8_t *format,uint8_t* invar)
{
// write your code here
	uint8_t recv[100];
	_USART_READ(USART2,recv,1000);
    char c = format[1];

    switch (c) {
        case 'c':
            _USART_WRITE(USART2,(uint8_t*)"kscanf: Character input detected:{");
            recv[1] = '\0';
            _USART_WRITE(USART2,(uint8_t*)recv);
            _USART_WRITE(USART2,(uint8_t*)"}\n");
            *invar = recv[0];
            break;
        case 's':
            _USART_WRITE(USART2,(uint8_t*)"kscanf: String input detected:{");
            _USART_WRITE(USART2,(uint8_t*)recv);
            _USART_WRITE(USART2,(uint8_t*)"}\n");
            int l = 0;
            while(recv[l]){
                invar[l] = recv[l];
                l++;
            }
            invar[l] = '\0';
            break;
        case 'd':
            _USART_WRITE(USART2,(uint8_t*)"kscanf: Integer input detected\n");
            int sign = 1, number = 0, idx = 0;
            if(recv[0] == '-'){
                sign = -1;
                idx = 1;
            }
     
            while(recv[idx] != '\0'){
                if(recv[idx] >= '0' && recv[idx] <= '9'){
                    number = number*10 + recv[idx] - '0';
                } else {
                    break;
                }
                idx++;
            }
            /* multiply number with sign to make it negative number if sign < 0*/
            number = number * sign;
            uint32_t *p = (uint32_t*)invar;
            (*p) = number;
            break;

        case 'x':
            _USART_WRITE(USART2,(uint8_t*)"kscanf: Hex input detected\n");
            int signh = 1, numberh = 0, idxh = 0;
            if(recv[0] == '-'){
                signh = -1;
                idxh = 1;
            }
     
            while(recv[idxh] != '\0'){
                if(recv[idxh] >= '0' && recv[idxh] <= '9'){
                    numberh = numberh*16 + recv[idxh] - '0';
                }else if(recv[idxh]>='A' && recv[idxh]<='F'){
                    numberh = numberh*16 + recv[idxh] - 55;
                }
                else {
                    break;
                }
                idxh++;
            }
            /* multiply number with sign to make it negative number if sign < 0*/
            numberh = numberh * signh;
            uint32_t *ph = (uint32_t*)invar;
            (*ph) = numberh;
            
            break;

        case 'f':
            _USART_WRITE(USART2,(uint8_t*)"kscanf: Floating point input detected\n");
            int signf = 1, idxf = 0;
            float numberf = 0.0;
            if(recv[0] == '-'){
                signf = -1;
                idxf = 1;
            }   
            int radixFound = 0;
            int rightOfRadix = 0;
            while(recv[idxf] != '\0'){
                if((recv[idxf] >= '0' && recv[idxf] <= '9') && !radixFound){
                    numberf = numberf*10 + recv[idxf] - '0';
                }else if(recv[idxf] == '.'){
                    radixFound = 1;
                    rightOfRadix++;
                }else if(radixFound && (recv[idxf] >= '0' && recv[idxf] <= '9')){
                    int val = recv[idxf] - '0';
                    int po = power(10, rightOfRadix);
                    numberf += ((val*1.0F)/po);
                    rightOfRadix++;
                }
                else {
                    break;
                }
                idxf++;
            }
            /* multiply number with sign to make it negative number if sign < 0*/
            numberf = numberf * signf;
            float *ptf= (float*)invar;
            (*ptf) = numberf;
            break;         
        default:
            break;
    }

}
