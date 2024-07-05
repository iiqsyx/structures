cmake_minimum_required(VERSION 3.20)
project(list VERSION 0.1.0)

file( GLOB project 
    src/*
)

add_executable(list ${project})

