#include<iostream>

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


// this works because if you subtract one from
// the binary rep. then you are essentially
// turning off the first on bit from right to
// left and then turning on all bits to the
// right of that bit. By taking taking the
// bit wise AND you are removing a 1 bit each time.
short CountBits_v2(unsigned int x)
{
  short num_bits = 0;
  while(x){
    num_bits++;
    x = x & (x-1);
  }
  return num_bits;
}

int main()
{
  std::cout << "start of program" << std::endl;
  std::cout << CountBits_v1(11) << std::endl; // 3
  std::cout << CountBits_v2(13) << std::endl; // 3 (different positions)
}
