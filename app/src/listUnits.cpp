/* Файл реализации модуля содержащего классы списка
   подразделений. 
   Имя файла: listUnits.cpp */

#include <iostream>
#include <boost/format.hpp>
#include "str_from_file.hpp"
#include "listUnits.hpp"

//const char *SQL = "SELECT GET_FULL_NAME_UNIT_LEVEL(idUNit, 2, 'i'), GET_FULL_NAME_UNIT_LEVEL(idUNit, -1, 'i')";
const std::string TUnit::templateSQL = StrFromFile("SQL.txt", ":").getString("TUnit");

TUnit::TUnit(){
	data_from_BD = nullptr;
	//file_strings = StrFromFile("SQL.txt", ":");
}

TUnit::TUnit(int _unitId){
	data_from_BD = nullptr;
	unitId = _unitId;
	boost::format fmter(templateSQL);
	//std::cout << fmter%unitId%unitId << std::endl;
	std::stringstream ss;
	ss << fmter%unitId%unitId;
	std::string SQL = ss.str();
	int mysql_status = 0;
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса: " << SQL << std::endl;
	}
	else {
		data_from_BD = mysql_store_result(appParametrs.getDescriptorBD());
		MYSQL_ROW row;
		row = mysql_fetch_row(data_from_BD);
		fullName = row[1];
		shortName = row[0];
	}
}

std::string TUnit::getShortName() const{
	return shortName;
}


std::string TUnit::getFullName() const {
	return fullName;
}

//ListUnits::ListUnits() {}

ListUnits::~ListUnits() {}

//void ListUnits::load() {
ListUnits::ListUnits(){
	int mysql_status = 0;
	const char *SQL = "SELECT idUnit FROM list_staff";
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL);
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса: " << SQL << std::endl;
	}
	MYSQL_RES *result = mysql_store_result(appParametrs.getDescriptorBD());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result))){
		content.push_back(TUnit(boost::lexical_cast<int>(row[0])));
	}
}

ListUnits::iterator ListUnits::getById(int recordId){
	for (ListUnits::iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
	return content.end();
}

ListUnits::const_iterator ListUnits::getById(int recordId) const {
	for (ListUnits::const_iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
	return content.end();
}

ListUnits::const_iterator ListUnits::findRecordId(int recordId){
	return getById(recordId);
}

