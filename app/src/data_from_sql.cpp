/*** Файл реализации модуля объектов доступа к SQL-серверу******
****				data_from_sql.cpp                       ****
***************************************************************/

#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "cl_parametrs.hpp"
#include "data_from_sql.hpp"
#include "str_from_file.hpp"
#include "tholiday.hpp"

extern clParametrs appParametrs;
const std::string TypesHoliday::SQL_load = StrFromFile("SQL.txt", ":").getString("loadTypes");

TypesHoliday::TypesHoliday(){
}

void TypesHoliday::load(){
	int mysql_status = 0;
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL_load.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса: " << SQL_load << std::endl;
		return;
	}
	MYSQL_RES *result = mysql_store_result(appParametrs.getDescriptorBD());
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(result);
	while ((row = mysql_fetch_row(result))){
		content_map[boost::lexical_cast<int>(row[0])]=std::make_pair(row[1], row[2]);
		/*for(int i = 0; i < num_fields; i++){
			//std::cout << row[i] << " : ";
		}*/
		//std::cout << std::endl;
	}
}

std::string TypesHoliday::operator[](int i){
/* Возвращает название типа отпуска в именительном падеже,
соответствующее коду типа в квадратных скобках */
	if (content_map.empty())
		throw NoIndex();
	auto it = content_map.find(i);
	if (it == content_map.end())
		throw NoIndex();
	return it->second.first;
}

std::string TypesHoliday::getNameType(int i, uint8_t padeg = 'i'){
	if (content_map.empty())
		throw NoIndex();
	auto it = content_map.find(i);
	if (it == content_map.end())
		throw NoIndex();
	if (padeg == 'r')
		return it->second.second;
	else
		return it->second.first;
}

void TypesHoliday::printContent(){
	auto it = content_map.cbegin();
	while(it != content_map.cend()){
		std::cout << it->first << ':' << it->second.first << ',' << it->second.second << ";\n"; 
		it++;
	}
}

const std::string ListHolidays::SQL_holidays = StrFromFile("SQL.txt", ":").getString("loadHolidays");
ListHolidays::ListHolidays(int idPerson){

}

void ListHolidays::load(){

}

void ListHolidays::printContent(){
	uint8_t display_number = 0; 
	auto it = content.cbegin();
	while (it != content.cend()){
		display_number++;
		it++;
	}

}

