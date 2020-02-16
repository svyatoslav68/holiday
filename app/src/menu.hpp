#ifndef MENU_HPP
#define MENU_HPP
/*****************************************************
 *****        Заголовок модуля меню 		  ********
 *****             menu.hpp                   ********
 ****************************************************/
#include "listUnits.hpp"
#include "unitsDisplayList.hpp"

class Menu {
// Виртуальный класс, предок всех меню
public:
	Menu();
	~Menu();
	// Основной цикл меню
	virtual void mainLoop() = 0;
	// Возвращаем текущее меню
	static Menu *activeMenu();
	// Помещение меню на вершину стека
	static void enterMenu(Menu *);
	// Выход из меню. Подвигаем стек вверх. 
	static void exitMenu();
	// True, если на вершине стека есть меню
	static bool isActive();
protected:
	static int getMenuSelection(const std::string& menu);
	static uint8_t getMenuSelection(const std::string& menu, const string& choices);
	static void clearScreen();
private:
	// Статический член класса
	static std::stack<Menu *> menuStack;
};

class MainMenu : public Menu{
public:
	MainMenu();
	MainMenu(Menu *_personMenu, Menu *_graphicMenu, Menu *_settingsMenu);
	//void setPersonMenu(Menu *_personMenu) {personMenu = _personMenu;}
	void mainLoop();
private:
	void persons();
	void graphic();
	void settings();
	void quit();
	Menu *personMenu;
	Menu *graphicMenu;
	Menu *settingsMenu;
};

class PersonMenu : public Menu{
public:
	PersonMenu(Menu *_listPersonsMenu);
	void mainLoop();
private:
	void manualControl();
	void orderPerson();
	void quit();
	Menu *listPersonsMenu;
};	

class ProcessingUnitMenu:public Menu{
public:
	ProcessingUnitMenu() {}
	void mainLoop();
private:
	const int idUnit = -1;
	void quit();
};

class SelectUnitMenu : public Menu {
public:
	SelectUnitMenu(ListUnits &listUnits_):listUnits(listUnits_),displayList(listUnits_) { }
	void mainLoop();
private:
	ListUnits &listUnits;
	UnitsDisplayList displayList;
	ProcessingUnitMenu *unitMenu;
	void selectUnit(uint8_t);
	void quit();
};

class GraphicMenu :public Menu {
public:
	GraphicMenu();
	void mainLoop();
private:
	void quit();
};


class ProcessingPersonMenu:public Menu{
public:
	ProcessingPersonMenu(){idPerson = -1;};
	void mainLoop();
	void setIdPerson(int id);
private:
	int idPerson;
	void addPlanHoliday();
	void editPlanHoliday(int numItem);
	void quit();
};

class ListPersonsMenu:public Menu {
public:
	ListPersonsMenu(ListPersons &_listPersons, ProcessingPersonMenu *_pMenu);
	void mainLoop();
private:
	void selectPerson(uint8_t number);
	void quit();
	ListPersons &listPersons;
	PersonsDisplayList displayList;
	ProcessingPersonMenu *personMenu;
};

class SettingsMenu:public Menu {
public:
	SettingsMenu(Menu *_selectUnitMenu):selectUnitMenu(_selectUnitMenu){};
	void mainLoop();
private:
	void selectUnit();
	void quit();
	Menu *selectUnitMenu;
};

#endif //MENU_HPP
