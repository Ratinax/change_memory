#include "memory.h"

int main(int argc, char **argv) {
	std::cout << argc << std::endl;
	if (argc < 5)
	{
		std::cerr << "Usage: ./change_memory proccess_id str_to_change nb_of_changes new_str" << std::endl;
		return (1);
	}
	pid_t pid = std::atoi(argv[1]);
	char *str = strdup(argv[2]);
	int nb_changes = std::atoi(argv[3]);
	std::vector<long long> memoryList = getMemoryList(pid, str);

	char *newValue = strdup(argv[4]);
	for (int i = 0; i < nb_changes; i++)
	{
		long long memoryAddress = memoryList[i];

		struct iovec local, distant;

		local.iov_base = newValue;
		local.iov_len = strlen(newValue);
		distant.iov_base = reinterpret_cast<void*>(memoryAddress);
		distant.iov_len = strlen(str);
		ssize_t bytesWritten = process_vm_writev(pid, &local, 1, &distant, 1, 0);
		if (bytesWritten == -1) {
			perror("Error while writing memory");
			return 1;
		}

		std::cout << memoryAddress << " Value modified successfully " << newValue << std::endl;
	}

	return 0;
}

