#include <stdio.h>

void merge(int arr[], int low, int mid, int high)
{
    int temp[50];
    int i=0;
    int left = low;
    int right = mid+1;

    while(left<=mid && right<=high)
    {
        if(arr[left]<=arr[right])
        {
            temp[i] = arr[left];
            left++;
        }
        else
        {
            temp[i] = arr[right];
            right++;
        }
        i++;
    }

    while(left<=mid)
    {
        temp[i] =  arr[left];
        left++;
        i++;
    }

    while(right<=high)
    {
        temp[i] = arr[right];
        i++;
        right++;
    }

    for(i=low; i<=high; i++)
    {
        arr[i] = temp[i-low];
    }
}

void mergesort(int arr[], int low, int high)
{
    if(low<high)
    {
        int mid = low + (high-low)/2;

        mergesort(arr, low, mid);
        mergesort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergesort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}