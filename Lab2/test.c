#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[10] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};
    //sort elements of array a
    int i, j, temp;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (a[i] < a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }

}