cmake_minimum_required(VERSION 3.7)
project(Practica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Chromosome.cc Chromosome.hh Organism.cc Organism.hh Specie.cc Specie.hh program.cc Exceptions.hh)
add_executable(Practica ${SOURCE_FILES})