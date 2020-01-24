/* Тест для проверки правильности работы класса StrFromFile */
#include <iostream>
#include "str_from_file.hpp"

int main(int argc, char **argv){
	if (argc > 1) {
		StrFromFile strfile(":");
		//const char *name_file = "/Users/slava/Projects/holiday/.build/tests/SQL.txt";
		strfile.setNameFile(argv[1]);
		//strfile.printFile();
		try {
			std::string result = strfile.getString(argv[2]);
			std::cout << "Find string: " << result << std::endl;
		}
		catch (StrFromFile::StrNoFound){
			std::cout << "Str \"" << argv[2] << "\" no found" << std::endl;
		}
	}
	return 0;
}

