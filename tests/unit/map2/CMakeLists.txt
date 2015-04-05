set(PACKAGE_NAME cdsu-map)

set(CDSUNIT_MAP_SOURCES
    map_find_int.cpp
    map_find_string.cpp
    map_insdel_func.cpp
    map_insdel_int.cpp
    map_insdel_item_int.cpp
    map_insdel_string.cpp
    map_insdel_item_string.cpp
    map_insfind_int.cpp
    map_insdelfind.cpp
    map_delodd.cpp)

add_executable(${PACKAGE_NAME} ${CDSUNIT_MAP_SOURCES} $<TARGET_OBJECTS:${TEST_COMMON}>)
target_link_libraries(${PACKAGE_NAME} ${CDS_SHARED_LIBRARY} ${Boost_THREAD_LIBRARY})
add_test(NAME ${PACKAGE_NAME} COMMAND ${PACKAGE_NAME})