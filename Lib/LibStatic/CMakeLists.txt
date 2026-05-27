cmake_minimum_required(VERSION 3.20)
project(RakNetLibStatic LANGUAGES CXX)

FILE(GLOB ALL_HEADER_SRCS ${RakNet_SOURCE_DIR}/Source/*.h)
FILE(GLOB ALL_CPP_SRCS ${RakNet_SOURCE_DIR}/Source/*.cpp)

include_directories( ${RAKNET_INTERNAL_INCLUDE_DIRS} ) 

add_library(RakNetLibStatic STATIC ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} readme.txt)

target_include_directories(RakNetLibStatic PRIVATE ${RAKNET_INTERNAL_INCLUDE_DIRS})

IF(WIN32 AND NOT UNIX)
	target_compile_definitions(RakNetLibStatic PRIVATE WIN32 _RAKNET_LIB)
	target_compile_options(RakNetLibStatic PRIVATE /GS- /GR-)
ENDIF(WIN32 AND NOT UNIX)

IF(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetLibStatic ${RAKNET_LIBRARY_LIBS})

	IF(NOT CMAKE_GENERATOR STREQUAL "MSYS Makefiles")
		set_target_properties(RakNetLibStatic PROPERTIES STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:LIBCD.lib /NODEFAULTLIB:LIBCMTD.lib /NODEFAULTLIB:MSVCRT.lib" )
	ENDIF(NOT CMAKE_GENERATOR STREQUAL "MSYS Makefiles")

ELSE(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetLibStatic ${RAKNET_LIBRARY_LIBS})
	INSTALL(TARGETS RakNetLibStatic DESTINATION ${RakNet_SOURCE_DIR}/Lib/RakNetLibStatic)
	INSTALL(FILES ${ALL_HEADER_SRCS} DESTINATION ${RakNet_SOURCE_DIR}/include/raknet)
ENDIF(WIN32 AND NOT UNIX)


