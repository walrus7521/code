#include<stdio.h> 
  
// returns index of element x in arr[] size n
int search(int arr[], int n, int x) 
{ 
    int i; 
    for (i = 0; i < n; i++) { 
       if (arr[i] == x) return i; 
    } 
    return -1; 
}  
  
int main() 
{ 
    int arr[100], x, n_tests, n, i; 

    // Input the number of test cases you want to run 
    scanf("%d", &n_tests);  

    while (n_tests--) { 
        // Input the size of the array 
        scanf("%d", &n);  

        // Input the array 
        for (i=0; i<n; i++) scanf("%d",&arr[i]); 
  
        // Input the element to be searched 
        scanf("%d", &x); 

        // Compute and print result 
        printf("%d\n", search(arr, n, x)); 
    } 
    return 0; 
} 

