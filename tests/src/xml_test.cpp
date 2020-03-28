#include<iostream>
#include "str_from_file.hpp"

int main(){
	ValuesFromXML xml_settings("settings.xml");
	xml_settings.print_settings();
	std::cout << "SQL = " << xml_settings.getStrSQL("FILE.SQL", "THoliday", "getPersonHolidays") << std::endl; 
	std::cout << "Считано из settings.xml:\n";
	std::cout << "Year = " << xml_settings.getIntValue("year") << std::endl;
	std::cout << "Unit = " << xml_settings.getIntValue("unit") << std::endl;
	xml_settings.putIntValue("unit", 20);
	xml_settings.putIntValue("year", 2030);
	xml_settings.saveSettings("FILE.SettingsApplication");
	return 0;	
}

