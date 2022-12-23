#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>

// 时间处理头文件
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;

class MyUtil
{
public:
	static bool compare_write_data(char *buf1, char *buf2);
	static std::vector<std::string> split(std::string str, std::string pattern);
	static const std::string getCurDate();
};

#endif