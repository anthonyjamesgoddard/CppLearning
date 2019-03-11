#include <iostream>
#include <vector>

int main()
{
	std::vector<int> arr = { 4, 5, 6, 8, 7, 9, 10, 3, 2 };

	// finding the min and max sum of n-1 elements of a set of n
	int min = std::numeric_limits<int>::max();
	int max = 0;
	unsigned int sum = 0;
	for (auto& v : arr){
		sum += v;
		if (v > max) max = v;
		if (v < min) min = v;
	}
	std::cout << "max sum " << sum - min << std::endl;
	std::cout << "min sum " << sum - max << std::endl;

	// this can be made to work for n-2 elements too
	min = std::numeric_limits<int>::max();
	max = 0;
	int smin = std::numeric_limits<int>::max();
	int smax = 0;
	sum = 0;
	for (auto& v : arr){
		sum += v;
		if (v > max){
			smax = max;
			max = v;
		}
		else if (v > smax) smax = v;
		if (v < min){
			smin = min;
			min = v;
		}
		else if (v < smin) smin = v;
	}
	// this sometimes breaks on ordered vector inputs
	std::cout << "min " << min << std::endl;
	std::cout << "smin " << smin << std::endl;
	std::cout << "max " << max << std::endl;
	std::cout << "smax " << smax << std::endl;
	std::cout << "max sum " << sum - min - smin << std::endl;
	std::cout << "min sum " << sum - max - smax << std::endl;

	// this can be generalise to k elements of an array of n elements
	// the downside is that the storage is now O(k). Also the complexity
	// increases.

	// idea: store 2 vectors of min and max values
}