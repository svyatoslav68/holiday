/***************************************************************
 ******     Класс для отображения списка подразделений *********
 ******            файл unitsDisplayList.hpp         ***********
 **************************************************************/
#ifndef UNITSDISPLAYLIST_HPP
#define UNITSDISPLAYLIST_HPP

#include "listUnits.hpp"
#include "displayList.hpp"

class UnitsDisplayList: public DisplayList {
private:
	ListUnits &listUnits;
};

#endif // UNITSDISPLAYLIST_HPP
