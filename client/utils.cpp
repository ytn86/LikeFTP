#include <cstring>
#include <sstream>
#include <vector>



std::vector<std::string> split(const std::string& str, char deliminer)
{
	std::istringstream stream(str);
	std::vector<std::string> elem;
	std::string field;

	while (std::getline(stream, field, deliminer)) {
		elem.push_back(field);
	}

	return elem;
}


std::string char2str(char *s) {
     
	std::string str(s, strlen(s));
	return str;
}
	
