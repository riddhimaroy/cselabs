#include <stdio.h>

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low+1;
    int j = high;

    while(i<=j)
    {
        while(arr[i]<=pivot && i<=high)
            i++;

        while(arr[j]>pivot)
            j--;

        if(i<j)
        {
            int temp = arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }

    arr[low] = arr[j];
    arr[j] = pivot;

    return j;
}

void quicksort(int arr[], int low, int high)
{
    if(low<high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi-1);
        quicksort(arr, pi+1, high);
    }
}

int main()
{
    int arr[] = {12, 7, 14, 9, 10, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}