/**********************************************************************
***** Реализация класса, подставляющего значение строковых ************
***** переменных из специального файла.                    ************
***** Имя файла - str_from_file.сpp                        ************
**********************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include "str_from_file.hpp"

using std::string;

StrFromFile::StrFromFile(const char *_delimiter):delimiter(string(_delimiter)){
}

StrFromFile::StrFromFile(const char *_name_file, const char *_delimiter):name_file(string(_name_file)), delimiter(string(_delimiter)) {
}

bool StrFromFile::setNameFile(const char *_name_file){
	name_file = string(_name_file);
	return true;
}

string StrFromFile::getString(const char *key_str, const char *delimiter){
	/*Ищется строка в файле name_file, содержащая построку key_str. 
	 * подстрока может содержаться в любом месте строки, не обязательно
	 * в ключе. Возвращается часть строки после delimiter */
	std::ifstream file;
	const uint16_t max_str_length = 1000;
	file.open(name_file, std::ifstream::in);
	char buf[max_str_length];
	string result;
	string search_str(key_str); 
	if (file){
		file.getline(buf, max_str_length);
		int numstr = 0;
		while (*buf){
			string source(buf);
			if (search(source.begin(), source.end(), search_str.begin(), search_str.end()) != source.end()){
				string delimiter_str(delimiter);
				auto it = search(source.begin(), source.end(), delimiter_str.begin(), delimiter_str.end());
				std::insert_iterator<string> ii(result, result.begin());
				std::copy(it+delimiter_str.size(), source.end(), ii);
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
	file.close();
	return result;
}

void StrFromFile::printFile(){
	std::ifstream file;
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

string StrFromFile::getModifiedString(const char *key_str, const char *template_str, const char *replace_str, const char *delimiter){
	string result = getString(key_str, delimiter);
	size_t idx;
	while ((idx = result.find(template_str)) != std::string::npos){
		result.replace(idx, std::strlen(template_str), replace_str) ;
	}
	return result;
}

