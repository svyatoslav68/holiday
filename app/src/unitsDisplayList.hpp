/***************************************************************
 ******     Класс для отображения списка подразделений *********
 ******            файл unitsDisplayList.hpp         ***********
 **************************************************************/
#ifndef UNITSDISPLAYLIST_HPP
#define UNITSDISPLAYLIST_HPP

#include "listUnits.hpp"
#include "displayList.hpp"

class UnitsDisplayList: public DisplayList {
public:
	UnitsDisplayList(ListUnits &listUnits_):listUnits(listUnits_) {}
private:
	ListUnits &listUnits;
protected:
	virtual void displayRecord(int recordId);
	//virtual void displayCard(int record_id);
	virtual bool fetchMore(int startId, int numRecords, std::vector<int> &result);
};

#endif // UNITSDISPLAYLIST_HPP
