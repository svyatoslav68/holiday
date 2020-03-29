/**********************************************************************
***** Реализация класса, подставляющего значение строковых ************
***** переменных из специального файла.                    ************
***** Имя файла - str_from_file.сpp                        ************
**********************************************************************/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/any.hpp>
#include "str_from_file.hpp"

using std::string;
//using string::size_type;

namespace pt = boost::property_tree;

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

ValuesFromXML::ValuesFromXML(const char *_name_file):name_file(string(_name_file)){
	pt::read_xml(name_file, tree);
	boost::property_tree::ptree tree_settings = tree.get_child("FILE.SettingsApplication");
	BOOST_FOREACH(auto param, tree_settings){
		if(param.first=="description") continue;
		//boost::any value = string(param.second);
		//settings_from_file.insert(std::pair<std::string, boost::any>(param.first, value));
		settings_from_file.insert(std::pair<std::string, std::string>(param.first, param.second.get<std::string>("")));
	}
}

void ValuesFromXML::print_settings(){
	using boost::any_cast;
	std::cout << "setting from xml-file " << name_file << std::endl;
	auto it = settings_from_file.cbegin();
	while (it != settings_from_file.cend()){
		//std::cout << it->first << "=" << any_cast<string>(it->second) << std::endl;
		std::cout << it->first << "=" << it->second << std::endl;
		it++;
	}
}

string ValuesFromXML::getStrSQL(const char *part, const char *section, const char *key){
	boost::property_tree::ptree tree_sql = tree.get_child(part);
	string result;
	char str_argument[strlen(section)+strlen(key)+strlen("query")+2];
	strcpy(str_argument, section);
	strcat(str_argument, ".");
	strcat(str_argument, key);
	strcat(str_argument, ".");
	strcat(str_argument, "query");
	//str_argument = new char(100);
	result =  tree_sql.get<string>(str_argument);
	const char * no_space = " \n\t";
	string::size_type idx_first = result.find_first_not_of(no_space); // Первый не пробельный символ строки
	string::size_type idx_last = result.find_last_not_of(no_space);
	result = result.substr(idx_first, idx_last-idx_first+1);
	//delete str_argument;
	return result;
}

string ValuesFromXML::getStrValue(const char *key){
	string result;
	const auto it = settings_from_file.find(key);
	if (it != settings_from_file.cend()){
		result = it->second;
		const char * no_space = " \n\t";
		string::size_type idx_first = result.find_first_not_of(no_space); // Первый не пробельный символ строки
		string::size_type idx_last = result.find_last_not_of(no_space);
		result = result.substr(idx_first, idx_last-idx_first+1);
		return result;
	}
	else {
		std::cerr << "Не найден параметр " << key << std::endl;
		return string("");	
	}
}
int ValuesFromXML::getIntValue(const char *key){
	const auto it = settings_from_file.find(key);
	if (it != settings_from_file.cend()){
		try{
			string result = it->second;
			const char * no_space = " \n\t";
			string::size_type idx_first = result.find_first_not_of(no_space); // Первый не пробельный символ строки
			string::size_type idx_last = result.find_last_not_of(no_space);
			result = result.substr(idx_first, idx_last-idx_first+1);
			return boost::lexical_cast<int>(result);
		}
		catch (...){
			std::cerr << "Не могу преобразовать значения параметра \"" << it->first << "\"" << it->second << " в int\n";
			std::cout << "Продолжить? (Y/n)\n";
			char x;
			std::cin.get(x);
			if (x == 'n')
				exit(1);
			else
				return -1;
		}
	}
	else {
		std::cerr << "Не найден параметр " << key << std::endl;
		return -1;	
	}
}

void ValuesFromXML::putIntValue(const char *key, const int value){
	auto it = settings_from_file.find(key);
	std::ostringstream oss;
	if (it != settings_from_file.end()){
		oss << std::dec << value;
		it->second = oss.str();
	}
	else
		std::cerr << "Не найден параметр " << key << std::endl;
}

void ValuesFromXML::saveSettings(const char *place){
	std::cout << "Состояние settings_from_file перед сохранением:\n";
	BOOST_FOREACH(auto set, settings_from_file){
		std::cout << set.first << " = " << set.second << std::endl;
		char key[strlen(place)+strlen(set.first.c_str())+2];
		strcpy(key, place);
		strcat(key, ".");
		strcat(key, set.first.c_str());
		tree.put(key, set.second);
	}
	pt::write_xml(name_file, tree);
}

