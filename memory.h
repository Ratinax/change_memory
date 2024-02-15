#ifndef MEMORY_H
# define MEMORY_H

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <iomanip>
# include <string>
# include <strings.h>
# include <cstring>
# include <vector>
# include <unistd.h>
# include <sys/uio.h>

std::vector<long long> getMemoryList(pid_t processId, char *str);
std::map<std::string, long long> getRanges(const std::string &string);

#endif
