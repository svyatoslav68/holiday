/** Заголовочный файл модуля объектов доступа к SQL-серверу***
***				data_from_sql.hpp                       ******
*************************************************************/
#ifndef DATA_FROM_SQL_HPP
#define DATA_FROM_SQL_HPP

#include <map>
class THoliday;

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
	static const std::string SQL_load;
	typedef std::map<int, std::pair<std::string, std::string>> tcontent;
	tcontent content_map;
};

class ListHolidays{
/* Класс содержит список отпусков сотрудника, предоставляет
функции-члены для работы с отпусками */
public:
	ListHolidays(int idPerson);
	void load();
	void printContent(); // Вывод на печать содержимого
private:
	static const std::string SQL_holidays;
	typedef std::vector<THoliday> tcontent;
	tcontent content;
	int id_person; // Идентификатор сотрудника, отпуска которого содержатся в content
};
#endif //DATA_FROM_SQL_HPP
