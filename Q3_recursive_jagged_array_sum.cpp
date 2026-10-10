
#include <iostream>
using namespace std;


int sumRow(int* row, int size)
{
    if (size == 0) return 0;                       
    return row[size - 1] + sumRow(row, size - 1);  
}

int recursiveArraySum(int* arr[], int sizes[], int dim)
{
    if (dim == 0) return 0;                        
    return sumRow(arr[dim - 1], sizes[dim - 1])    
         + recursiveArraySum(arr, sizes, dim - 1); 
}

int main()
{
    int r0[] = {1, 2, 3};
    int r1[] = {4, 5};
    int r2[] = {6, 7, 8, 9};
    int r3[] = {10};
    int r4[] = {11, 12, 13, 14, 15};

    int* arr[]  = {r0, r1, r2, r3, r4};            
    int  sizes[] = {3, 2, 4, 1, 5};                
    int  dims = sizeof(sizes) / sizeof(sizes[0]);  

    cout << "Total sum = " << recursiveArraySum(arr, sizes, dims) << endl;  
    return 0;
}
