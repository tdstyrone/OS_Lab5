#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int array[SIZE];

void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.
void* mergeSort(void* args) {
    StartEndIndexes sei = *((StartEndIndexes*)args);
    int error1, error2, midpoint;
    if (sei.start < sei.end){
        midpoint = (sei.start + sei.end) / 2;
        StartEndIndexes sei1, sei2;
        sei1.start = sei.start;
        sei1.end = midpoint;
        sei2.start = midpoint + 1;
        sei2.end = sei.end;
        pthread_t left_tid, right_tid;


        error1 = pthread_create(&left_tid, NULL, mergeSort, &sei1);
        error2 = pthread_create(&right_tid, NULL, mergeSort, &sei2);
        if (error1 != 0)
            printf("Error sorting left tree.\n");
        if (error2 != 0)
            printf("Error sorting right tree.\n");
            error1 = pthread_join(left_tid, NULL);
            error2 = pthread_join(right_tid, NULL);
        if (error1 != 0)
            printf("Error sorting left tree.\n");
        if (error2 != 0)
            printf("Error sorting right tree.\n");
            merge(sei.start, midpoint, sei.end);
    }
    return NULL;
}

int main() {
    srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
    
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create a 2 threads for merge sort.
    
    // 4. Wait for mergesort to finish.
    
    // 5. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);
}
