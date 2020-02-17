/*Заголовочный файл реализации классов TUnit, ListUnits.
*********** listUnits.hpp ********************************
**********************************************************/
#ifndef TUNIT_HPP
#define TUNIT_HPP
#include "cl_parametrs.hpp"

extern clParametrs appParametrs;

class TUnit {
public:
	TUnit();
	TUnit(int);
	int getId() const {return unitId;}
	std::string getFullName() const;
	std::string getShortName() const;
	class RowNoFound {}; // Исключение вызывается, когда не найдена запись о unit
private:
	std::string shortName;
	std::string fullName;
	static const std::string templateSQL;
	int unitId;
	MYSQL_RES *data_from_BD;
};

class ListUnits {
private:
	typedef std::vector<TUnit> TContent;
public:
	ListUnits();
	~ListUnits();
	typedef TContent::iterator iterator;
	typedef TContent::const_iterator const_iterator;
	//void load();
	const_iterator begin() const {return content.begin();}
	const_iterator end() const {return content.end();}
	const_iterator findRecordId(int recordId);
private:
	TContent content;
	iterator getById(int recordId);
	const_iterator getById(int recordId) const;
};

#endif //TUNIT_HPP
