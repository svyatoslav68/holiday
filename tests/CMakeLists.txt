cmake_minimum_required(VERSION 3.10)

project(holiday-tests)
set(TARGET string_test)
set(TARGET_DISPLAY display_lists)
set(TARGET_XML xml_test)
set(SOURCE_DIR src)
set(SOURCE_APP ../app/src)

set(SOURCES_C ${SOURCE_APP}/mysql_connect.c)

set(CMAKE_BINARY_DIR ./build)

add_executable(${TARGET} ${SOURCE_DIR}/string_test.cpp)# ${SOURCE_APP}/str_from_file.cpp)
target_include_directories(${TARGET} PUBLIC ${SOURCE_APP})
target_sources(${TARGET} PUBLIC ${SOURCE_APP}/str_from_file.cpp)

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	)


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

add_executable(${TARGET_DISPLAY} ${SOURCE_DIR}/display_lists.cpp)
target_link_libraries(${TARGET_DISPLAY} ${MariaDBClient_LIBRARY})
target_include_directories(${TARGET_DISPLAY} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP})

target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/displayList.cpp)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/unitsDisplayList.cpp)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/personsDisplayList.cpp)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/listUnits.cpp)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/listPersons.cpp)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/str_from_file.cpp)

add_executable(${TARGET_XML} ${SOURCE_DIR}/xml_test.cpp)
target_include_directories(${TARGET_XML} PUBLIC ${SOURCE_APP})

if (SOURCES_C)
	message("Найдены файлы для C")
	message("SOURCES_C = ${SOURCES_C}")
	target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCES_C})
endif(SOURCES_C)
target_sources(${TARGET_DISPLAY} PUBLIC ${SOURCE_APP}/cl_parametrs.cpp)
target_sources(${TARGET_XML} PUBLIC ${SOURCE_APP}/str_from_file.cpp)

if(Boost_FOUND)
	target_link_libraries(${TARGET_DISPLAY} ${Boost_LIBRARIES})
	target_include_directories(${TARGET_DISPLAY} PUBLIC ${Boost_INCLUDE_DIRS})
	#target_link_libraries(${TARGET_XML} ${Boost_LIBRARIES})
	target_include_directories(${TARGET_XML} PUBLIC ${Boost_INCLUDE_DIRS})
	target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
else()
	message("Не получится собрать приложение\n, не найден Boost")
endif()

set_target_properties(
	${TARGET_DISPLAY} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	C_STANDARD	11
	)
