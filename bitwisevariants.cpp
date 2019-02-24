// right propagate the rightmost set bit in x

#include<iostream>
#include<bitset>

unsigned long long propRightmostOne(unsigned long long x)
{
  // aside from a loop can i reduce x-1 to something
  // bitwise ?
  x |= (x-1); 
  return x;
}

int modPowerOf2(int x, int thePower)
{                                                        
  // isolate the last thePower bits
  int mask = (1 << thePower) -1;
  return mask & x;
}

bool isPowerOf2(int x)
{
  // true if there is only 1 bit set in binary rep
  return x && (! (x & (x-1)) );
  // y = x & (x-1) removes the least significant bit.
  // if x is a power of 2 then the result is 0.
  // !y will be true in this case.
  // since x >0 then true && true = true

  // y will have the boolean value of true
  // if it is greater than zero, which is the case
  // if x is not a power of 2
}

int main()
{
  int x = 23;
  std::string binary = std::bitset<32>(x).to_string(); //to binary
  std::cout<<binary<<"\n";
  x = modPowerOf2(x,2);
  binary = std::bitset<32>(x).to_string(); //to binary
  std::cout<<binary<<"\n";                                           
  return 0;
}
