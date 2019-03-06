// converts excel 'AAAA', 'BASD' to its int value

#include<iostream>
#include<string>

// Anthony's knucklehead solution
int b26ToInt(std::string& s)
{
	int result = 0;
	int power = 1;
	while (s.size())
	{
		char last = s.back();
		int temp = last - 64;
		s.pop_back(); 
		result += temp * power;
		power *= 26;
	}
	return result;
}

// beautiful solution 
int SSDecodeColID(const std::string& col)
{
	int result = 0;
	for (char c : col) // range based loop, oosh
	{
		result = result * 26 + c - 'A' + 1;
	}
	return result;
}

// now for the variants : 
// 1. what if A represented 0 onwardS...
/*
	this could be really easy, if A represents 0
	then AA is 26(?). If so then we just subtract 
	1 from the result of the previous routines.

	I do think think interpreting this any other
	way makes sense. :S.
*/
// 2. converting an integer back to SSCID

int main()
{
	std::string s = "AZ";
	std::cout << b26ToInt(s) << std::endl;
}