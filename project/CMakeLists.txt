cmake_minimum_required(VERSION 2.8)
project(CuttingStockProblemGeneticSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

# Finding GALib
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(GALIB REQUIRED)

# Variables with source files
file(GLOB_RECURSE COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/*.cpp")
file(GLOB SOLVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/solver/*.cpp")
file(GLOB GENOME_TESTER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/composite_genome_tester/*.cpp")

# Move input file to build directory
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input/maleplyty.txt" "${CMAKE_CURRENT_BINARY_DIR}/maleplyty.txt" COPYONLY)

# Main app - genetic solver
set(SOLVER_ALL_FILES "${COMMON_SRC}" "${SOLVER_SRC}")
add_executable(Solver "${SOLVER_ALL_FILES}")
target_link_libraries(Solver "${GALIB_LIBRARIES}")
target_include_directories(Solver PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/area_calculators"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/genetic_algorithm"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/io_handlers"
    "${GALIB_INCLUDE_DIR}")

# Composite genome tester app
set(GENOME_TESTER_ALL_FILES "${COMMON_SRC}" "${GENOME_TESTER_SRC}")
add_executable(GenomeTester "${GENOME_TESTER_ALL_FILES}")
target_link_libraries(GenomeTester "${GALIB_LIBRARIES}")
target_include_directories(GenomeTester PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/area_calculators"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/genetic_algorithm"
    "${CMAKE_CURRENT_SOURCE_DIR}/cutting_stock_problem_solver/common/io_handlers"
    "${GALIB_INCLUDE_DIR}")
