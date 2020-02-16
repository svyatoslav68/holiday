#ifndef LISTPERSONS_HPP
#define LISTPERSONS_HPP
#include "cl_parametrs.hpp"

using std::string; 

extern clParametrs appParametrs;

class TPerson {
private:
	int dataId;		// Идентификатор записи о сотруднике в БД
	string family;
	string name;
	string parent;
	MYSQL_RES *data_from_BD;
public:
	static const char *templateCardPersonSQL;
	TPerson();
	TPerson(const TPerson &p);
	TPerson(int id);
	TPerson(int id, string _family, string _name, string _parent);
	int getId() const {return dataId;}
	void displayCard();
	string getFamilyIO() const;
};

class ListPersons {
private:
	typedef std::vector<TPerson> TContent; //Тип содержимого списка персонала
public:
	typedef TContent::const_iterator const_iterator;
	typedef TContent::iterator iterator;
	ListPersons();
	~ListPersons();
	void load();	
	const_iterator begin() const {return content.begin();}
	const_iterator end() const {return content.end();}
	const_iterator findRecordId(int recordId);
private:
	TContent content;
	iterator getById(int recordId);
	const_iterator getById(int recordId) const;
};
#endif //LISTPERSONS_HPP
