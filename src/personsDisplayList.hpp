/***************************************************************
 ******     Класс для отображения списка сотрудников ***********
 ******            файл personsDisplayList.hpp       ***********
 **************************************************************/

#ifndef PERSONSDISPLAYLIST_HPP
#define PERSONSDISPLAYLIST_HPP

#include "listPersons.hpp"
#include "displayList.hpp"

class PersonsDisplayList: public DisplayList {
public:
	//PersonsDisplayList();
	PersonsDisplayList(ListPersons &listPersons_);
	void listAll();
protected:
	virtual void displayRecord(int recordId);
	virtual bool fetchMore(int startId, int numRecords, std::vector<int> &result);
private:
	ListPersons &listPersons;
};

#endif //PERSONSDISPLAYLIST_HPP
