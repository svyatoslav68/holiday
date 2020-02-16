/** Заголовочный файл модуля объектов доступа к SQL-серверу***
***				data_from_sql.hpp                       ******
*************************************************************/
#ifndef DATA_FROM_SQL_HPP
#define DATA_FROM_SQL_HPP

#include <map>

class TypesHoliday {
/* Класс предоставляет интерфейс получения типов отпусков.
Переопределенный оператор '[]' возвращает название типа в 
именительном или родительном падеже.*/

public:
	class NoIndex {}; //Класс исключения. Вызывается, когда не находится тип отпуска, соотвествующий заданному коду
	TypesHoliday();
	void load();
	std::string operator[](int i);
	std::string getNameType(int i, uint8_t padeg);
	void printContent();
private:
	typedef std::map<int, std::pair<std::string, std::string>> tcontent;
	tcontent content_map;
};

#endif //DATA_FROM_SQL_HPP
