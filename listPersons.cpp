#include <iostream>
#include <string>
#include <vector>
#include "listPersons.hpp"
#include <boost/lexical_cast.hpp>

using std::string; 
TPerson::TPerson(){
}

TPerson::TPerson(int id, string _family, string _name, string _parent){
	dataId = id;
	family = _family;
	name = _name;
	parent = _parent;
}


void ListPersons::load(){
	int mysql_status = 0;
	string SQL = "SELECT idPerson, family, name, parent FROM main";
	mysql_status = mysql_query(&descriptorBD, SQL.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса" << std::endl;
	}
	MYSQL_RES *result = mysql_store_result(&descriptorBD);
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(result);
	while ((row = mysql_fetch_row(result))){
		for(int i = 0; i < num_fields; i++){
			content.push_back(TPerson(boost::lexical_cast<int>(row[0]), row[1], row[2], row[3]));
			//std::cout << row[i] << " : ";
		}
		//std::cout << std::endl;
	}

}

ListPersons::iterator ListPersons::getById(int recordId){
	for (ListPersons::iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
}

ListPersons::const_iterator ListPersons::getById(int recordId) const {
	for (ListPersons::const_iterator iter = content.begin(); iter != content.end(); iter++)
		if (iter->getId() == recordId)
			return iter;
}

ListPersons::const_iterator ListPersons::findRecordId(int recordId){
	return getById(recordId);
}

ListPersons::ListPersons(){
	string name_bd = "unit";
	bd_connect(&descriptorBD, name_bd.c_str());
}

ListPersons::~ListPersons(){

}

