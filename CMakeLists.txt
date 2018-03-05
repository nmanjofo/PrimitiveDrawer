cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "PrimitiveDrawer")

project(${PROJECT_NAME})

set(PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)


set(SRC_FILES
	src/main.cpp
	src/AbstractPrimitiveDrawer.hpp
	src/Application.cpp
	src/Console.cpp
	src/CubeDrawer.cpp
	src/GLProgram.cpp
	src/LineDrawer.cpp
	src/OrbitalCamera.cpp
	src/Plane.cpp
	src/PlaneDrawer.cpp
	src/PrimitiveParser.cpp
	src/PrimitiveRenderer.cpp
	src/ShaderCompiler.cpp
	src/Tokenizer.cpp
)

set(HEADER_FILES
	src/AbstractPrimitiveDrawer.cpp
	src/Application.hpp
	src/Console.hpp
	src/CubeDrawer.hpp
	src/CubeParams.hpp
	src/GLProgram.hpp
	src/LineDrawer.hpp
	src/LineParams.hpp
	src/OrbitalCamera.hpp
	src/Plane.hpp
	src/PlaneDrawer.hpp
	src/PlaneParams.hpp
	src/PrimitiveParser.hpp
	src/PrimitiveType.hpp
	src/PrimitiveParam.hpp
	src/Primitive.hpp
	src/PrimitiveRenderer.hpp
	src/ShaderCompiler.hpp
	src/Tokenizer.hpp
	src/TokenDescriptors.hpp
)

# Set binary output to /bin
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR} )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BIN_DIR} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BIN_DIR} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BIN_DIR} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

include_directories(${PROJECT_NAME} PUBLIC 
	${GLEW_INCLUDE_DIR} 
	${SDL2_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}
	)
	
target_link_libraries(${PROJECT_NAME}
	${GLEW_LIBRARIES} 
	${SDL2_LIBRARY} 
	${OPENGL_gl_LIBRARY}
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BIN_DIR}")
