/******************************************************
 *** Заголовочный файл класса отвечающего за **********
 *** разбор параметров командной строки для  **********
 *** запуска приложения. cl_parametrs.hpp    **********
 *****************************************************/
#ifndef CL_PARAMETRS_HPP
#define CL_PARAMETRS_HPP

extern "C"{
#include "mysql_connect.h"
}
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class clParametrs{
public:
	const char *name_bd = "unit";
	clParametrs();
	clParametrs(int argc, char *argv[]);
	void setArgs(int argc, char *argv[]);
	bool isHelp();
	bool isVersion();
	MYSQL *getDescriptorBD();
private:
	MYSQL descriptorBD;		// Дескриптор базы данных
	po::options_description ops_desc; // Options description (Описание опций)
	po::positional_options_description pos_desc; // Positional options description
	po::variables_map op_store;		// Container for store received options
};
#endif //CL_PARAMETRS_HPP
