#include <stdio.h>
#include <stdlib.h>

void del(int arr[], int n, int k) {
    int stack[n];
    int top = -1;
    int i;
    int t=k;

    for (i = 0; i < n; i++) {

        while (top >= 0 && stack[top] < arr[i] && k > 0) {
            top--;
            k--; 
        }
        stack[++top] = arr[i]; 
    }

    while (k > 0) {
        top--;
        k--;
    }

    for (i = 0; i < n-t; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    int l, i, k, arr[15];
    printf("Enter the limit of array");
    scanf("%d", &l);
    printf("Enter elements into array");
    for(i =0; i<l; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter number of elements to be deleted");
    scanf("%d", &k);

    del(arr, l, k);

    return 0;
    
}
