/* Тест для проверки правильности работы класса StrFromFile */
#include <iostream>
#include "str_from_file.hpp"
#include <string>
#include <cstring>

int main(int argc, char **argv){
	if (argc > 1) {
		StrFromFile strfile(":");
		//const char *name_file = "/Users/slava/Projects/holiday/.build/tests/SQL.txt";
		strfile.setNameFile(argv[1]);
		//strfile.printFile();
		try {
			std::string result = strfile.getString(argv[2]);
			std::cout << "Find string: " << result << std::endl;
			//const std::string  templateStr("{{idUnit}}");
			const char *templateStr = "{{idUnit}}";
			const char *replace_str = "40";
			//std::string m_result = 
			//std::cout << "На позиции " << idx << " найдена подстрока "<< templateStr << std::endl;
			size_t idx;
			while ((idx = result.find(templateStr)) != std::string::npos){
				//result.replace(idx, templateStr.length(), replace_str) ;
				result.replace(idx, std::strlen(templateStr), replace_str) ;
				//std::cout << "Result = " << result <<std::endl;
				//std::cout << "На позиции " << idx << " найдена подстрока "<< templateStr << std::endl;
				//idx = result.find(templateStr, idx+1);
			}
			//result.replace(templateStr.begin(), templateStr.end(), "40");
			std::cout << "Template = " << templateStr << "; Modified string: " << result << std::endl;
		}
		catch (StrFromFile::StrNoFound){
			std::cout << "Str \"" << argv[2] << "\" no found" << std::endl;
		}
		try {
			std::string result_str = strfile.getModifiedString(argv[2], "{{idUnit}}", "str");
			std::cout << "Modified string: " << result_str << std::endl;
		}
		catch (StrFromFile::StrNoFound){
			std::cout << "Не найдена строка \"" << argv[2] << "\"\n";
		}
	}
	return 0;
}

