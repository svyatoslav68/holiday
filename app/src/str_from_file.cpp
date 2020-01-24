/**********************************************************************
***** Реализация класса, подставляющего значение строковых ************
***** переменных из специального файла.                    ************
***** Имя файла - str_from_file.сpp                        ************
**********************************************************************/

#include <iostream>
#include <algorithm>
#include "str_from_file.hpp"

StrFromFile::StrFromFile(const char *_delimiter):delimiter(std::string(_delimiter)){
}

StrFromFile::StrFromFile(const char *_name_file, const char *_delimiter):name_file(std::string(_name_file)) {
	delimiter = std::string(_delimiter);
}

bool StrFromFile::setNameFile(const char *_name_file){
	name_file = std::string(_name_file);
	return true;
}

std::string StrFromFile::getString(const char *key_str, const char *delimiter){
	const uint16_t max_str_length = 1000;
	file.open(name_file, std::ifstream::in);
	char buf[max_str_length];
	std::string result;
	std::string search_str(key_str); 
	if (file){
		file.getline(buf, max_str_length);
		int numstr = 0;
		while (*buf){
			std::string source(buf);
			//if (auto it = result.find(key_str)){
			//search(source.begin(), source.end(), search_str.begin(), search_str.end()); 
			if (search(source.begin(), source.end(), search_str.begin(), search_str.end()) != source.end()){
				//std::cout << "№" << numstr << ':' << buf << std::endl;
				//std::cout << "№" << numstr << ':' << it << std::endl;
				//result = 
				//std::cout << *it << std::endl;
				std::string delimiter_str(delimiter);
				auto it = search(source.begin(), source.end(), delimiter_str.begin(), delimiter_str.end());
				std::insert_iterator<std::string> ii(result, result.begin());
				std::copy(it+delimiter_str.size(), source.end(), ii);
				//std::cout << "Find string: " << result << std::endl;
				return result;
			}
			file.getline(buf, max_str_length);
			numstr++;
		}
		throw StrNoFound();
	}
	else{
		std::cout << "Файл " << name_file << " не получилось открыть." << std::endl;
		throw FileNoFound();
	}
	return result;
}


void StrFromFile::printFile(){
	file.open(name_file, std::ifstream::in);
	if (file){
		std::cout << "name_file = " << name_file << std::endl;
		char c;
		while (file.get(c)) {
			std::cout.put(c);
		}
	}
	else
		std::cout << "Файл с именем " << name_file << " открыть не удалось." << std::endl;
	file.close();
}

