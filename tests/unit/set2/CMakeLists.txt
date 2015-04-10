set(PACKAGE_NAME cdsu-set)

set(CDSUNIT_SET_SOURCES
	set_insdel_func.cpp
	set_insdel_func2.cpp
	set_insdel_func3.cpp
	set_insdel_func4.cpp
	set_insdel_func5.cpp
	set_insdel_func6.cpp
	set_insdel_func7.cpp
	set_insdel_string.cpp
	set_insdelfind.cpp
	set_delodd.cpp)

add_executable(${PACKAGE_NAME} ${CDSUNIT_SET_SOURCES} $<TARGET_OBJECTS:${TEST_COMMON}>)
target_link_libraries(${PACKAGE_NAME} ${CDS_SHARED_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME ${PACKAGE_NAME} COMMAND ${PACKAGE_NAME})