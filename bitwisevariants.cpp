// right propagate the rightmost set bit in x

#include<iostream>
#include<bitset>

unsigned long long subtract(unsigned long long x,
							unsigned long long y)
{
    unsigned long long b; // borrow
    while(y != 0)                 
    {                             
        b = ~x & y;                
        x = x ^ y; // diff   
        y = b >> 1;               	
    }                             
    return x;                     
}

// the idea is to recursively add the remainder and
// the shifted carry untill the carry is zero.
unsigned long long add(unsigned long long x,
                       unsigned long long y)
{
	unsigned long long c; // carry
	while(y != 0)
	{
		c = x & y;
		x = x ^ y; // remainder
		y = c << 1;
	}
	return x;
}



unsigned long long propRightmostOne(unsigned long long x)
{
	// using arith. orerations 
	x |= subtract(x,1);
	// using bitwise operations
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
	return x && (! (x & subtract(x,1)) );
	// y = x & (x-1) removes the least significant bit.
	// if x is a power of 2 then the result is 0.
	 // !y will be true in this case.
	 // since x >0 then true && true = true
	
	 // y will have the boolean value of true
	 // if it is greater than zero, which is the case
	 // if x is not a power of 2
}


unsigned long long swapbits(unsigned long long x, int i, int j)
{
	// we only want to swap bits when they are different
	if(!((x & (1 << i)) & (x & (1 << j))))
	{
		unsigned long long mask = (1L << i) | (1L << j);
		return x ^= mask; // XOR does the job
	}
	return x;
}

int main()
{
	int x = 23;
	std::cout << std::bitset<32>(x).to_string() << std::endl;
	std::cout << std::bitset<32>(swapbits(swapbits(x,1,3),1,3)).to_string() << std::endl;
	 
	return 0;
}
