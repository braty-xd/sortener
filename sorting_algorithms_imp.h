#include <iostream>
#include <vector>
#include <algorithm>
//#include "sorting_algorithms.h"
#include "visualize.h"
#include <unistd.h>

using namespace std; 


// void visTry()
// {
//     startScreen();
// }
// void visTryEnd()
// {
//     endScreen();
// }

//string current_array;
//stringstream ss;


template <typename T>
void printArray(T arr[], int size,bool is_vis)  
{  
    int i;  
    for (i=0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
}  
  
template <typename T>
void selectionSort(T arr, int n,bool is_vis)  
{  
    int i, j, min_idx;
    
    if(is_vis)
    {
        visPrintArray(arr,n,"Selection Sort");
        //sleep(0.5);
    }
    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n-1; i++)  
    {  
        // Find the minimum element in unsorted array  
        min_idx = i;
        visSetAttr(i,0);
        visWait();
        for (j = i+1; j < n; j++)
        {
            visSetAttr(j,0);
            visWait();
            if (arr[j] < arr[min_idx])
            {
                if(min_idx != i)
                {
                    visRemoveAttr(min_idx);
                }
                
                min_idx = j;
                //visSetAttr(min_idx,2);
            }
            
            visRemoveAttr(j);
            if(i != min_idx)
            {
                visSetAttr(min_idx,2);
            }
            
        }
         
        // Swap the found minimum element with the first element
        swap(arr[min_idx], arr[i]);
        visSwap(i,min_idx);
        visPrintCurrentArray();
    }
    //ss.str("");
    //std::cout << "current arr is " << current_array << "\n";
    current_array="";
} 

template <typename T>
void bubbleSort(T arr[], int n,bool is_vis)  
{
    visPrintArray(arr,n,"Bubble Sort");
    int i, j;  
    for (i = 0; i < n-1; i++)      
    {
        
        // Last i elements are already in place  
        for (j = 0; j < n-i-1; j++)
        {
            visSetAttr(j,0);
            visSetAttr(j+1,0);
            visWait();
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                visSwap(j,j+1);
                
            }
            visPrintCurrentArray();
            visWait();
        }     
    }
    current_array="";
} 

template <typename T>
void insertionSort(T arr[], int n,bool is_vis) 
{ 
    int i, j; 
    T key;
    visPrintArray(arr,n,"Insertion Sort");
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        //visVerticalLine(i);
        visSetAttr(i,0);
        visWait();
        j = i - 1; 
 
        /* Move elements of arr[0..i-1], that are 
        greater than key, to one position ahead 
        of their current position */
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key;
        visReplaceWithSpace(i,j+1); 
    }

    current_array="";
}

template <typename T>
void merge(T arr[], int l, int m, int r,bool is_vis)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    T L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            visMergePrintElement(l+i);
            i++;
        }
        else {
            arr[k] = R[j];
            visMergePrintElement(l+n1+j);
            j++;
        }
        k++;
        visWait();
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        visMergePrintElement(l+i);
        visWait();
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        visMergePrintElement(l+n1+j);
        visWait();
        j++;
        k++;
    }
    //visCrossBetween(l,r,merge_line-1);
    //visWait();
    visMergeReprintArray(l,r);
    //visCrossBetween(l,r,merge_line-1);
    //visCrossBetween(l,r,merge_line-1);
    visWait();
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
template <typename T>
void mergeSort(T arr[],int l,int r,bool is_vis)
{
    if(l>=r)
    {
        return;//returns recursively
    }
    if(merge_line== 0)
    {
        visPrintArray(arr,r+1,"Merge Sort");
        
    }
    else
    {
        visPrintArrayToLine(merge_line);
    }
    visCrossBetween(l,r,merge_line);
    visWait();
    merge_line++;
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m,is_vis);
    mergeSort(arr,m+1,r,is_vis);
    visMergeCrossVertical(m);
    visCrossBetween(l,r,merge_line-1);
    merge(arr,l,m,r,is_vis);
    //visCrossBetween(l,r,merge_line-1);
    //

    if(merge_line == 0)
    {
        current_array = "";
    }
}

