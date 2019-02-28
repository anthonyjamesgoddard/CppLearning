#include<iostream>
#include<vector>
#include<iterator>

void evenOdd(std::vector<int>* A_ptr)
{
    std::vector<int> A  = *A_ptr;
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

int main()
{
    std::vector<int> A = {1,4,6,3,6,23};
    evenOdd(&A);
    
    return 0;
}