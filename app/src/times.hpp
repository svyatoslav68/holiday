/* Заголовочный файл классов, работающих с временными промежутками.
   Здесь будут классы: Date(момент времени), DurationHoliday(интервал времени, 
   соответствующий части отпуска) 
   */
#ifndef TIMES_HPP
#define TIMES_HPP

#include <iostream>
#include <ctime>

class Date {
public:
	Date(): theDate_(0) {}
	Date(int year, int month, int day);
private:
	std::time_t theDate_;
};

class DurationHoliday {
public:
	DurationHoliday() {}
private:
	Date begin_;
	Date end_;
};
#endif //TIMES_HPP
