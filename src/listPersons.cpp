#include <iostream>
#include <string>
#include <vector>
#include "listPersons.hpp"
#include <boost/lexical_cast.hpp>

using std::string; 
TPerson::TPerson(){
	data_from_BD = 0;
}

TPerson::TPerson(const TPerson &p){
	dataId = p.dataId;
	family = p.family;
	name = p.name;
	parent = p.parent;
	if (p.data_from_BD){
		data_from_BD = new MYSQL_RES();
		//*data_from_BD = *(p.data_from_BD);
	}
}

TPerson::TPerson(int id){
	data_from_BD = 0;
	dataId = id;
	std::stringstream ss;
	ss << templateCardPersonSQL << id;
	string SQL;
	SQL = ss.str();
	std::cout << "Выполняется запрос :" << SQL << std::endl;
	int mysql_status = 0;
	mysql_status = mysql_query(appParametrs.getDescriptorBD(), SQL.c_str());
	if (mysql_status){
		std::cout << "Ошибка при выполнении запроса: " << SQL << std::endl;
	}
	data_from_BD = mysql_store_result(appParametrs.getDescriptorBD());
	//int num_fields = mysql_num_fields(data_from_BD);
	//if (!num_fields == 1)
	//	std::cout << "Что-то не так. Запрос " << SQL << " вернул не одну запись" << std::endl;
}

TPerson::TPerson(int id, string _family, string _name, string _parent){
	data_from_BD = nullptr;
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
	std::cout << "Данные о сотруднике:" << std::endl;
	MYSQL_ROW row;
	row = mysql_fetch_row(data_from_BD);
	std::cout << "звание: " << row[14] << std::endl;
	std::cout << "фамилия: " << row[1] << std::endl;
}

const char *TPerson::templateCardPersonSQL = "SELECT idPerson, family, name, parent, person_no, sex, birthday, placeborn, payposition, kodunit, field_duty, dopusk, inn, file_image, GET_CURRENT_ACTION(idPerson, 1, 0) as rank_person, GET_CURRENT_ACTION(idPerson, 2, 0) as position_person, GET_CURRENT_ACTION(idPerson, 3, 0) as class_person, GET_FULL_NAME_UNIT_LEVEL(kodunit, -1, 'i') as name_unit FROM main WHERE idPerson = ";

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

