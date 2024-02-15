#include "memory.h"
std::vector<long long> getMemoryList(pid_t processId, char *str);

int main(int argc, char **argv) {
	if (argc < 3)
	{
		std::cout << "Should be used ./list pid str_to_find" << std::endl;
	}

	pid_t pid = std::atoi(argv[1]);
	char *str = strdup(argv[2]);

	getMemoryList(pid, str);
	free(str);
	return 0;
}
