#include "util.h"
#ifdef MIRIV
    #include "libc.h"
#else
    #include <stdio.h>
#endif

int m_w = 0xFFFF2399;    /* must not be zero, nor 0x464fffff */
int m_z = 0xFFFF9841;    /* must not be zero, nor 0x9068ffff */
int get_random() {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

int abs(int value) {
    if (value < 0) return value * -1;
    return value;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int arr[], int n) {
    int i, j;
    int swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == 0)
            break;
    }
}
void print_prediction(int prediction) {
#ifdef MIRIV
    putstring("Prediction: ");
    putnumber(prediction);
    putstring("\n");
#else
    printf("Prediction: %d \n", prediction);
#endif
}
