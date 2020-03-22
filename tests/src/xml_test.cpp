#include<iostream>
#include "str_from_file.hpp"

int main(){
	ValuesFromXML xml_settings("settings.xml");
	xml_settings.print_settings();
	std::cout << "SQL = " << xml_settings.getStrValue("THoliday", "getPersonHolidays") << std::endl; 
	std::cout << "Year = " << xml_settings.getIntValue("year") << std::endl;
	return 0;	
}

