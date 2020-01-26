/*************************************************************
 *********** Файл реализации класса отображения **************
 *********** части списка на экране монитора    **************
 ***********          displayList.cpp           **************
 ************************************************************/
#include <iostream>
#include <iomanip>
//#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include "displayList.hpp"

DisplayList::DisplayList(){//const uint8_t n_strings):number_strings(n_strings){
	reset();
}

DisplayList::~DisplayList(){

}

void DisplayList::display(){
	// Заполнение буфера первым экранным списком
	fillCachedFwd(firstVisibleId, number_strings);
	// Если буфер пустой, то нечего показывать
	if (cache.empty()){
		std::cout << "============== Нет записей для показа ===========" << std::endl;
		return;
	}
	int recsToShow = /* Количество записей для показа, определяется, как минимальное
					из двух значения: количество отображаемых за один проход записей или
					разница между размером буфера и первой отображаемой записью */
		std::min((int)number_strings, int(cache.size() - firstVisibleId));
	if (atStart()) // Сообщение о начале списка
		std::cout << "============ Начало списка ==============" << std::endl;
	else 
		std::cout << "-----------------------------------------" << std::endl;
	std::deque<int>::iterator start = cache.begin() + firstVisibleId; // Итератор указывающий на первую показываемую запись
	std::deque<int>::iterator finish = start + recsToShow;			// Итератор указывающий на последнюю показываемую запись
	for (std::deque<int>::iterator i = start; i != finish; i++){
		// Показ номера строк
		int linenum = i - start + 1;
		std::cout << std::setw(2) << std::setfill(' ') << std::right << std::dec << linenum << ":";
		displayRecord(*i);
		std::cout << std::endl;
	}
	if (atEnd()) // Сообщение о конце списка
		std::cout << "============ Конец списка ==============" << std::endl;
	else 
		std::cout << "-----------------------------------------" << std::endl;
}

void DisplayList::pageUp(){
	if (atStart())
		return;
	fillCachedBkwd(firstVisibleId, number_strings);
	firstVisibleId = std::max(firstVisibleId - number_strings, 0);
}

int DisplayList::getIdRecord(int number){
	// Итератор указывающий на number-ную запись в кэше
	std::deque<int>::const_iterator it = cache.begin()+firstVisibleId+number - 1;
	return *it;
}

void DisplayList::pageDown(){
	if (atEnd())
		return;
	fillCachedFwd(firstVisibleId, 2*number_strings);
	if(!atEnd())
		firstVisibleId+=number_strings;
}

void DisplayList::toStart(){
	if (cachedFirst)	// Уже показывается первая запись списка
		firstVisibleId = 0;
	else
		reset();
}

bool DisplayList::atStart(){
	return cachedFirst && (firstVisibleId == 0);
}

bool DisplayList::atEnd(){
	return (cachedLast && (cache.size() - firstVisibleId <= number_strings));
}

void DisplayList::reset(){
	cache.clear();
	cachedFirst = false;
	cachedLast = false;
	firstVisibleId = 0;
}

/* Добавление needed записей в конец буфера. Если количество добавленных записей меньше needed, то устанавливается cachedLast */
void DisplayList::fillCachedFwd(int start, int needed){
	int startId; // Позиция, начиная с которой будут добавляться записи
	startId = 0; // Изначально считаем, что добавлять записи нужно в начало буфера
	if (cache.empty()){ // Если записи добавляются с начала буфера
		cachedFirst = true;
	}
	else {
		startId = cache.back(); // Если буфер не пуст, то начальная позиция устанавливается в конец буфера
	}
	int recordsTillEnd; // Количество записей от start до конца буфера. Нужно, чтобы знать, сколько еще записей требуется добавить
	recordsTillEnd = cache.size() - start;
	if ( !cachedLast && recordsTillEnd < needed ) { // Если не отображается последняя запись, и количество имеющихся в буфере данных меньше, чем требуется, то нужно добавить в буфер записей
		std::vector<int> moreRecords; // В векторе будут содержаться записи, которые нужно будет добавить в буфер
		cachedLast = fetchMore(startId, needed - recordsTillEnd, moreRecords);
		std::copy(moreRecords.begin(), moreRecords.end(), std::back_inserter(cache));
	}		
}

void DisplayList::fillCachedBkwd(int start, int needed){
	int startId = 0;
	if (cache.empty()) {
		cachedLast = true;
	}
	else {
		startId = cache.front();
	}
	int recordsTillStart = start;
	if (!cachedFirst && recordsTillStart < needed){
		std::vector<int> moreRecords;	// Контейнер будет содержать коды записей, которые нужно будет добавить в кеш
		cachedFirst = fetchMore(startId, - (needed -recordsTillStart), moreRecords);
		std::copy(moreRecords.rbegin(), moreRecords.rend(), std::front_inserter(cache));
		firstVisibleId += moreRecords.size(); // Индекс первого видимого элемента должен увеличиться на число добавленных записей
	}
}

void DisplayList::printAll(){
	auto it = cache.cbegin();
	while (it < cache.cend()){
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

