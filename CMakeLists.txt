cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_sleep C)

add_bare_module(bare_sleep)

target_sources(
  ${bare_sleep}
  PRIVATE
    binding.c
)
