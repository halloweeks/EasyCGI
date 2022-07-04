#ifndef _RANDOM_STRING_
#define _RANDOM_STRING_

#include <ctime>
#include <unistd.h>

std::string randstr(const unsigned long long len) {
	static const char alphanum[] = 
	        "0123456789"
	        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	        "abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);
	
	for (unsigned long long i = 0; i < len; ++i ) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) -1)];
	}
	
	return tmp_s;
}

#endif
/*
int main() {
	srand((unsigned)time(NULL) * getpid());
	std::cout << randstr(1000) << "\n";
	return 0;
}
*/