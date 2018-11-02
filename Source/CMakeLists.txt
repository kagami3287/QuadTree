cmake_minimum_required (VERSION 3.12)
project (QuadTree)

set (LIBRARY_DIR QuadTree)
set(SOURCE_FILE_SAMPLE Testing/SampleCode.cpp Testing/ProfileCPU.h)

file(GLOB HEADER_FILES ${LIBRARY_DIR}/*.h)
file(GLOB SOURCE_FILES ${LIBRARY_DIR}/*.cpp)

add_library(QuadTree STATIC ${HEADER_FILES} ${SOURCE_FILES})

OPTION(BUILD_EXAMPLE "Build QuadTree examples." OFF)

if(BUILD_EXAMPLE)
	add_executable(QuadTreeSample ${SOURCE_FILE_SAMPLE})
	add_dependencies(QuadTreeSample QuadTree)
	target_include_directories(QuadTreeSample PRIVATE ${LIBRARY_DIR})
	target_link_libraries(QuadTreeSample QuadTree)
endif()

install(TARGETS QuadTree DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)