#include<iostream>
#include<chrono>
#include<ctime>

// for debugging
#include<bitset>
#include<string>
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
// a 1 in the binary rep. of the number x.
//
// result wont change unless x&1 is 1. 
// This operation is O(n)

short parity_v2(unsigned long long x)
{
  short result = 0;
  while(x){
    result ^=1; // result = result ^ 1
    x &= (x-1); // removes the least significant 1
  }
  return result;
}

// again this is O(k) as the algorithm removes a 1 bit each time
// and finishes when all 1 bits are gone.

int kPreComputedParity[4] = {0, 1, 1, 0};

short parity_v3(unsigned long long x)
{
  short result = 0;
  const int kMaskSize = 2; // limited by 8 bit itegers
  const int kBitMask  = 3; // gets the last two bits after shifting
  return kPreComputedParity[x >> (3*kMaskSize)] ^
    kPreComputedParity[(x >> (2*kMaskSize)) & kBitMask] ^
    kPreComputedParity[(x >> kMaskSize) & kBitMask] ^
    kPreComputedParity[x & kBitMask];
}

// this is okay but we have to store data
// the time expense comes frm the shifting operation
// That is, the cost is O(kMaskSize) = O(n/len(kPreComputedParity)).

// the above algorithms have been O(n), or thereabouts
// the below algorithm uses a halving method which reduces the
// problem to O(log n) = log 64 = 5

short parity_v4(unsigned long long x)
{
  x^= x >> 32;
  x^= x >> 16;
  x^= x >> 8;
  x^= x >> 4;
  x^= x >> 1;
  return x & 0x1;  
}


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

  start = std::chrono::system_clock::now();                         
  parity_v1(99999999);                                           
  end = std::chrono::system_clock::now();                           
  elapsed_seconds = end-start;                                      
  std::cout << "parity_v1:  " << elapsed_seconds.count() << "s\n";

  start = std::chrono::system_clock::now();                       
  parity_v2(99999999);                                            
  end = std::chrono::system_clock::now();                           
  elapsed_seconds = end-start;                                      
  std::cout << "parity_v2:  " << elapsed_seconds.count() << "s\n";

  start = std::chrono::system_clock::now();                       
  parity_v4(99999999);                                            
  end = std::chrono::system_clock::now();                         
  elapsed_seconds = end-start;                                    
  std::cout << "parity_v4:  " << elapsed_seconds.count() << "s\n";
}
