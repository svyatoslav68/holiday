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

std::string Menu::parseString(const std::string &menu){
	return menu;
}

char Menu::getMenuSelection(const std::string& menu){
	while (std::cin.good()){
		std::cout << menu;
		char selection = 0;	// В переменную поместим введенный на клавиатуре символ
		if (std::cin.fail())
			break;
		std::string choices;// Здесь будут содержаться все символы, которые соответствуют пункту меню
		choices = parseString(menu);
		if (choices.find(std::tolower(selection)) != std::string::npos)
			return std::tolower(selection);
		else
			std::cout << "Выберите пункт меню еще раз" << std::endl;
	}
	return 0;
}

// Определение статической переменной-члена класса
std::stack<Menu *> Menu::menuStack;

MainMenu::MainMenu(){
}

void MainMenu::mainLoop(){
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

