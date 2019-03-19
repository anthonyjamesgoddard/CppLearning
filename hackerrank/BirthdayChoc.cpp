#include<iostream>
#include<vector>

int day = 10;
int month = 2;
int count = 0;

// Solution takes O(n * month) = O(n)

int main()
{
	std::vector<int> A = { 5,5,5,5,5,5 };
	for (int i = 0; i < A.size() - month; i++)
	{
		int j = 0;
		int sum = 0;
		while (j < month)
		{
			sum += A[i + j];
			j++;
		}
		if (sum == day) count++;
	}
	std::cout << count << std::endl;
}