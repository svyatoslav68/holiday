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
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/lexical_cast.hpp>
#include "personsDisplayList.hpp"
#include "listPersons.hpp"
#include "listUnits.hpp"
#include "parent_menu.hpp"
#include "menu.hpp"
#include "tholiday.hpp"
#include "data_from_sql.hpp"

using std::string; 

ListPersons lstPersons;

extern clParametrs appParametrs;

MainMenu::MainMenu(){
	PersonMenu *pMenu = new PersonMenu();
	personMenu = pMenu;
	GraphicMenu *gMenu = new GraphicMenu();
	graphicMenu = gMenu;
	SettingsMenu *sMenu = new SettingsMenu();//nullptr);
	settingsMenu = sMenu;
}

MainMenu::MainMenu(Menu *_personMenu, Menu *_graphicMenu, Menu *_settingsMenu):personMenu(_personMenu), graphicMenu(_graphicMenu), settingsMenu(_settingsMenu){
}

MainMenu::~MainMenu(){
	if (personMenu)
		delete personMenu;
	if (graphicMenu)
		delete graphicMenu;
	if (settingsMenu)
		delete settingsMenu;
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
	//ListPersons lstPersons;
	//lstPersons.load();
	//ProcessingPersonMenu *ppMenu = new ProcessingPersonMenu();
	//ListPersonsMenu *lMenu = new ListPersonsMenu(lstPersons, ppMenu);
	//personMenu = new PersonMenu(nullptr);
	//personMenu = new PersonMenu(lMenu);
	if (!personMenu){
		PersonMenu *pMenu = new PersonMenu();
		personMenu = pMenu;
	}
	Menu::enterMenu(personMenu);
}

void MainMenu::graphic(){
	if (!graphicMenu){
		GraphicMenu *gMenu = new GraphicMenu();
		graphicMenu = gMenu;
	}
	Menu::enterMenu(graphicMenu);
}

void MainMenu::settings(){
	if (!settingsMenu){
		SettingsMenu *sMenu = new SettingsMenu();//nullptr);
		settingsMenu = sMenu;
	}
	Menu::enterMenu(settingsMenu);
}

void MainMenu::quit(){
	exitMenu();
}

PersonMenu::PersonMenu(){
	ListPersonsMenu *lMenu = new ListPersonsMenu(lstPersons);
	listPersonsMenu = lMenu;
}

PersonMenu::PersonMenu(Menu *_listPersonsMenu):listPersonsMenu(_listPersonsMenu){ }

PersonMenu::~PersonMenu(){
	if (listPersonsMenu)
		delete listPersonsMenu;
}

void PersonMenu::mainLoop(){
	clearScreen();
	//std::cout << "************ Person menu **************" << std::endl;
	static const string menu = "Manual control, Order person, Quit?";
	static const string choices = "MOQ";
	switch (getMenuSelection(menu, choices)){
	case 'M': manualControl();	break;
	case 'O': orderPerson();	break;
	case 'Q':	quit(); break;
	default:;
	}
}

void PersonMenu::manualControl(){
	if (!listPersonsMenu){
		ListPersonsMenu *lMenu = new ListPersonsMenu(lstPersons);
		listPersonsMenu = lMenu;
	}
	Menu::enterMenu(listPersonsMenu);
}

void PersonMenu::orderPerson(){
}

void PersonMenu::quit(){
	exitMenu();
}

SelectUnitMenu::SelectUnitMenu(){
	//listUnits.load();	
	displayList = new UnitsDisplayList(listUnits);
}

SelectUnitMenu::~SelectUnitMenu(){

}

void SelectUnitMenu::mainLoop(){
/*Главный цикл меню выбора подразделения. Выводится очередная страница подразделения. Ввод цифры выбирает
подразделение. А ввод буквы 'p' или 'n' выводит
предыдущую или следующую страницу списка подразделений */
	clearScreen();
	displayList->display();
	//displayList->printAll();
	static const string menu = "Previous, Next, Quit";
	static const string choices = "PNQ";
	std::cout << "Выбрано подразделение : " << TUnit(appParametrs.getIdUnit()).getFullName() << std::endl;
	lstPersons.load(appParametrs.getIdUnit());
	uint8_t result = getMenuSelection(menu, choices);
	if ((result > 0) and (result <= displayList->number_strings)){
		selectUnit(result);
	}
	switch (result){
	case 'P': displayList->pageUp();break;
	case 'N': displayList->pageDown();break;
	case 'Q':	quit(); break;
	default:;
	}
}

