#include <stdio.h>
#include "sort.h"

void bubbleSort(int arr[], int n) {
    if (!arr || n <= 1) return;
    for (int i = 0; i < n - 1; i++) {
        int sorted = 1;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                sorted = 0;
            }
        }
        if (sorted) break;
    }
}

void bubbleSortFloats(double arr[], int n) {
    if (!arr || n <= 1) return;
    for (int i = 0; i < n - 1; i++) {
        int sorted = 1;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                sorted = 0;
            }
        }
        if (sorted) break;
    }
}

void printArray(const int arr[], int n) {
    if (!arr || n <= 0) return;
    for (int w = 0; w < n; w++) {
        if (w > 0) {
            printf(" ");
        }
        printf("%d", arr[w]);
    }
}

int isSorted(const int arr[], int n) {
    if (!arr || n <= 0) return 1;
    int ok = 1;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            ok = 0;
        }
    }
    return ok;
}
