#include "memory.h"

std::map<std::string, long long> getRanges(const std::string &string)
{
	std::string firstRange = "";
	std::string secondRange = "";
	std::map<std::string, long long> res;
	int j = 0;
	for (int i = 0; string[i]; i++)
	{
		if (string[i] == '-')
		{
			j = i;
			firstRange = string.substr(0, i);
			long long val = std::stoll(firstRange, 0, 16);
			res["min"] = val;
		}
		if (string[i] == ' ')
		{
			secondRange = string.substr(j + 1, i - j);
			long long val = std::stoll(secondRange, 0, 16);
			res["max"] = val;
		}
		if (!secondRange.empty() && !firstRange.empty())
			return res;
	}
	return (res);
}
