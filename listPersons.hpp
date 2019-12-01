#ifndef LISTPERSONS_HPP
#define LISTPERSONS_HPP
extern "C"{
#include "mysql_connect.h"
}
using std::string; 

class TPerson {
private:
	int dataId;		// Идентификатор записи о сотруднике в БД
	string family;
	string name;
	string parent;
public:
	TPerson();
	TPerson(int id, string _family, string _name, string _parent);
	int getId() const {return dataId;}
	string getFamilyIO() const;
};

class ListPersons {
private:
	typedef std::vector<TPerson> tcontent; //Тип содержимого списка персонала
public:
	typedef tcontent::const_iterator const_iterator;
	typedef tcontent::iterator iterator;
	ListPersons();
	~ListPersons();
	void load();	
	const_iterator begin() const {return content.begin();}
	const_iterator end() const {return content.end();}
	const_iterator findRecordId(int recordId);
private:
	tcontent content;
	MYSQL descriptorBD;
	iterator getById(int recordId);
	const_iterator getById(int recordId) const;
};
#endif //LISTPERSONS_HPP
