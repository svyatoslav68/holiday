cmake_minimum_required(VERSION 3.10)

project(holiday VERSION 0.3.1)

set(TARGET holiday)
set(SOURCE_DIR src)
configure_file(
	${CMAKE_HOME_DIRECTORY}/version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/version.hpp
)

file(GLOB SOURCES_CXX
	${SOURCE_DIR}/*.cpp)

file(GLOB SOURCES_C
	${SOURCE_DIR}/*.c)

set(HEADERS
	${SOURCE_DIR}/menu.hpp)

set(CMAKE_BINARY_DIR ./build)
#set(VERSION_MAJOR 0)
#set(VERSION_MINOR 1)

# Поиск необходимых для сборок библиотек и заголовочных файлов

list(APPEND CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake_modules)

message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
find_package(MariaDBClient REQUIRED)
if(MariaDBClient_FOUND)
	include_directories(${MariaDBClient_INCLUDE_DIR})
	message("MariaDBClient_INCLUDE_DIR = ${MariaDBClient_INCLUDE_DIR}")
else()
	message("Не получится собрать приложение,\nне найден MariaDBClient")
	exit()
endif()

find_package(Boost REQUIRED COMPONENTS regex program_options date_time)

add_executable(${TARGET} ${SOURCES_CXX} ) 
target_link_libraries(${TARGET} ${MariaDBClient_LIBRARY})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
if(Boost_FOUND)
	message("Boost_LIBRARIES = "${Boost_LIBRARIES})
	target_link_libraries(${TARGET} ${Boost_LIBRARIES})
	target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
else()
	message("Не получится собрать приложение\n, не найден Boost")
endif()

message("Собирается проект ${PROJECT_NAME}")
message("Версия № ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

if (SOURCES_C)
	message("Найдены файлы для C")
	message("SOURCES_C = ${SOURCES_C}")
	target_sources(${TARGET} PRIVATE ${SOURCES_C})
endif(SOURCES_C)

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	C_STANDARD	11
	)
