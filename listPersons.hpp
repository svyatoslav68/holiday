#ifndef LISTPERSONS_HPP
#define LISTPERSONS_HPP
<<<<<<< HEAD
extern "C"{
#include "mysql_connect.h"
}
=======
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
using std::string; 

class TPerson {
private:
<<<<<<< HEAD
	int dataId;		// Идентификатор записи о сотруднике в БД
=======
	int dataID;		// Идентификатор записи о сотруднике в БД
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
	string family;
	string name;
	string parent;
public:
	TPerson();
<<<<<<< HEAD
	TPerson(int id, string _family, string _name, string _parent);
	int getId() const {return dataId;}
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
=======
	void load();	
	void save();
};

class ListPersons {
public:
	ListPersons();
private:
	std::vector<TPerson> contain;
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
};
#endif //LISTPERSONS_HPP
