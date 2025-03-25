#include <stdio.h>
#include <string.h>

int main (void)
{ 
    int a[5] = {2, 4, 6, 8, 22}; 
    int* p = &a[1]; 
    printf("%d %d ", a[0], p[-1]); 
    printf("%d %d ", a[1], p[0]);
}