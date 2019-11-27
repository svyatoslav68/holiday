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
<<<<<<< HEAD
	ListPersons lstPersons;
	lstPersons.load();
=======
	string name_bd = "unit";
	MYSQL connection;
	bd_connect(&connection, name_bd.c_str());
	ListPersons lstPersons;
>>>>>>> 3df0734f50db4a4f426d8eb5dce4f0eb12a94616
	ListPersonsMenu lMenu(lstPersons);
	PersonMenu pMenu(&lMenu);
	GraphicMenu gMenu;
	MainMenu mainMenu(&pMenu, &gMenu);
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}
