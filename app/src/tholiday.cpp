/* Файл реализации класса THoliday, представляющего собой
				описание отпуска сотрудника. 
				    файл  tholiday.cpp
***********************************************************/
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "tholiday.hpp"
#include "str_from_file.hpp"

const std::string THoliday::templateSQLHoliday=StrFromFile("SQL.txt", ":").getString("getHoliday");

THoliday::THoliday(){

}

THoliday::THoliday(int cod_holiday){
	data_from_BD = nullptr;
	boost::format fmter(templateSQLHoliday);
	std::stringstream ss;
	ss << fmter%cod_holiday;
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
		name_holiday = row[1];
		cod_person = boost::lexical_cast<int>(row[2]);		
		date_begin = from_simple_string(std::string(row[3]));
		holiday_duration = date_duration(boost::lexical_cast<int>(row[4])+boost::lexical_cast<int>(row[5]));
	}
}
