/*****************************************************
 ***** Модуль содержит классы, использующиеся ********
 ***** для построения меню приложения.        ********
 ***** Все меню будут потомками виртуального  ********
 ***** класса Menu.                           ********
 *****             menu.cpp                   ********
 ****************************************************/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <boost/algorithm/string/regex.hpp>
#include "personsDisplayList.hpp"
#include "menu.hpp"

using std::string; 

Menu::Menu(){
}

Menu::~Menu(){
}

Menu *Menu::activeMenu(){
	return menuStack.top();
}

void Menu::enterMenu(Menu *menu){
	menuStack.push(menu);
}

void Menu::exitMenu(){
	menuStack.pop();
}

bool Menu::isActive(){
	return ! menuStack.empty();
}

int Menu::getMenuSelection(const string& menu){
	std::vector<string> list_items;
	boost::split_regex(list_items, menu, boost::regex(", "));
	std::vector<string>::const_iterator i = list_items.begin();
	while (std::cin.good()){
		for (uint8_t i = 0; i < list_items.size(); i++){
			std::cout << std::dec << "(" << (static_cast<int>(i)+1)%list_items.size() << ")" << list_items[i] << "," << std::endl;
		}
		std::cout << std::endl;
		int selection = -1;	// В переменную поместим введенный на клавиатуре символ
		std::cin >> selection;
		if (std::cin.fail())
			break;
		std::cout << "Нажата клавиша: "<< selection << std::endl;
		if (selection < list_items.size())
			return selection;
		else
			std::cout << "Выберите пункт меню еще раз" << std::endl;
	}
	return 0;
}

void Menu::clearScreen(){
	std::cout << string(100, '\n') << std::flush;
}

// Определение статической переменной-члена класса
std::stack<Menu *> Menu::menuStack;

MainMenu::MainMenu(Menu *_personMenu, Menu *_graphicMenu):personMenu(_personMenu), graphicMenu(_graphicMenu) {
}

void MainMenu::mainLoop(){
	clearScreen();
	//std::cout << "******* Main menu *********" << std::endl;
	static const string menu = "Persons, Graphic, Settings, Quit?";
	switch (getMenuSelection(menu)){
		case 1:persons();		break;
		case 2:graphic();		break;
		case 3:settings();	break;
		case 0:
		default: quit();
	}
}

void MainMenu::persons(){
	Menu::enterMenu(personMenu);
}

void MainMenu::graphic(){
	Menu::enterMenu(graphicMenu);
}

void MainMenu::settings(){

}

void MainMenu::quit(){
	exitMenu();
}

PersonMenu::PersonMenu(Menu *_listPersonsMenu):listPersonsMenu(_listPersonsMenu){
}

void PersonMenu::mainLoop(){
	clearScreen();
	//std::cout << "************ Person menu **************" << std::endl;
	static const string menu = "Select unit, Manual control, Order person, Quit?";
	switch (getMenuSelection(menu)){
	case 1: selectUnit();		break;
	case 2: manualControl();	break;
	case 3: orderPerson();	break;
	case 0:
	default:	quit();
	}
}

void PersonMenu::selectUnit(){
}

void PersonMenu::manualControl(){
	Menu::enterMenu(listPersonsMenu);
}

void PersonMenu::orderPerson(){
}

void PersonMenu::quit(){
	exitMenu();
}


GraphicMenu::GraphicMenu(){
}

void GraphicMenu::mainLoop(){
	clearScreen();
	//std::cout << "******* Graphic menu *********" << std::endl;
	static const string menu = "Input, View, Manual, Auto, Quit?";
	switch (getMenuSelection(menu)){
	case 0:
	default:	quit();
	}
}

void GraphicMenu::quit(){
	exitMenu();
}

ListPersonsMenu::ListPersonsMenu(PersonsDisplayList _lPerson):displayList(_lPerson){ } 

void ListPersonsMenu::mainLoop(){
	clearScreen();
	static const string menu = "Previous, Next, Quit";
	switch (getMenuSelection(menu)){
		case 1:	displayList.pageUp();
		case 2:	displayList.pageDown();
		case 0:
		default: quit();
	}
}

void ListPersonsMenu::quit(){
	exitMenu();
}

