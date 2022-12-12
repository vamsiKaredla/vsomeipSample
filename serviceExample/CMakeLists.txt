cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-g -std=c++0x")

set (VSOMEIP_INCLUDE_DIRS "/home/mob/Documents/vsomeip/vsomeip/interface/")
set (VSOMEIP_LINK_DIR "/home/mob/Documents/vsomeip/vsomeip/build")

find_package(vsomeip3 2.6.0 REQUIRED)

find_package(Boost 1.55 COMPONENTS system thread log REQUIRED)

include_directories (
	${Boost_INCLUDE_DIR}
	${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service-example service-example.cpp)

#target_link_directories(service-example PUBLIC ${VSOMEIP_LINK_DIR})

target_link_libraries(service-example vsomeip3 ${BOOST_LIBRARIES})

