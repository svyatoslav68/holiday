/************************************************************
****** Реализация класса отображения списка подразделений ***
******         файл unitsDisplayList.cpp                  ***
************************************************************/
#include <iostream>
#include <vector>
#include "unitsDisplayList.hpp"

void UnitsDisplayList::displayRecord(int record_id){
	auto it = listUnits.findRecordId(record_id);
	std::cout << it->getShortName();
}

bool UnitsDisplayList::fetchMore(int startId, int numRecords, std::vector<int> &result){
	result.clear();
	if (numRecords == 0) 
		return false;
	bool forwards = true; //Переменная имеет значение true, если нужно возвращать записи дальше startId, и false, если нужно возвращать записи до startId
	if (numRecords < 0){
		forwards = false;
		numRecords = -numRecords;
	}
	if (listUnits.begin() == listUnits.end()){
		return true;
	}
	ListUnits::const_iterator iter;
	if (startId == 0)
		iter = (forwards ? listUnits.begin() : listUnits.end());
	else {
		iter = listUnits.findRecordId(startId);
		if (forwards)
			++iter;
	}
	if (forwards) {
		while (iter != listUnits.end() && numRecords-- > 0)
			result.push_back((iter++)->getId());
		return iter == listUnits.end();
	}
	else {
		while (iter != listUnits.begin() && numRecords-- > 0)
			result.push_back((--iter)->getId());
		std::reverse(result.begin(), result.end());
		return iter == listUnits.begin();
	}
	return true;
}

