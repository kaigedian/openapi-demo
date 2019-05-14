project(TestRSA)

if(PROJECT_SOURCE_DIR)
    set(RSATOOL_SRC_DIR ${PROJECT_SOURCE_DIR})
endif()

if(NOT PROJECT_SOURCE_DIR)
    set(RSATOOL_SRC_DIR ${PROJECT_SOURCE_DIR}/..)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(OPENSSL_ROOT_DIR "${RSATOOL_SRC_DIR}/lib/openssl")
find_package(OpenSSL)

set(REA_TOOL_SOURCES
  RSATool.hpp
  TestRSATool.cc
  )

add_executable(${PROJECT_NAME} ${REA_TOOL_SOURCES})
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
