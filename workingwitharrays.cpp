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
        if(A[j] < pivot)
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
        if(A[j] > pivot)
        {
            i--; // decrement to obtain item smaller than the pivot
            std::swap(A[i],A[j]); // swap with elemeent less than pivot
        }
    }
    std::swap(A[i-1], A[smallest]);
    return (i-1);
}

// median element (generally can be any element)
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
    
    int j=largest;
    for(int i = largest; i >= smallest && A[i] >= pivot ; i--)
    {
        for(j = i - 1; j >= smallest && A[j] >= pivot; j--)
        {
            if(A[j] > pivot)
            {
                std::swap(A[i], A[j]);
                break;
            }
        } 
    } 
    return (j-1);
    
}



// the above implementation is silly as we are 
// always starting from the beginning in the j loop.
// There is an improvement we can make. Taking inspiration
// from the vanilla partition algos
int partitionME(std::vector<int> &A, int smallest, int largest)
{
    std::cout << "pivot index " << (largest - smallest)/2 << std::endl;
    int pivot = A[(largest- smallest)/2];

    // the first pass groups elements smaller than the pivot
    int i = smallest - 1;
    for(int j = smallest; j <= largest; j++)    // this time our loop has to include the largest
    {
        if(A[j] < pivot)
        {
            std::swap(A[++i], A[j]);
        } 
    }
    
    i = largest + 1;
    for(int j = largest; j >= smallest && A[j] >= pivot; j--)
    {
        if(A[j] > pivot)
        {
            std::swap(A[--i], A[j]);
        } 
    } 
    return (i-1);
}

int partition_improved(std::vector<int>& A, int pi)
{
    int pivot = A[pi];
    int smaller = 0, equal = 0, larger = A.size();
    while(equal < larger)
    {
        if(A[equal] < pivot) std::swap(A[smaller++], A[equal++]);
        else if(A[equal] == pivot) ++equal;
        else std::swap(A[equal],A[--larger]); // A[equal] > pivot
    }
    return equal; 
}

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

// VARIANTS

/*
    1.
    Assuming that keys take one of three values reorder the array such that
    all objects with the same key appear together.

    In the following solutions we can suppose that each time we swap the keys (which
    are actually the values of the array) we can swap the objects as well. So that
    the indexing works out. Swapping object corresponds to swapping adresses so it should
    not be an issue.

    EASY, just choose the "middle" key. That is if we have {1,2,3,1,2,3,2,2,2,3,3,3}
    we just use pi = 1 (A[i] = 2). Running through the array to find the first
    instace of this will take O(n) in worst case. No significant addition space required

    2.
    The same but they can take one of four values. 
    
    implemented in partitionFourKeys

    3.
    array of n objects with boolean-valued keys. 
    
    Pretty much same answer as 1 above.

    4. 
    same as 3 but the relative ordering of true keys should not change.

    instead of fussing with templates lets just have 0 = false and 1 = true :D.
    Do this later, just to keep track of relativity we should keep
    an array of the same size with some ordering imposed. 
*/

    // we can answer 2 by modifying the algorithm to just
    // consider 1 and 4 as less than and greater than 2 OR 
    // 3. Then run partition on sub array

void partitionFourKeys(std::vector<int>& A)
{
    int smaller = 0, equal = 0, larger = A.size();
    while(equal < larger)
    {
        if(A[equal] == 1) std::swap(A[smaller++], A[equal++]);
        else if(A[equal] == 2 || A[equal] == 3) ++equal;
        else std::swap(A[equal],A[--larger]); // A[equal] == 4
    }
    equal = smaller;
    while(equal < larger)
    {
        if(A[equal] == 2) std::swap(A[smaller++], A[equal++]);
        else std::swap(A[equal],A[--larger]); // A[equal] == 4
    }
}

// adding 1 using arrays.
// this could be done in such a way that
// respects the user a bit more.
void addOne(std::vector<int>& A)
{
    int i = A.size() - 1;
    while(A[i] == 9)
    {
        A[i--] = 0;
        if(i == 0) break; // we have been given 999...9. Could throw an error
    }
    A[i]++;
}


int main()
{
    std::vector<int> A = {9,9,1};
    addOne(A);
    printVec(A);
    return 0;
}