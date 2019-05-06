#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;

// O(num1.size()*num2.size())
vector<int> Multiply(vector<int>& num1, vector<int>& num2) {
    vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i) {
        for (int j = num2.size() - 1; j >= 0; --j) {
            result[i + j + 1] += num1[i] * num2[j];
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }
    // Remove the leading zeroes. This will boost efficiency later on
    // result = {where_non-zero_entries_start, result(end)}
    result = {
        find_if_not(begin(result), end(result), [](int a) { return a == 0; }),
        end(result)};
    // if the above evaluates to result = {result(end), result(end)}
    if (result.empty()) {
        return {0};
    }
    return result;
}

// linear in number of digits
int SumOfDigits(vector<int>& num) {
    int sum = 0;
    for(auto& v : num) sum += v;
    return sum;
}

// linear in number of digits
vector<int> intToArray(int i) {
    vector<int> result;
    while(i){
        result.push_back(i%10);
        i/=10;
    }
    std::reverse(result.begin(),result.end());
    return result;
}

// Calculates the factorial
vector<int> Factorial(int n) {
    vector<int> current = {1};
    for(int i = 2; i <= n; i++)
    {
        vector<int> temp = intToArray(i); // implicit C++11 move semantics
        current = Multiply(temp, current); // same
    }
    return current;
}

int main()
{
    auto vec = Factorial(100);
    int sum = SumOfDigits(vec);
    std::cout << sum << std::endl;
}

