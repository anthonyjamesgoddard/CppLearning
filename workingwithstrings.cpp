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
std::string ConstructFromBase(int NumAsInt, int base)
{
	return NumAsInt == 0 ? "" : ConstructFromBase(NumAsInt / base, base) +
		(char)(NumAsInt % base >= 10 ? 'A' + NumAsInt % base - 10
			   : '0' + NumAsInt % base);
}



std::string convertBase(const std::string& NumAsString, int b1, int b2)
{
	bool is_negative = NumAsString.front() == '-';
	int NumAsInt = 0;
	for(size_t i = (is_negative == true ? 1 : 0);
		i < NumAsString.size();
		i++)
	{
		NumAsInt *= b1; 
		NumAsInt += isdigit(NumAsString[i]) ? NumAsString[i] - '0' : NumAsString[i] - 'A' + 10;
		std::cout << NumAsInt << std::endl;
	}
	return (is_negative ? "-" : "") +
		(NumAsInt == 0 ? "0" : ConstructFromBase(NumAsInt, b2));
}



int main()
{
	std::string str = "100000";
	std::cout << convertBase(str,2,10) << std::endl;
  	return 0;
}
