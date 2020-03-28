/**********************************************************************
***** Определение класса подставляющего значение строковых ************
***** переменных из специального файла.                    ************
***** Имя файла - str_from_file.hpp                        ************
**********************************************************************/
#ifndef STR_FROM_FILE_HPP
#define STR_FROM_FILE_HPP

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <boost/any.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class StrFromFile {
public:
	StrFromFile(const char *_delimiter);
	StrFromFile(const char *_name_file, const char *_delimiter);
	bool setNameFile(const char *_name_file);
	std::string getString(const char *key_str, const char *delimiter_str = ":");
	std::string getModifiedString(const char *key_str, const char *template_str, const char *replace_str, const char *delimiter = ":");
// Функции тестирования
	void printFile();
	class StrNoFound{}; // Исключение вырабатывается, когда строка не найдена в файле
	class FileNoFound{};// Исключение вырабатывается, когда файл не найден
private:
	StrFromFile();
	std::string delimiter;
	std::string name_file;
	//std::ifstream file;
};

class ValuesFromXML {
public:
	ValuesFromXML(const char *_name_file);
	std::string getStrSQL(const char *part, const char *section, const char *key);
	std::string getStrValue(const char *key);
	int getIntValue(const char *key);
	void putIntValue(const char *key, const int value);
	void saveSettings(const char *place);
	void print_settings();
private:
	ValuesFromXML();
	boost::property_tree::ptree tree; 
	//std::map<std::string, boost::any> settings_from_file;
	std::map<std::string, std::string> settings_from_file;
	std::string name_file;
};

#endif //STR_FROM_FILE_HPP
