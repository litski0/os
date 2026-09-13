#include "string.h"

uint32_t strlen(uint8_t *s){
    uint32_t count =0;
    for(int i=0;s[i]!='\0';i++){
        count++;
    }
    return count;
}