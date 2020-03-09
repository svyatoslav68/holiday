/*** Файл реализации класса Menu **************************
**********************************************************/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include "parent_menu.hpp"
#include <boost/algorithm/string/regex.hpp>
#include <boost/lexical_cast.hpp>

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

