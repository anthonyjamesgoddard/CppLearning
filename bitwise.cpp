#include <iostream>

void swap0(int& i, int& j) {
    int temp = i;
    i = j;
    j = temp;
}

void swap1(int& i, int& j) {
    i = i + j;
    j = i - j;  // i + j - j = i
    i = i - j;  // i - i + j = j
}

void multiplyBy7(int& x) { x = (x << 3) - x; }

void swap2(int& i, int& j) {
    i = i ^ j;
    j = i ^ j;  // i^ j ^ j = i^0 = i
    i = i ^ j;  // i ^ i ^ j = 0 ^ j = j
}

// cheeky : multiply by 7 as fast as possible

// x = (x << 3) - x;

int main() {
    int i = 10;
    int j = 4;
    swap1(i, j);
    swap2(i, j);
    std::cout << i << " " << j << std::endl;


    int x = 10;
    multiplyBy7(x);
    std::cout << x << std::endl;
}
