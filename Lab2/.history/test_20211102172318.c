#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[10];
    //calculate the sum of the elements in the array
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        sum += a[i];
    }
    //reverse the array
    for (int i = 0; i < 10; i++) {
        a[i] = a[9 - i];
    }
    //
}