template <typename T>
int partition (T arr[], int low, int high,bool is_vis) 
{ 
    T pivot = arr[high]; // pivot
    visCrossVertical(high);
    visCrossVerticalToLeft(low);
    visPrintCurrentArray();
    visSetAttr(high,0);
    visWait();
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++) 
    { 
        visCrossVertical(high);
        visCrossVerticalToLeft(low);
        if(j == low)
        {
            visSetAttr(i+1,2);
        } 
        // If current element is smaller than the pivot 
        visRemoveLineBetween();
        if(i+1 != j)
        {
            visAddLineBetween(i+1,j);
            visWait();
        }
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element
            
            swap(arr[i], arr[j]);

            if(i != j) 
            {
                visRemoveLineBetween();
                visAddLineBetween(i,j);
                visWait();
                visSwap(i,j);
                visWait();
                //visRemoveLineBetween();
                visPrintCurrentArray();
                visCrossVertical(high);
                visCrossVerticalToLeft(low);
                //visWait();
                visSetAttr(high,0);
                visSetAttr(i+1,2);
                
            } 
        } 
    } 
    swap(arr[i + 1], arr[high]);
    visRemoveLineBetween();
    visSwap(i+1,high);
    visWait();
    visPrintCurrentArray();
    visWait();
    return (i + 1); 
} 
 
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
template <typename T>
void quickSort(T arr[], int low, int high,bool is_vis) 
{   
    if(first_quick)
    {
        visPrintArray(arr,high+1,"Quick Sort");
        first_quick=false;
    }
    
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high,is_vis);
        
 
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1,is_vis); 
        quickSort(arr, pi + 1, high,is_vis); 
    } 
}

template <typename T>
void heapify(T arr[], int n, int i,bool is_vis)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest,is_vis);
    }
}
 
// main function to do heap sort
template <typename T>
void heapSort(T arr[], int n,bool is_vis)
{
    visPrintArray(arr,n,"Heap Sort");
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i,is_vis);
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) 
    {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0,is_vis);
    }
}

template <typename T>
void shellSort(T arr[], int n,bool is_vis) 
{ 
    visPrintArray(arr,n,"Shell Sort");
    bool is_changed;
    // Start with a big gap, then reduce the gap 
    for (int gap = n/2; gap > 0; gap /= 2) 
    { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i = gap; i < n; i += 1) 
        { 
            is_changed = false;
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            T temp = arr[i]; 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                is_changed = true;
                visAddLineBetween(j-gap,j);
                visSetAttr(j,2);
                visSetAttr(j-gap,2);
                visWait();
                arr[j] = arr[j - gap];
                visSwap(j-gap,j);
                visPrintCurrentArray();
                visRemoveLineBetween();
            }

            if(!is_changed)
            {
                visAddLineBetween(j-gap,j);
                visSetAttr(j,2);
                visSetAttr(j-gap,2);
                visWait();
                visPrintCurrentArray();
                visRemoveLineBetween();
            }
              
            //  put temp (the original a[i]) in its correct location 
            arr[j] = temp; 
        } 
    } 
    //return 0;
    current_array="";
}

// template <typename T>
// void bucketSort(T arr[], int n)
// {
     
//     // 1) Create n empty buckets
//     std::vector<float> b[n];
 
//     // 2) Put array elements 
//     // in different buckets
//     for (int i = 0; i < n; i++) {
//         int bi = n * arr[i]; // Index in bucket
//         b[bi].push_back(arr[i]);
//     }
 
//     // 3) Sort individual buckets
//     for (int i = 0; i < n; i++)
//         std::sort(b[i].begin(), b[i].end());
 
//     // 4) Concatenate all buckets into arr[]
//     int index = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < b[i].size(); j++)
//             arr[index++] = b[i][j];
// }