void SelectUnitMenu::selectUnit(uint8_t _idUnit){
	int selectedIdUnit = displayList->getIdRecord(_idUnit);
	appParametrs.setIdUnit(selectedIdUnit);
}

void SelectUnitMenu::quit(){
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

ListPersonsMenu::ListPersonsMenu(ListPersons &_listPersons):listPersons(_listPersons), displayList(_listPersons){
		ProcessingPersonMenu *ppMenu = new ProcessingPersonMenu();
		personMenu = ppMenu;
}

ListPersonsMenu::ListPersonsMenu(ListPersons &_listPersons, ProcessingPersonMenu *_pMenu):listPersons(_listPersons),displayList(_listPersons), personMenu(_pMenu){ } 

ListPersonsMenu::~ListPersonsMenu(){
	if (personMenu)
		delete personMenu;
}

void ListPersonsMenu::mainLoop(){
	clearScreen();
	/* Отображаем очередную страницу с выбранными
	сотрудниками. Сотрудника можно выбрать набрав
	соответствующее число. */
	displayList.display();
	//displayList.printAll();
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
	if (!personMenu){
		ProcessingPersonMenu *ppMenu = new ProcessingPersonMenu();
		personMenu = ppMenu;
	}
	personMenu->setIdPerson(displayList.getIdRecord(static_cast<int>(number)));
	Menu::enterMenu(personMenu);
}

void ListPersonsMenu::quit(){
	exitMenu();
}

ProcessingPersonMenu::~ProcessingPersonMenu(){

}

void ProcessingPersonMenu::mainLoop(){
	static const string menu = "Add holiday, Quit";
	static const string choices = "AQ";
	clearScreen();
	std::cout << "Выбран сотрудник с идентификатором " << idPerson << std::endl;
	TPerson myPerson(idPerson);
	myPerson.displayCard();
	/* Создаем и загружаем объект, содержащий список
	типов отпусков 
	TypesHoliday th;
	th.load();
	th.printContent();*/
	ListHolidays lstHolidays(idPerson);
	lstHolidays.load();
	lstHolidays.printContent();
	uint8_t result = getMenuSelection(menu, choices);
	if ((result > 0) and (result < 9)){
		editPlanHoliday(result);
	}
	switch (result){
		case 'A':	addPlanHoliday(); break;
		case 'Q':	quit(); break;
		default: ;
	}
}

void ProcessingPersonMenu::setIdPerson(int id){
	idPerson = id;
}

void ProcessingPersonMenu::addPlanHoliday(){
}

void ProcessingPersonMenu::editPlanHoliday(int numItem){
}

void ProcessingPersonMenu::quit(){
	exitMenu();
}

void ProcessingUnitMenu::mainLoop(){
	static const string menu = "Quit";
	static const string choices  = "Q";
	clearScreen();
	std::cout << "Выбрано подразделение с идентификатором " << idUnit << std::endl;
	uint8_t result = getMenuSelection(menu, choices);
	switch (result){
		case 'Q': quit(); break;
		default: ;
	}
}

void ProcessingUnitMenu::quit(){
	exitMenu();
}

SettingsMenu::SettingsMenu(){
	SelectUnitMenu *uMenu = new SelectUnitMenu();
	selectUnitMenu = uMenu;
}

SettingsMenu::~SettingsMenu(){
	if (selectUnitMenu)
		delete selectUnitMenu;
}

void SettingsMenu::mainLoop(){
	static const string menu = "Select unit, Quit";
	static const string choices  = "SQ";
	clearScreen();
	uint8_t result = getMenuSelection(menu, choices);
	switch (result){
		case 'S': selectUnit();		break;
		case 'Q':	quit(); break;
		default: ;
	}
}

void SettingsMenu::selectUnit(){
	if (!selectUnitMenu){
		SelectUnitMenu *uMenu = new SelectUnitMenu();
		selectUnitMenu = uMenu;
	}
	Menu::enterMenu(selectUnitMenu);
}


void SettingsMenu::quit(){
	exitMenu();
}

