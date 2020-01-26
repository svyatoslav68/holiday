#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "listPersons.hpp"
#include "personsDisplayList.hpp"
extern "C"{
#include <mysql.h>
}
#include <cstring>

/*personsDisplayList::personsDisplayList(){
	listPersons = 
}*/

PersonsDisplayList::PersonsDisplayList(ListPersons &listPersons_):listPersons(listPersons_){ }

void PersonsDisplayList::listAll(){
	toStart();
}

void PersonsDisplayList::displayRecord(int recordId){
	ListPersons::const_iterator it = listPersons.findRecordId(recordId);
	std::cout << std::setw(5) << std::setfill(' ') <<  std::right << std::dec << it->getId() << ". ";
	std::cout << it->getFamilyIO();
}

bool PersonsDisplayList::fetchMore(int startId, int numRecords, std::vector<int> &result){
/* Возвратить порцию данных из содержимого (listPersons). 
	- startId - позиция, начиная с которой возвращать данные;
	- numRecords - количество возвращаемых данных, если отрицательное, то данные брать до startId;
	- result - ссылка на вектор, в котором будут возвращаемые данные */
	result.clear();
	if (numRecords == 0) 
		return false;
	bool forwards = true; //Переменная имеет значение true, если нужно возвращать записи дальше startId, и false, если нужно возвращать записи до startId
	if (numRecords < 0){
		forwards = false;
		numRecords = -numRecords;
	}
	if (listPersons.begin() == listPersons.end()){
		/* Если список содержимого пуст, то возвращаем true и 
		пустой вектор result */
		return true;
	}
	ListPersons::const_iterator iter;	// Итератор по содержимому списка
	if (startId == 0)
		iter = (forwards ? listPersons.begin() : listPersons.end());
	else {
		iter = listPersons.findRecordId(startId);
		if (forwards)
			++iter;
	}
	if (forwards) {
		while (iter != listPersons.end() && numRecords-- >0)
			result.push_back((iter++)->getId());
		return iter == listPersons.end();
	}
	else {
		while (iter != listPersons.begin() && numRecords-- >0)
			result.push_back((--iter)->getId());
		std::reverse(result.begin(), result.end());
		return iter == listPersons.begin();
	}
	return true;
}
