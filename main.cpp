#include <iostream>
#include <stack>
#include <string>
extern "C"{
#include "mysql_connect.h"
}
#include "menu.hpp"

using std::string;

int main(int argc, char **argv){
	string name = "asasd";
	connect(name.c_str(), "qweqwe", "123123", "dgdfgd");
	MainMenu mainMenu;
	Menu::enterMenu(&mainMenu);
	while (Menu::isActive())
		Menu::activeMenu()->mainLoop();
	return 0;
}
