#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

void printVec(std::vector<int> &A)
{
    std::for_each(
              A.cbegin(),
              A.cend(),
              [] (const int c) {std::cout << c << " ";} 
              );
    std::cout << std::endl;
}


// puts the even numbers at the beginning of the array, odd numbers at the end
void evenOdd(std::vector<int>& A)
{
    int next_even = 0, next_odd = A.size() - 1;
    while(next_even < next_odd)
    {
        if(A[next_even] % 2)
        {
            next_even++;
        }
        else
        {
            std::swap(A[next_even], A[next_odd]);
            next_odd--;
        }
        
    }
}

// partition routine that appears in QuickSort
// the pivot is hardcoded as the last element of the vector
// LE last element
int partitionLE(std::vector<int>& A, int smallest, int largest)
{
    int pivot = A[largest];
    int i = smallest -1 ; 
    // i is the index "before" the first seen element larger 
    // than pivot since a swap
    for(int j = smallest; j < largest; j++)
    {
        if(A[j] <= pivot)
        {
            i++; // increment to obtain item larger than the pivot
            std::swap(A[i],A[j]); // swap with elemeent less than pivot
        }
    }
    std::swap(A[i+1],A[largest]);
    return (i+1);
}

// pi = pivot index
// FE first element
int partitionFE(std::vector<int> &A, int smallest, int largest)
{
    int pivot = A[smallest];
    int i = largest + 1; 
    // i is the index "after" the last seen element smaller
    // than pivot since the last swap
    for(int j = largest; j > smallest; j--)
    {
        if(A[j] >= pivot)
        {
            i--; // decrement to obtain item smaller than the pivot
            std::swap(A[i],A[j]); // swap with elemeent less than pivot
        }
    }
    std::swap(A[i-1], A[smallest]);
    return (i-1);
}

// median element
// the above are special cases, when we choose an
// element to be the pivot other than the first or 
// last one then we have to be carefull
int partitionMEStupidVersion(std::vector<int> &A, int smallest, int largest)
{
    std::cout << "pivot index " << (largest - smallest)/2 << std::endl;
    int pivot = A[(largest- smallest)/2];

    // the first pass groups elements smaller than the pivot
    for(int i = smallest; i <= largest; i++)
    {
        for(int j = i + 1; j <= largest; j++)
        {
            if(A[j] < pivot)
            {
                std::swap(A[i], A[j]);
                break;
            }
        } 
    }
    
    for(int i = largest; i >= smallest && A[i] >= pivot ; i--)
    {
        for(int j = i - 1; j >= smallest && A[j] >= pivot; j--)
        {
            if(A[j] > pivot)
            {
                std::swap(A[i], A[j]);
                break;
            }
        } 
    } 
    
}

// the above implementation is silly as we are 
// always starting from the beginning.

// They are all really buggy! All these partition algos break. Find out where and fix!

// could pass the partition function as a pointer!
void QuickSort(std::vector<int>& A, int smallest, int largest)
{
    if(smallest < largest)
    {
        int p = partitionLE(A,smallest,largest);
        QuickSort(A, smallest, p-1);
        QuickSort(A, p+1, largest);
    }
}



int main()
{
    // this is an example where the first two algorithms break
    std::vector<int> A = {1,2,4,3,9,0,1};
    auto B = A;
    auto C = A;
    printVec(A);
    std::cout << "first element partitioning" << std::endl;
    partitionFE(B,0,B.size()-1);
    printVec(B);
    std::cout << "last element partitioning" << std::endl;
    partitionLE(C,0,C.size()-1);
    printVec(C);
    std::cout << "median element partitioning" << std::endl;
    partitionMEStupidVersion(C,0,C.size()-1);
    printVec(C);
    return 0;
}