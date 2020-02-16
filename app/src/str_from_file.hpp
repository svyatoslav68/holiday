/**********************************************************************
***** Определение класса подставляющего значение строковых ************
***** переменных из специального файла.                    ************
***** Имя файла - str_from_file.hpp                        ************
**********************************************************************/
#ifndef STR_FROM_FILE_HPP
#define STR_FROM_FILE_HPP

#include <fstream>
#include <string>

using std::string;

class StrFromFile {
public:
	StrFromFile(const char *_delimiter);
	StrFromFile(const char *_name_file, const char *_delimiter);
	bool setNameFile(const char *_name_file);
	string getString(const char *key_str, const char *delimiter_str = ":");
	string getModifiedString(const char *key_str, const char *template_str, const char *replace_str, const char *delimiter = ":");
// Функции тестирования
	void printFile();
	class StrNoFound{}; // Исключение вырабатывается, когда строка не найдена в файле
	class FileNoFound{};// Исключение вырабатывается, когда файл не найден
private:
	StrFromFile();
	string delimiter;
	string name_file;
	//std::ifstream file;
};

#endif //STR_FROM_FILE_HPP
