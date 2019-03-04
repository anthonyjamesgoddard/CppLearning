#include<iostream>
#include<string>

bool isPalindromic(const std::string& s)
{
	int sz = s.size();
	for(int i = 0; i < sz; i++)
	{
		if(s[i] != s[sz-i-1])
		{
			return false;
		}
	}
	return true;
}

std::string intToString(int x)
{
	
}

int stringToInt(std::string& s)
{
	
}



int main()
{
	std::string str = "helleh";
	std::cout << str << std::endl;
	std::cout << isPalindromic(str) << std::endl;
	return 0;
}
