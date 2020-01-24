/* Файл реализации модуля содержащего классы списка
   подразделений. 
   Имя файла: listUnits.cpp */

#include <iostream>
#include "listUnits.hpp"

TUnit::TUnit(){
	data_from_BD = nullptr;
}

TUnit::TUnit(int _unitId){
	data_from_BD = nullptr;
	unitId = _unitId;
}

std::string TUnit::getShortName(){
	return "";
}

const char *SQL = "GET_FULL_NAME_UNIT_LEVEL(idUNit, -1, 'i')";

std::string TUnit::getFullName(){
	return "";
}

ListUnits::ListUnits() {}

ListUnits::~ListUnits() {}

void ListUnits::load() {
	int mysql_status = 0;
	const char *SQL = "SELECT idUnit FROM list_stuff";
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL);
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса" << std::endl;
	}
	MYSQL_RES *result = mysql_store_result(appParametrs.getDescriptorBD());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result))){
		content.push_back(TUnit(boost::lexical_cast<int>(row[0])));
	}
}

