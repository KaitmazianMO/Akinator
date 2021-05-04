cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Akinator)

add_executable(${PROJECT_NAME} 
	src/main.cpp
    src/Akinator.h
    src/Akinator.cpp 
    src/Tree.h
	src/Tree.cpp
	src/Node.h
	src/DataBase.h
	src/DataBase.cpp
	src/TastyFunctions.h
	src/TastyFunctions.cpp
	src/VisualStudioWarnings.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

