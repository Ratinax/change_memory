#include "memory.h"

using namespace std;

static bool put_address(void *tab, char *str, long long memoryAddress)
{
	char *rtab = reinterpret_cast<char*>(tab);

	if (strncmp(rtab, str, strlen(str)) == 0)
	{
		std::cout << "String \""<< str << "\" found at address " << std::hex << memoryAddress << std::endl;
		return (true);
	}
	return (false);
}

static bool printMemories(pid_t processId, long long memoryAddress, char *str)
{
	char buffer[strlen(str)];

	void *remotePtr = (void *)memoryAddress;

	struct iovec local[1];
	local[0].iov_base = calloc(strlen(str), sizeof(char));
	local[0].iov_len = strlen(str);

	struct iovec remote[1];
	remote[0].iov_base = remotePtr;
	remote[0].iov_len = strlen(str);

	ssize_t nread = process_vm_readv(processId, local, 2, remote, 1, 0);
	if (nread < 0) {
		switch (errno) {
			case EINVAL:
			printf("ERROR: INVALID ARGUMENTS.\n");
			break;
			case EFAULT:
			printf("ERROR: UNABLE TO ACCESS TARGET MEMORY ADDRESS.\n");
			break;
			case ENOMEM:
			printf("ERROR: UNABLE TO ALLOCATE MEMORY.\n");
			break;
			case EPERM:
			printf("ERROR: INSUFFICIENT PRIVILEGES TO TARGET PROCESS.\n");
			break;
			case ESRCH:
			printf("ERROR: PROCESS DOES NOT EXIST.\n");
			break;
			default:
			printf("ERROR: AN UNKNOWN ERROR HAS OCCURRED.\n");
		}

		return false;
	}
	return put_address(local[0].iov_base, str, memoryAddress);
}

std::vector<long long> getMemoryList(pid_t processId, char *str) {
	std::string mapsFilePath = "/proc/" + std::to_string(processId) + "/maps";

	std::ifstream mapsFile(mapsFilePath.c_str());
	std::vector<long long> addresses;

	if (!mapsFile.is_open()) {
		std::cerr << "Error while opening " << "/proc/" + std::to_string(processId) + "/maps" << std::endl;
		return (addresses);
	}

	std::string line;
	while (std::getline(mapsFile, line)) {

		if (line.find("stack") <= line.size() || line.find("heap") <= line.size())
		{
			std::cout << line << std::endl;
			std::map<std::string, long long> res = getRanges(line);
			for (long long i = res["min"]; i < res["max"]; i++)
			{
				if (printMemories(processId, i, str))
					addresses.push_back(i);
			}
		}
	}
	mapsFile.close();
	return (addresses);
}
