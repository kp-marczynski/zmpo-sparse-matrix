cmake_minimum_required(VERSION 3.8)
project(ZMPO_lista2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Interface.cpp Interface.h SparseMatrix.cpp SparseMatrix.h SparseCell.cpp SparseCell.h SparseMatrixRepository.cpp SparseMatrixRepository.h)
add_executable(ZMPO_lista2 ${SOURCE_FILES})