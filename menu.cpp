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
#include "menu.hpp"

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

char Menu::getMenuSelection(const std::string& menu, const std::string &choices){
	while (std::cin.good()){
		std::cout << menu;
		char selection = 0;	// В переменную поместим введенный на клавиатуре символ
		std::cin >> selection;
		if (std::cin.fail())
			break;
		if (choices.find(std::tolower(selection)) != std::string::npos ||
			choices.find(std::toupper(selection)) != std::string::npos)
			return std::toupper(selection);
		else
			std::cout << "Выберите пункт меню еще раз" << std::endl;
	}
	return 0;
}

void Menu::clearScreen(){
	std::cout << "\f" << std::flush;
}

// Определение статической переменной-члена класса
std::stack<Menu *> Menu::menuStack;

MainMenu::MainMenu(){
}

void MainMenu::mainLoop(){
	clearScreen();
	std::cout << "Main menu" << std::endl;
	static const char menu[] = "";
	static const char choises[] = "";
	getMenuSelection(menu, choises);
}

void MainMenu::persons(){
}

void MainMenu::graphic(){
}

PersonMenu::PersonMenu(){
}

void PersonMenu::mainLoop(){
}

void PersonMenu::selectUnit(){
}

void PersonMenu::manualControl(){
}

void PersonMenu::orderPerson(){
}

