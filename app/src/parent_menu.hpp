/********** Заголовочный файл класса Menu, предка всех *********
*********** меню приложения. Класс абстрактный.        *********
***************************************************************/
#ifndef PARENT_MENU_HPP
#define PARENT_MENU_HPP

class Menu {
// Виртуальный класс, предок всех меню
public:
	Menu();
	virtual ~Menu();
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
	static uint8_t getMenuSelection(const std::string& menu, const std::string& choices);
	static void clearScreen();
private:
	// Статический член класса
	static std::stack<Menu *> menuStack;
};

#endif //PARENT_MENU_HPP
