cmake_minimum_required(VERSION 3.20)

set( RAKNET_INTERNAL_INCLUDE_DIRS 
	${RakNet_SOURCE_DIR}/Source 
)

if( RAKNET_ENABLE_STATIC )
	add_subdirectory(LibStatic)
endif()


if( RAKNET_ENABLE_DLL )
	add_subdirectory(DLL)
endif()
