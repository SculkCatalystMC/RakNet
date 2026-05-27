cmake_minimum_required(VERSION 3.20)
project(RakNetDLL LANGUAGES CXX)

FILE(GLOB ALL_HEADER_SRCS ${RakNet_SOURCE_DIR}/Source/*.h)
FILE(GLOB ALL_CPP_SRCS ${RakNet_SOURCE_DIR}/Source/*.cpp)


include_directories( ${RAKNET_INTERNAL_INCLUDE_DIRS} ) 

add_library(RakNetDLL SHARED ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} readme.txt)

target_include_directories(RakNetDLL PRIVATE ${RAKNET_INTERNAL_INCLUDE_DIRS})
	
IF(WIN32 AND NOT UNIX)
	target_compile_definitions(RakNetDLL PRIVATE WIN32 _RAKNET_DLL)
	target_compile_options(RakNetDLL PRIVATE /GS- /GR-)
ENDIF(WIN32 AND NOT UNIX)

IF(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS})
ELSE(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS})
	INSTALL(TARGETS RakNetDLL DESTINATION ${RakNet_SOURCE_DIR}/Lib/DLL)
ENDIF(WIN32 AND NOT UNIX)
