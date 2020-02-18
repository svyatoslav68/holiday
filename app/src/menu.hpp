#ifndef MENU_HPP
#define MENU_HPP
/*****************************************************
 *****        Заголовок модуля меню 		  ********
 *****             menu.hpp                   ********
 ****************************************************/
#include "unitsDisplayList.hpp" 
#include "personsDisplayList.hpp"

class ListPersons;
class ListUnits;
class PersonsDisplayList;

#include "parent_menu.hpp"

class MainMenu : public Menu{
public:
	MainMenu();
	MainMenu(Menu *_personMenu, Menu *_graphicMenu, Menu *_settingsMenu);
	//void setPersonMenu(Menu *_personMenu) {personMenu = _personMenu;}
	~MainMenu();
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
	PersonMenu();
	PersonMenu(Menu *_listPersonsMenu);
	~PersonMenu();
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
	SelectUnitMenu();//ListUnits &listUnits_):listUnits(listUnits_),displayList(listUnits_) { }
	~SelectUnitMenu();
	void mainLoop();
private:
	ListUnits listUnits;
	UnitsDisplayList *displayList;
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
	~ProcessingPersonMenu();
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
	ListPersonsMenu(ListPersons &_listPersons);
	ListPersonsMenu(ListPersons &_listPersons, ProcessingPersonMenu *_pMenu);
	~ListPersonsMenu();
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
	SettingsMenu();
	SettingsMenu(Menu *_selectUnitMenu):selectUnitMenu(_selectUnitMenu){};
	~SettingsMenu();
	void mainLoop();
private:
	void selectUnit();
	void quit();
	Menu *selectUnitMenu;
};

#endif //MENU_HPP
