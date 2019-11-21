#include <iostream>
#include <vector>
#include "listPersons.hpp"
#include "personsDisplayList.hpp"

/*personsDisplayList::personsDisplayList(){
	listPersons = 
}*/

PersonsDisplayList::PersonsDisplayList(ListPersons &listPersons_):listPersons(listPersons_){ }

void PersonsDisplayList::displayRecord(int recordId){

}

bool PersonsDisplayList::fetchMore(int startId, int numRecords, std::vector<int> &result){
	return true;
}


