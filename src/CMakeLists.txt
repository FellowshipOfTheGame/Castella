# sources são os arquivos .cpp
file(GLOB sources *.cpp)

# Executável final
add_executable(castella.exe ${sources})
target_link_libraries(castella.exe ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLTTF_LIBRARY})