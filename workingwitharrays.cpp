#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>


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
int partition(std::vector<int>& A, int smallest, int largest)
{
    int pivot = A[largest];
    int i = smallest -1 ; 
    // i is the index before the last seen element larger than
    // the pivot 
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

// could pass the partition function as a pointer!
void QuickSort(std::vector<int>& A, int smallest, int largest)
{
    if(smallest < largest)
    {
        int p = partition(A,smallest,largest);
        QuickSort(A, smallest, p-1);
        QuickSort(A, p+1, largest);
    }
}

int main()
{
    std::vector<int> A = {1,4,6,3,3,7,8,6,4};
    QuickSort(A, 0, A.size()-1 ); // Sorted  ;) !
    std::for_each(
              A.cbegin(),
              A.cend(),
              [] (const int c) {std::cout << c << " ";} 
              );
    return 0;
}