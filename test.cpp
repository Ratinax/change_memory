#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main()
{
	char *str = strdup("bonjour");
	pid_t pid = getpid();

	std::string exitString = "";
	while (exitString.empty() || exitString.compare("exit") != 0)
	{
		std::cout << "The string : " << str << std::endl;
		std::cout << std::endl;
		std::cout << "Enter exit if you want to quit and something else if you want to show The string: ";
		getline(std::cin, exitString);
		// std::cout << std::endl;
	}
	std::cout << str << std::endl;
	return(0);
}
