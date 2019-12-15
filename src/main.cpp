#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <locale>
extern "C"{
#include "mysql_connect.h"
}
#include "personsDisplayList.hpp"
#include "menu.hpp"
#include "listPersons.hpp"

using std::string;

int main(int argc, char **argv){
	setlocale(LC_ALL, "");
	ListPersons lstPersons;
	lstPersons.load();
	ListPersonsMenu lMenu(lstPersons);
	PersonMenu pMenu(&lMenu);
	GraphicMenu gMenu;
	MainMenu mainMenu(&pMenu, &gMenu);
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}