cmake_minimum_required(VERSION 3.10)

project(cmake-install)

add_library(cmake-install SHARED src/Hello.cpp)
target_include_directories(cmake-install PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(cmake-install-bin src/main.cpp)
target_link_libraries(cmake-install-bin PRIVATE cmake-install)

# install
# usr/local/bin
install(TARGETS cmake-install-bin DESTINATION bin)
# usr/local/lib
install(TARGETS cmake-install LIBRARY DESTINATION lib)
# usr/local/include
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
# usr/local/etc
install(FILES cmake-examples.conf DESTINATION etc)