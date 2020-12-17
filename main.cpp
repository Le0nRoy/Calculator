#include <iostream>
#include <string>

// Read expression from stdin
void get_expression(std::string &str){
	std::cout << "Please enter your expression:" << std::endl;
	std::getline(std::cin, str);
}

int main(int argc, char **argv) {
	std::string buf;

	std::cout << "Hello vim!" << std::endl;

	while(true) {
		get_expression(buf);
		std::cout << buf << std::endl;
	}
	return 0;
}
