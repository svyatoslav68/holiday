cmake_minimum_required(VERSION 3.10)

project(Holiday VERSION 0.0.1)

set(TARGET holiday)

set(SOURCES 
	main.cpp menu.cpp)

set(HEADERS
	menu.hpp)

add_executable(${TARGET} ${SOURCES} ${HEADERS}) #Собрать файл calendar из файла main.cpp

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 11	#Собирать в соответствии со стандартом c11
	)
