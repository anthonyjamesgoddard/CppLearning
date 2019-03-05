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
	bool is_negative = false;
	if(x < 0)
	{
		is_negative = true;
	}
	
	std::string s;
	
	do {
		s += '0' + abs(x % 10);
		x /= 10;
	} while(x);

	if(is_negative) {
		s += '-';
	}

	return {s.rbegin(), s.rend()};
	
}

// slightly more elegant than what I come up with
int stringToInt(const std::string& s)
{
	int result = 0;
	for(int i = s[0] == '-' ? 1 : 0; i < s.size(); ++i)
	{
		const int digit = s[i] - '0';
		result = result * 10 + digit;
	}
	return s[0] == '-' ? -result : result;
}


std::string convertBase(const std::string& NumAsString, int b1, int b2)
{
	bool is_negative = NumAsString
	
}

int main()
{
	std::string str = "100001";
	std::cout << str << std::endl;
	std::cout << intToString(10) << std::endl;
	std::cout << stringToInt(str) << std::endl;
	return 0;
}
