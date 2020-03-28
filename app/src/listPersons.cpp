#include <iostream>
#include <string>
#include <vector>
#include "str_from_file.hpp"
#include "listPersons.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

using std::string; 

//const string TPerson::templateCardPersonSQL = StrFromFile("SQL.txt", ":").getString("getDataPerson");
//const string TPerson::templateCardPersonSQL = ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "TPerson", "getDataPerson");

TPerson::TPerson():templateCardPersonSQL(ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "TPerson", "getDataPerson")){
	data_from_BD = nullptr;
}

TPerson::TPerson(const TPerson &p):templateCardPersonSQL(ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "TPerson", "getDataPerson")),data_from_BD(nullptr){
	dataId = p.dataId;
	family = p.family;
	name = p.name;
	parent = p.parent;
	if (p.data_from_BD){
		data_from_BD = new MYSQL_RES();
		//*data_from_BD = *(p.data_from_BD);
	}
}

TPerson::TPerson(int id):templateCardPersonSQL(ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "TPerson", "getDataPerson")),data_from_BD(nullptr),dataId(id){
	std::stringstream ss;
	try{
	boost::format fmter(templateCardPersonSQL);
	ss << fmter%id;
	}
	catch (...){
		std::cout << "From listPersons TPerson()\n";
	}
	string SQL = ss.str();
	SQL = ss.str();
	//std::cout << "Выполняется запрос :" << SQL << std::endl;
	int mysql_status = 0;
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса: " << SQL << std::endl;
	}
	else
		data_from_BD = mysql_store_result(appParametrs.getDescriptorBD());
}

TPerson::TPerson(int id, string _family, string _name, string _parent):templateCardPersonSQL(ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "TPerson", "getDataPerson")),data_from_BD(nullptr),dataId(id){
	family = _family;
	name = _name;
	parent = _parent;
}

string TPerson::getFamilyIO() const{
	return family + " " + name;
}

void TPerson::displayCard(){
	//ListPersons::const_iterator it = listPersons.findRecordId(recordId);
	//MYSQL descriptorBD = listPersons.getDescriptorBD();
	/*char cardPersonSQL[strlen(templateCardPersonSQL)+10];
	sprintf(cardPersonSQL, templateCardPersonSQL, getId());
	std::cout << "SQL =" << cardPersonSQL << std::endl;*/
	if (!data_from_BD)
		return;
	std::cout << "Данные о сотруднике:" << std::endl;
	MYSQL_ROW row;
	row = mysql_fetch_row(data_from_BD);
	std::cout << "звание: " << row[14] << std::endl;
	std::cout << "фамилия: " << row[1] << std::endl;
}


void ListPersons::load(int idUnit){
	content.clear();
	int mysql_status = 0;
	//const string templateSQL = StrFromFile("SQL.txt", ":").getString("getListPersons");
	const string templateSQL = ValuesFromXML(appParametrs.getNameConfFile().c_str()).getStrSQL("FILE.SQL", "ListPerson", "getListPersonsUnit");
	try {
	boost::format fmter(templateSQL);
	std::stringstream ss;
	ss << fmter%idUnit;
	std::string SQL = ss.str();
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL.c_str());
	}
	catch (...){
		std::cout << "listPersons.cpp ListPersons\n";
	}
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса" << std::endl;
	}
	MYSQL_RES *result = mysql_store_result(appParametrs.getDescriptorBD());
	MYSQL_ROW row;
	//int num_fields = mysql_num_fields(result);
	while ((row = mysql_fetch_row(result))){
		content.push_back(TPerson(boost::lexical_cast<int>(row[0]), row[1], row[2], row[3]));
		/*for(int i = 0; i < num_fields; i++){
			//std::cout << row[i] << " : ";
		}*/
		//std::cout << std::endl;
	}
}

ListPersons::iterator ListPersons::getById(int recordId){
	for (ListPersons::iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
	return content.end();
}

ListPersons::const_iterator ListPersons::getById(int recordId) const {
	for (ListPersons::const_iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
	return content.end();
}

ListPersons::const_iterator ListPersons::findRecordId(int recordId){
	return getById(recordId);
}

ListPersons::ListPersons(){
}


ListPersons::~ListPersons(){

}

