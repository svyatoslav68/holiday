/* Заголовочный файл класса THoliday, представляющего собой
				описание отпуска сотрудника. 
				    файл  tholiday.hpp
***********************************************************/
#ifndef THOLIDAY_HPP
#define THOLIDAY_HPP

#include <vector>
#include <boost/lexical_cast.hpp>
#include "cl_parametrs.hpp"

using bt=boost::gregorian::date;
using namespace boost::gregorian;

extern clParametrs appParametrs;

class THoliday {
public:
	THoliday();
	THoliday(int cod_holiday);
	THoliday(int _cod_person, std::string s_date, int duration, std::string _name_holiday):cod_person(_cod_person), date_begin(from_simple_string(std::string(s_date))), holiday_duration(date_duration(duration)), name_holiday(_name_holiday){};
	void displayHoliday() const;
private:
	const std::string templateSQLHoliday;
	MYSQL_RES *data_from_BD;
	int cod_person;
	bt date_begin;	
	date_duration holiday_duration;
	std::string name_holiday;
};
#endif //THOLIDAY_HPP
