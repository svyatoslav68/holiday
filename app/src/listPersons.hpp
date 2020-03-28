#ifndef LISTPERSONS_HPP
#define LISTPERSONS_HPP
#include "cl_parametrs.hpp"

extern clParametrs appParametrs;

class TPerson {

public:
	TPerson();
	TPerson(const TPerson &p);
	TPerson(int id);
	TPerson(int id, std::string _family, std::string _name, std::string _parent);
	int getId() const {return dataId;}
	void displayCard();
	std::string getFamilyIO() const;
private:
	const std::string templateCardPersonSQL;
	MYSQL_RES *data_from_BD;
	int dataId;		// Идентификатор записи о сотруднике в БД
	std::string family;
	std::string name;
	std::string parent;
};

class ListPersons {
private:
	typedef std::vector<TPerson> TContent; //Тип содержимого списка персонала
public:
	typedef TContent::const_iterator const_iterator;
	typedef TContent::iterator iterator;
	ListPersons();
	~ListPersons();
	void load(int idUnit);	
	const_iterator begin() const {return content.begin();}
	const_iterator end() const {return content.end();}
	const_iterator findRecordId(int recordId);
private:
	TContent content;
	iterator getById(int recordId);
	const_iterator getById(int recordId) const;
};
#endif //LISTPERSONS_HPP
