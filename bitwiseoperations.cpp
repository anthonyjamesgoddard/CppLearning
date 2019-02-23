#include<iostream>
#include<chrono>
#include<ctime>
// counts the bits equal to 1 in binary rep.
short CountBits_v1(unsigned int x)
{
  short num_bits = 0;
  while(x){
    num_bits += x & 1;  
    x >>= 1; // right-shift and assignment
    // this is equiv. to x = x/2
  }
  return num_bits;
}


// this works because if you subtract one from the binary rep. then you are essentially
// turning off the first on bit from right to left and then turning on all bits to the
// right of that bit. By taking taking the bit wise AND you are erasing the lowest
// bit each time.
short CountBits_v2(unsigned int x)
{
  short num_bits = 0;
  while(x){
    num_bits++;
    x = x & (x-1);
  }
  return num_bits;
}

// SUMMARY

// version 1 is slower than version 2.
// version 1 is O(n) where n is the word size (length of binary rep.)
// version 2 is O(k) where k is the number of bits equal to 1 (k < n)


// the parity of a binary number is partity of the number of bits equal to 1
short parity_v1(unsigned long long x)
{
  short result = 0;
  while(x){
    result ^= (x & 1); // ^ XOR operation
    // result = result^(x & 1)
    x >>= 1;
  }
  return result;
}
// the above code works by taking the bitwise AND which
// in turn causes result to change each time we encounter
// a 1 in the binary rep. of the number x. This operation is O(n)

int main()
{
  // we could use a class to obtain timing information.
  auto start = std::chrono::system_clock::now();
  CountBits_v1(99999999);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "bit_count_v1: " << elapsed_seconds.count() << "s\n";
  
  start = std::chrono::system_clock::now();                    
  CountBits_v2(99999999);                                           
  end = std::chrono::system_clock::now();                      
  elapsed_seconds = end-start;          
  std::cout << "bit_count_v2: " << elapsed_seconds.count() << "s\n";
}
