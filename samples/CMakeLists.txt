# Example use of awaituv

add_executable (test1 test1.cpp)
add_executable (test2 test2.cpp)
add_executable (test3 test3.cpp)
add_executable (test5 test5.cpp)
add_executable (test6 test6.cpp)
add_executable (boost_sample boost_sample.cpp)
add_executable (smiz smiz.cpp)
add_executable (boost_coroutines boost_coroutines.cpp)
target_link_libraries(boost_sample ${Boost_LIBRARIES})
target_link_libraries(boost_coroutines ${Boost_LIBRARIES})
