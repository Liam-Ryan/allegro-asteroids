project(allegro_asteroids)
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

find_package(PkgConfig REQUIRED)
add_executable(allegro_asteroids src/main.c)
pkg_search_module(ALLEGRO REQUIRED allegro-5)
pkg_search_module(ALLEGRO_IMAGES REQUIRED allegro_image-5)
pkg_search_module(ALLEGRO_PRIMITIVES REQUIRED allegro_primitives-5)

target_link_libraries(allegro_asteroids ${ALLEGRO_LIBRARIES} ${ALLEGRO_IMAGES_LIBRARIES} ${ALLEGRO_PRIMITIVES_LIBRARIES})
target_include_directories(allegro_asteroids PUBLIC ${ALLEGRO_INCLUDE_DIRS})
