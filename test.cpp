#include <stdio.h>
char buffer[8192];
int main(){
    int *intbuffer = (int*)buffer;
    intbuffer[5] = 2222;
    printf("%d\n",intbuffer[5]);
    return intbuffer[5] >> 1;
}