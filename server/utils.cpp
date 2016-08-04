#include <iostream>
#include <cstring>

std::string char2str(char *s) {
     
	std::string str(s, strlen(s));
	return str;
}
	
