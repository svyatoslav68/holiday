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

string TPerson::getFamilyIO() const{
	return family + " " + name;
}

void TPerson::displayCard(){
	//ListPersons::const_iterator it = listPersons.findRecordId(recordId);
	//MYSQL descriptorBD = listPersons.getDescriptorBD();
	char cardPersonSQL[strlen(templateCardPersonSQL)+10];
	sprintf(cardPersonSQL, templateCardPersonSQL, getId());
	std::cout << "SQL =" << cardPersonSQL << std::endl;
}

const char *TPerson::templateCardPersonSQL = "SELECT idPerson, family, name, parent, person_no, sex, birthday, placeborn, payposition, kodunit, field_duty, dopusk, inn, file_image, GET_CURRENT_ACTION(idPerson, 1, 0) as rank_person, GET_CURRENT_ACTION(idPerson, 2, 0) as position_person, GET_CURRENT_ACTION(idPerson, 3, 0) as class_person, GET_FULL_NAME_UNIT_LEVEL(kodunit, -1, 'i') as name_unit FROM main WHERE idPerson = %s";

void ListPersons::load(){
	int mysql_status = 0;
	string SQL = "SELECT idPerson, family, name, parent FROM main";
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса" << std::endl;
	}
	MYSQL_RES *result = mysql_store_result(appParametrs.getDescriptorBD());
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(result);
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

