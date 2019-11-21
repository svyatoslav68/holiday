#ifndef LISTPERSONS_HPP
#define LISTPERSONS_HPP
using std::string; 

class TPerson {
private:
	int dataID;		// Идентификатор записи о сотруднике в БД
	string family;
	string name;
	string parent;
public:
	TPerson();
	void load();	
	void save();
};

class ListPersons {
public:
	ListPersons();
private:
	std::vector<TPerson> contain;
};
#endif //LISTPERSONS_HPP
