/* Тест для уяснение того, как в точности работают классы потомки DisplayList.
   Здесь будем создавать эти классы и выводить на экран результаты работы 
   методов класса. */

#include <iostream>
#include "personsDisplayList.hpp"
#include "unitsDisplayList.hpp"
extern "C"{
#include "mysql_connect.h"
}

clParametrs appParametrs; // Параметры приложения - глобальная переменная

template<class T>
void printContent(T container){
	auto it = container.cbegin();
	while (it != container.cend()){
		std::cout << *it << ' ';
		++it;
	}
	std::cout << std::endl;
}

int main(int argc, char **argv){
	//ListPersons lstItems;
	ListUnits lstItems;
	//lstItems.load();
	//PersonsDisplayList plist(lstItems);
	UnitsDisplayList plist(lstItems);
	plist.display();
	plist.printAll();
	std::vector<int> fromList;// = {111, 666, -234};
	plist.executeFetchMore(101, -5, fromList);
	//std::list<double> lsDouble = {2.123, 23,19, 34.02, 56.389};
	printContent(fromList);
	//printContent(lsDouble);
	/*plist.pageDown();
	plist.display();
	plist.printAll();*/
	plist.pageUp();
	plist.display();
	plist.printAll();
	return 0;
}

