/******************************************************
 *** Файл реализациии класса отвечающего за  **********
 *** разбор параметров командной строки для  **********
 *** запуска приложения. cl_parametrs.сpp    **********
 *****************************************************/

#include <iostream>
#include "cl_parametrs.hpp"

clParametrs::clParametrs(int argc, char *argv[]){
	ops_desc.add_options()
		("help,h", "Show help")
		("version,v", "Show version of application")
	;
	po::store(po::command_line_parser(argc, argv).options(ops_desc).positional(pos_desc).run(), op_store);
	po::notify(op_store);
	if(op_store.count("help")){
		std::cout << "Помощь по программе:" << std::endl;
		std::cout << ops_desc << std::endl;
	}
	bd_connect(&descriptorBD, name_bd);
}

bool clParametrs::isHelp(){
	return op_store.count("help");
}

bool clParametrs::isVersion(){
	return op_store.count("version");
}

MYSQL *clParametrs::getDescriptorBD(){
/*Нужно перед возвращение дескриптора проверить, указывает ли он 
на реально подключенную базу данных. Если нет, то выдавать исключение.*/
	return &descriptorBD;
}
