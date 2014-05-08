# CMake do jogo Castella
# porque usar make tava ficando complicado xP
project(Castella)
cmake_minimum_required(VERSION 2.6)

# Pacotes necessários pro jogo funfar
find_package(SDL)
find_package(SDL_image)
find_package(SDL_mixer)
find_package(SDL_ttf)
find_package(Lua51)

# Flags pro compilador
set(CMAKE_CXX_FLAGS "-g -Wall -fpermissive")

# pasta de includes
include_directories(include)
include_directories("arquivos\ lua")
include_directories("/usr/include/SDL")
# pasta dos códigos-fonte, compila pra pasta "build"
add_subdirectory(src build)
