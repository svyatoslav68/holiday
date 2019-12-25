#ifndef DISPLAYLIST_HPP
#define DISPLAYLIST_HPP

#include <deque>
/*******************************************************
 ******* Заголовочный файл класса отображения **********
 ******* части списка на экране монитора	  **********
 ******************************************************/
class DisplayList {
	/* Это абстрактный класс. Он будет предком нескольких 
	 * классов, которые будут отображать список, который 
	 * не помещается на экран, а отображается каждый раз
	 * только часть списка. */
	private:
		typedef std::deque<int> cache_t;   // Тип двусторонней очереди целых. Тип кэша записей.
		cache_t cache;
		//const uint8_t number_strings; // Количество строк экрана
		bool cachedFirst;	// True, если буфер содержит первую запись списка
		bool cachedLast;	// True, если буфер содержит последнюю запись списка
		int firstVisibleId;	//Идентификатор первой видимой записи
		void fillCachedFwd(	int start, // Позиция в буфере, начиная с которой отображаются записи 
							int needed // Количество записей в буфере, которых не хватает для отображения
							);
		void fillCachedBkwd(int start, int needed);
	protected:
		/* Отображение записи с идентификатором record_id.
		 * Определяется в классе-потомке*/
		virtual void displayRecord(int record_id) = 0;
		/* Функция отображает карточку записи. Там минимальная информация о записи.
		 * Переопределяется в потомке */
		//virtual void displayCard(int record_id) = 0;
		/* Функция добавляет очередную часть отображаемого списка, определяется в классе-потомке. Возвращает true, если в result представлена первая или последняя запись */
		virtual bool fetchMore(
			int startId,// Запись с которой начинается добавление новой порции данных
			int numRecords,// Количество добавляемых записей, если numRecords отрицательное число, то добавляются предшествующие записи, если numRecords положительное чило, то добавлются последующие записи
			std::vector<int>& result // возвращаемые записи
			) = 0;
	public:
		static const int number_strings = 15;
		//DisplayList(const uint8_t n_strings = 15);
		DisplayList();//const uint8_t n_strings = 15);
		//DisplayList
		virtual ~DisplayList();
		void display();
		void pageUp();
		void pageDown();
		void toStart(); 	// Процедура показа первого экранного списка
		bool atStart();		// True, если показываемый список является первым
		bool atEnd();		// True, если показываемый список является последним
		void reset();
};

#endif //DISPLAYLIST_HPP
