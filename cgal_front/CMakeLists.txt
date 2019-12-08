project( cgal_link )


cmake_minimum_required(VERSION 2.8.11)


# set(CMAKE_CXX_COMPILER "clang++")

find_package(CGAL QUIET COMPONENTS Core )

if ( NOT CGAL_FOUND )
  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()

endif()


include( ${CGAL_USE_FILE} )


find_package(Boost COMPONENTS thread REQUIRED)

if ( NOT Boost_FOUND )
  message(STATUS "This project requires the Boost library, and will not be compiled.")
  return()

endif()

# cgal
if (USE_CGAL)
  set(CGAL_DIR ${3rdParty_DIR}/cgal)
  find_package(CGAL REQUIRED)
  include(${CGAL_USE_FILE})
endif()


add_executable( cgal_link main.cpp )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS cgal_link )

target_link_libraries(cgal_link   ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )
