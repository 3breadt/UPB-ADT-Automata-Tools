cmake_minimum_required(VERSION 2.6)

PROJECT(AutomataTools)

IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS(-std=c++0x) # Enable C++0x Extension
ENDIF()

# Compiler flags
SET(CMAKE_CXX_FLAGS "-Wall -Wold-style-cast -Wpointer-arith -Wno-unused-parameter -Wcast-qual")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNODEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Linker flags
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined")

ADD_EXECUTABLE(AutomataTools
  main.cpp
  FSA_ConvertFsaToRg.cpp
  FSA_ConvertFsaToRg.hpp
  FSA_FiniteStateAutomata.cpp
  FSA_FiniteStateAutomata.hpp
  FSA_FSAtoREConverter.cpp
  FSA_FSAtoREConverter.hpp
  FSA_State.cpp
  FSA_State.hpp
  FSA_Transition.cpp
  FSA_Transition.hpp
  RE_ReaderWriter.cpp
  RE_ReaderWriter.hpp
  RE_RegularExpression.cpp
  RE_RegularExpression.hpp
  RE_TreeNode.cpp
  RE_TreeNode.hpp
  RG_DynArray.h
  RG_Grammar.cpp
  RG_Grammar.h
  RG_Production.cpp
  RG_Production.h
  RG_ReaderWriter.cpp
  RG_ReaderWriter.h
  RG_Substitution.cpp
  RG_Substitution.h
 )
