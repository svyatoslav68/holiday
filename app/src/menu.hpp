#ifndef MENU_HPP
#define MENU_HPP
/*****************************************************
 *****        Заголовок модуля меню 		  ********
 *****             menu.hpp                   ********
 ****************************************************/

class Menu {
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
	static std::stack<Menu *> menuStack;
};

class MainMenu : public Menu{
public:
	MainMenu(Menu *_personMenu, Menu *_graphicMenu);
	void mainLoop();
private:
	void persons();
	void graphic();
	void settings();
	void quit();
	Menu *personMenu;
	Menu *graphicMenu;
};

class PersonMenu : public Menu{
public:
	PersonMenu(Menu *_listPersonsMenu, Menu *_selectUnitMenu);
	void mainLoop();
private:
	void selectUnit();
	void manualControl();
	void orderPerson();
	void quit();
	Menu *listPersonsMenu;
	Menu *selectUnitMenu;
};	

class SelectUnitMenu : public Menu {
public:
	SelectUnitMenu();
	void mainLoop();
private:
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
#endif //MENU_HPP
