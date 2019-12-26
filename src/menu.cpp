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
#include <boost/lexical_cast.hpp>
#include "personsDisplayList.hpp"
#include "listPersons.hpp"
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
			std::cout << std::dec << "(" << (static_cast<int>(i)+1)%list_items.size() << ")" << list_items[i];
			if  (i != list_items.size() - 1)
				std::cout << ",";
			std::cout << std::endl;
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

uint8_t Menu::getMenuSelection(const string& menu, const string& choices){
	//string buf_for_digit("");	// Переменная для хранения строки, которая будет преобразована в число
	std::vector<string> list_items;
	boost::split_regex(list_items, menu, boost::regex(", "));
	std::vector<string>::const_iterator i = list_items.begin();
	while (std::cin.good()){
		for (uint8_t i = 0; i < list_items.size(); i++){
			std::cout << std::dec << "(" << choices[i] << ")" << list_items[i];
			if  (i != list_items.size() - 1)
				std::cout << ",";
			std::cout << std::endl;
		}
		/*uint8_t selection = -1;	// В переменную поместим введенный на клавиатуре символ
		std::cin >> selection;*/
		string input_str("");
		string digit_str("");
		bool str_is_digit = false;
		std::cin >> input_str;
		if (std::cin.fail())
			break;
		std::cout << "Введена строка: "<< input_str << std::endl;
		//if (selection < list_items.size())
		string::const_iterator ch_it = input_str.begin();
		while (ch_it < input_str.end()){
			if (std::isdigit(*ch_it)){
				str_is_digit = true;
				std::cout << "Нажата клавиша цифры: "  << *ch_it << std::endl;
				digit_str += *ch_it;
			}
			if (choices.find(std::toupper(*ch_it)) != string::npos || 
				choices.find(std::tolower(*ch_it)) !=        string::npos)
				return std::toupper(*ch_it);
			else
				std::cout << "Выберите пункт меню еще раз" << std::endl;
			ch_it++;
		}
		if (str_is_digit)
			return boost::lexical_cast<int>(digit_str);
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
	static const string choices = "PGSQ";
	switch (getMenuSelection(menu, choices)){
		case 'P':persons();		break;
		case 'G':graphic();		break;
		case 'S':settings();	break;
		case 'Q':	quit(); break;
		default:;
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
	static const string choices = "SMOQ";
	switch (getMenuSelection(menu, choices)){
	case 'S': selectUnit();		break;
	case 'M': manualControl();	break;
	case 'O': orderPerson();	break;
	case 'Q':	quit(); break;
	default:;
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
	static const string choices = "IVMAQ";
	switch (getMenuSelection(menu, choices)){
	case 'Q':	quit(); break;
	default:;
	}
}

void GraphicMenu::quit(){
	exitMenu();
}

ListPersonsMenu::ListPersonsMenu(ListPersons &_listPersons, ProcessingPersonMenu *_pMenu):listPersons(_listPersons),displayList(_listPersons), personMenu(_pMenu){ } 

void ListPersonsMenu::mainLoop(){
	clearScreen();
	displayList.display();
	static const string menu = "Previous, Next, Quit";
	static const string choices = "PNQ";
	uint8_t result = getMenuSelection(menu, choices);
	if ((result > 0) and (result <= displayList.number_strings)){
		//std::cout << "Select digit " << static_cast<int>(result) << std::endl;
		selectPerson(result);
	}
	switch (result){
		case 'P':	displayList.pageUp();break;
		case 'N':	displayList.pageDown();break;
		case 'Q':	quit(); break;
		default: ;
	}
}

void ListPersonsMenu::selectPerson(uint8_t number){
	personMenu->setIdPerson(displayList.getIdRecord(static_cast<int>(number)));
	Menu::enterMenu(personMenu);
}

void ListPersonsMenu::quit(){
	exitMenu();
}

void ProcessingPersonMenu::mainLoop(){
	static const string menu = "Quit";
	static const string choices = "Q";
	clearScreen();
	std::cout << "Выбран сотрудник с идентификатором " << idPerson << std::endl;
	uint8_t result = getMenuSelection(menu, choices);
	switch (result){
		case 'Q':	quit(); break;
		default: ;
	}
}

void ProcessingPersonMenu::setIdPerson(int id){
	idPerson = id;
}

void ProcessingPersonMenu::quit(){
	exitMenu();
}

