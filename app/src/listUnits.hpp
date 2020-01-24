/* Заголовочный файл модуля описывающего классы, 
   необходимые для построения списка подразделений.
   Модуль содержит класс описания подразделения и 
   класс списка описаний подразделений.            */
#ifndef LIST_UNITS_HPP
#define LIST_UNITS_HPP

#include "cl_parametrs.hpp"
#include <string>

extern clParametrs appParametrs;

class TUnit {
public:
	TUnit();
	TUnit(int _unitId);
	std::string getShortName();
	std::string getFullName();
	const static char *SQL;
private:
	MYSQL_RES *data_from_BD;
	int unitId;
};

class ListUnits {
private:
	typedef std::vector<TUnit> TContent; // Тип контейнера содержимого
public:
	typedef TContent::iterator iterator;
	typedef TContent::const_iterator const_iterator;
	ListUnits();
	~ListUnits();
	void load();
	const_iterator begin() const {return content.begin();}
	const_iterator end() const {return content.end();}
private:
	TContent content;
};


#endif //LIST_UNITS_HPP
