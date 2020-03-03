#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <locale>
extern "C"{
#include "mysql_connect.h"
}
//#include "personsDisplayList.hpp"
#include "menu.hpp"
#include "parent_menu.hpp"
#include "listPersons.hpp"
#include "cl_parametrs.hpp"
#include "version.hpp"

using std::string;

clParametrs appParametrs; // Параметры приложения - глобальная переменная
extern ListPersons lstPersons;

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
	lstPersons.load(appParametrs.getIdUnit());
	//ListPersonsMenu lMenu(lstPersons, nullptr);
	//SelectUnitMenu uMenu;
	//SettingsMenu sMenu(&uMenu);
	//PersonMenu pMenu(nullptr);
	//MainMenu mainMenu(nullptr, nullptr, &sMenu);
	MainMenu mainMenu;//nullptr, nullptr, nullptr);//&sMenu);
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}
