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
	PersonMenu();
	void mainLoop();
private:
	void selectUnit();
	void manualControl();
	void orderPerson();
	void quit();
};	

class GraphicMenu :public Menu {
public:
	GraphicMenu();
	void mainLoop();
private:
	void quit();
};
#endif //MENU_HPP
