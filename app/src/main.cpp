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
#include "cl_parametrs.hpp"
#include "version.hpp"

using std::string;

clParametrs appParametrs; // Параметры приложения - глобальная переменная

string getVersion(){
	return string(g_version);
}

int main(int argc, char **argv){
	appParametrs.setArgs(argc, argv);
	setlocale(LC_ALL, "");
	if (appParametrs.isVersion()){
		std::cout << "Version of app: " << getVersion() << std::endl; 
		exit(0);
	}
	ListPersons lstPersons;
	lstPersons.load();
	ProcessingPersonMenu ppMenu;
	ListPersonsMenu lMenu(lstPersons, &ppMenu);
	//ListPersonsMenu lMenu(nullptr, &ppMenu);
	ListUnits lstUnits;
	lstUnits.load();
	SelectUnitMenu uMenu(lstUnits);
	SettingsMenu sMenu(&uMenu);
	PersonMenu pMenu(&lMenu);
	//PersonMenu pMenu(nullptr);
	GraphicMenu gMenu;
	//MainMenu mainMenu(nullptr, nullptr, &sMenu);
	MainMenu mainMenu(&pMenu, &gMenu, &sMenu);
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}
