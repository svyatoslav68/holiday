#include <iostream>
#include <stack>
#include <string>
#include "menu.hpp"

int main(int argc, char **argv){
	MainMenu mainMenu;
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}
