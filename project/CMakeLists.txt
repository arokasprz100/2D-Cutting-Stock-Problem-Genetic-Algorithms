cmake_minimum_required(VERSION 2.8)
project(CuttingStockProblemGeneticSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

# Finding GALib
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(GALIB REQUIRED)

# Variables with source files
file(GLOB_RECURSE COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/src/*.cpp")
file(GLOB SOLVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/main/Solver.cpp")
file(GLOB GENOME_TESTER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/main/CompositeGenomeTesterMain.cpp")

# Move input file and plotting script to build directory
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input/maleplyty.txt" "${CMAKE_CURRENT_BINARY_DIR}/maleplyty.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/scripts/results_drawer.py" "${CMAKE_CURRENT_BINARY_DIR}/results_drawer.py" COPYONLY)

# Main app - genetic solver
set(SOLVER_ALL_FILES "${COMMON_SRC}" "${SOLVER_SRC}")
add_executable(Solver "${SOLVER_ALL_FILES}")
target_link_libraries(Solver "${GALIB_LIBRARIES}")
target_include_directories(Solver PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/include"
    "${GALIB_INCLUDE_DIR}")

# Composite genome tester app
set(GENOME_TESTER_ALL_FILES "${COMMON_SRC}" "${GENOME_TESTER_SRC}")
add_executable(GenomeTester "${GENOME_TESTER_ALL_FILES}")
target_link_libraries(GenomeTester "${GALIB_LIBRARIES}")
target_include_directories(GenomeTester PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/include"
    "${GALIB_INCLUDE_DIR}")
