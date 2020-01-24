cmake_minimum_required(VERSION 3.10)

project(holiday-tests)
set(TARGET string_test)
set(SOURCE_DIR src)
set(SOURCE_APP ../app/src)

set(CMAKE_BINARY_DIR ./build)

include_directories(${SOURCE_APP})
add_executable(${TARGET} ${SOURCE_DIR}/string_test.cpp)# ${SOURCE_APP}/str_from_file.cpp)

target_sources(${TARGET} PUBLIC ${SOURCE_APP}/str_from_file.cpp)

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	)

