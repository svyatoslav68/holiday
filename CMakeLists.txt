cmake_minimum_required(VERSION 3.10)

project(holiday VERSION 0.0.1)

set(TARGET holiday)

file(GLOB SOURCES_CXX
	*.cpp)

file(GLOB SOURCES_C
	*.c)

set(HEADERS
	menu.hpp)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

# Поиск необходимых для сборок библиотек и заголовочных файлов

list(APPEND CMAKE_MODULE_PATH /home/slava/Net_Projects/cmake)
message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
find_package(MariaDBClient REQUIRED)
if(MariaDBClient_FOUND)
	include_directories(${MariaDBClient_INCLUDE_DIR})
else()
	message("Не получится собрать приложение,\nне найден MariaDBClient")
	exit()
endif()

find_package(Boost REQUIRED COMPONENTS regex program_options)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else()
	message("Не получится собрать приложение\n, не найден Boost")
endif()

add_executable(${TARGET} ${SOURCES_CXX} ) #Собрать файл calendar из файла main.cpp
target_link_libraries(${TARGET} ${MariaDBClient_LIBRARY})
target_link_libraries(${TARGET} ${Boost_LIBRARIES})

message("Собирается проект ${PROJECT_NAME}")
message("Версия № ${VERSION_MAJOR}.${VERSION_MINOR}")
if (SOURCES_C)
	message("Найдены файлы для C")
	message("SOURCES_C = ${SOURCES_C}")
	target_sources(${TARGET} PRIVATE ${SOURCES_C})
endif(SOURCES_C)

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c14
	C_STANDARD	11
	)
