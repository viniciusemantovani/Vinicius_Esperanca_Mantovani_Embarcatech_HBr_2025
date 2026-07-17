cmake_minimum_required(VERSION 3.13)

project(test_unity C)

add_executable(test_unity test.c ../leitor_temperatura_testado.c ../unity/unity.c)

target_include_directories(test_unity PRIVATE ../unity ../)