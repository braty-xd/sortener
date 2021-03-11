#ifndef sorting_algortihms
#define sorting_algortihms

void printArray(float arr[], int size);
void selectionSort(float arr[], int n);
void bubbleSort(float arr[], int n);
void insertionSort(float arr[], int n);
void merge(float arr[], int l, int m, int r);
void mergeSort(float arr[],int l,int r);
int partition (float arr[], int low, int high);
void quickSort(float arr[], int low, int high);
void heapify(float arr[], int n, int i);
void heapSort(float arr[], int n);
void bucketSort(float arr[], int n);
void shellSort(float arr[], int n);


#endif