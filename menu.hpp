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
	static char getMenuSelection(const std::string& menu);
private:
	static std::stack<Menu *> menuStack;
	static std::string parseString(const std::string &menu);
};

class MainMenu : public Menu{
public:
	MainMenu();
	void mainLoop();
private:
	void persons();
	void graphic();
};

class PersonMenu : public Menu{
public:
	PersonMenu();
	void mainLoop();
private:
	void selectUnit();
	void manualControl();
	void orderPerson();
};	
#endif //MENU_HPP
