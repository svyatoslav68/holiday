/******************************************************
 *** Файл реализациии класса отвечающего за  **********
 *** разбор параметров командной строки для  **********
 *** запуска приложения. cl_parametrs.сpp    **********
 *****************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "cl_parametrs.hpp"

clParametrs::clParametrs(){
	ops_desc.add_options()
		("unit,u", po::value<int>(), "Persons unit")
		("year,y", po::value<int>(), "Year")
		("help,h", "Show help")
		("save,s", "Save parametrs")
		("version,v", "Show version of application")
	;
	bd_connect(&descriptorBD, name_bd);
}

clParametrs::clParametrs(int argc, char *argv[]){
	ops_desc.add_options()
		("unit,u", po::value<int>(), "Persons unit")
		("year,y", po::value<int>(), "Year")
		("help,h", "Show help")
		("save,s", "Save parametrs")
		("version,v", "Show version of application")
	;
	po::store(po::command_line_parser(argc, argv).options(ops_desc).positional(pos_desc).run(), op_store);
	po::notify(op_store);
	if(op_store.count("help")){
		std::cout << "Помощь по программе:" << std::endl;
		std::cout << ops_desc << std::endl;
		std::exit(0);
	}
	bd_connect(&descriptorBD, name_bd);
}

void clParametrs::loadFromFile(char *_nameFile){
	nameFile = std::string(_nameFile);
}

void clParametrs::setArgs(int argc, char *argv[]){
	po::store(po::command_line_parser(argc, argv).options(ops_desc).positional(pos_desc).run(), op_store);
	po::notify(op_store);
	if(op_store.count("help")){
		std::cout << "Помощь по программе:" << std::endl;
		std::cout << ops_desc << std::endl;
		std::exit(0);
	}
	if(op_store.count("unit"))
		idUnit=op_store["unit"].as<int>();
	if(op_store.count("year"))
		workYear = op_store["year"].as<int>();
	else {
		using bt=boost::gregorian::date;
		bt today = boost::gregorian::day_clock::local_day();
		workYear = today.year();
	}
	if(op_store.count("save")){
	/* Сохраняем значения параметров параметров командной строки в
	конфигурационном файле settings.xml */
	}
}

bool clParametrs::isHelp(){
	return op_store.count("help");
}

bool clParametrs::isVersion(){
	return op_store.count("version");
}

bool clParametrs::isSave(){
	return op_store.count("save");
}

MYSQL *clParametrs::getDescriptorBD(){
/*Нужно перед возвращение дескриптора проверить, указывает ли он 
на реально подключенную базу данных. Если нет, то выдавать исключение.*/
	return &descriptorBD;
}
