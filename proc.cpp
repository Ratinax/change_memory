#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <map>

typedef struct s_proc
{
	bool is_running;
	time_t date_start;
	bool has_been_printed;
} t_proc;

#define PROCCESS_TIME 30

static int get_max_proc() {
	std::ifstream limitsFile("/proc/self/limits");

	if (!limitsFile.is_open()) {
		std::cerr << "Error while oppening /proc/self/limits." << std::endl;
		return 1;
	}
	std::string line;
	while (std::getline(limitsFile, line)) {
		size_t pos = line.find("Max processes");
		if (pos != std::string::npos) {
			std::string value = line.substr(pos + 14);
			size_t found = value.find_first_of("0123456789");
			std::string processLimit = value.substr(found);
			limitsFile.close();
			return (99999);
			return(std::atoi(processLimit.c_str()));
		}
	}
	return 0;
}


static void reset_proc_map(std::map<int, t_proc> &map)
{
	int max_proc = get_max_proc();
	for (int i = 0; i < max_proc; i++)
	{
		map[i].is_running = false;
		map[i].date_start = 0;
		map[i].has_been_printed = false;
	}
}

static void print_closed_proc(std::map<int, t_proc> &map, std::map<int, t_proc> &map2)
{
	int max_proc = get_max_proc();
	for (int i = 0; i < max_proc; i++)
	{
		if (map[i].is_running == true && map2[i].is_running == false)
		{
			if (map[i].date_start + PROCCESS_TIME < time(NULL))
				std::cout << "Process ID : " << i << " stoped" << std::endl;
			map[i].is_running = false;
		}
		else if (!(map[i].has_been_printed) && map[i].is_running == true && map2[i].is_running == true && map[i].date_start + PROCCESS_TIME < time(NULL))
		{
			std::cout << "Process ID : " << i << " started" << std::endl;
			map[i].has_been_printed = true;
		}
	}
}

static void monitorProccesses() {
	bool is_first_round = true;
	pid_t parentProcessId = getpid();
	std::map<int, t_proc> alive;
	reset_proc_map(alive);
	std::map<int, t_proc> alive2 = alive;


	while (true) {
		reset_proc_map(alive2);
		DIR *dir = opendir("/proc");
		if (dir == nullptr) {
			std::cerr << "Error while openning /proc." << std::endl;
			return;
		}

		dirent *entry;

		while ((entry = readdir(dir)) != nullptr) {
			if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
				pid_t processId = atoi(entry->d_name);

				if (alive[processId].is_running == false) {
					alive[processId].is_running = true;
					alive[processId].date_start = time(NULL);
					if (is_first_round)
						alive[processId].has_been_printed = true;
				}
				alive2[processId].is_running = true;
			}
		}
		print_closed_proc(alive, alive2);
		closedir(dir);
		is_first_round = false;
	}
}

int main() {
	std::cout << "Monitoring processes. Press Ctrl+C to stop." << std::endl;

	std::thread monitorThread(monitorProccesses);

	monitorThread.join();

	return 0;
}

