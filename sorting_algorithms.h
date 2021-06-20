#ifndef sorting_algortihms
#define sorting_algortihms


template <typename T>
void printArray(T arr, int size, bool is_vis);
template <typename T>
void selectionSort(T arr, int n,bool is_vis);
template <typename T>
void bubbleSort(T arr, int n,bool is_vis);
template <typename T>
void insertionSort(T arr, int n,bool is_vis);
template <typename T>
void merge(T arr, int l, int m, int r,bool is_vis);
template <typename T>
void mergeSort(T arr,int l,int r,bool is_vis);
template <typename T>
int partition (T arr, int low, int high,bool is_vis);
template <typename T>
void quickSort(T arr, int low, int high,bool is_vis);
template <typename T>
void heapify(T arr, int n, int i,bool is_vis);
template <typename T>
void heapSort(T arr, int n,bool is_vis);
// template <typename T>
// void bucketSort(T arr, int n);
template <typename T>
void shellSort(T arr, int n,bool is_vis);


//void visTry();

#include "sorting_algorithms_imp.h"
#include "visualize.h"
#include "vis_op.h"



#endif