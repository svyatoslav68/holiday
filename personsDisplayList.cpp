#include <iostream>
#include <vector>
#include "listPersons.hpp"
#include "personsDisplayList.hpp"

/*personsDisplayList::personsDisplayList(){
	listPersons = 
}*/

PersonsDisplayList::PersonsDisplayList(ListPersons &listPersons_):listPersons(listPersons_){ }

<<<<<<< HEAD
void PersonsDisplayList::listAll(){
	toStart();
}

=======
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
void PersonsDisplayList::displayRecord(int recordId){

}

bool PersonsDisplayList::fetchMore(int startId, int numRecords, std::vector<int> &result){
<<<<<<< HEAD
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

=======
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
	return true;
}


