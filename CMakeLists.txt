cmake_minimum_required(VERSION 3.13)
project(GraphicalAspects)

set(CMAKE_CXX_STANDARD 14)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

include_directories(GraphicalAspects)
include_directories(GraphicalAspects/Buffer)
include_directories(GraphicalAspects/Data)
include_directories(GraphicalAspects/Mesh)
include_directories(GraphicalAspects/Parser)
include_directories(GraphicalAspects/Rasterizer)
include_directories(GraphicalAspects/Tests)
include_directories(GraphicalAspects/VertexProcessor)

add_executable(GraphicalAspects
        GraphicalAspects/Buffer/Buffer.cpp
        GraphicalAspects/Buffer/Buffer.h
        GraphicalAspects/Buffer/ITgaSavable.h
        GraphicalAspects/Buffer/TgaBuffer.cpp
        GraphicalAspects/Buffer/TgaBuffer.h
        GraphicalAspects/Data/math_structs.cpp
        GraphicalAspects/Data/math_structs.h
        GraphicalAspects/Data/Triangle.cpp
        GraphicalAspects/Data/Triangle.h
        GraphicalAspects/Mesh/cone_mesh.cpp
        GraphicalAspects/Mesh/cone_mesh.h
        GraphicalAspects/Mesh/CubeMesh.cpp
        GraphicalAspects/Mesh/CubeMesh.h
        GraphicalAspects/Mesh/cylinder_mesh.cpp
        GraphicalAspects/Mesh/cylinder_mesh.h
        GraphicalAspects/Mesh/mesh.cpp
        GraphicalAspects/Mesh/mesh.h
        GraphicalAspects/Mesh/TriangleMesh.cpp
        GraphicalAspects/Mesh/TriangleMesh.h
        GraphicalAspects/Mesh/vertex.cpp
        GraphicalAspects/Mesh/vertex.h
        GraphicalAspects/Parser/objParser.cpp
        GraphicalAspects/Parser/objParser.h
        GraphicalAspects/Rasterizer/Rasterizer.cpp
        GraphicalAspects/Rasterizer/Rasterizer.h
        GraphicalAspects/Tests/main_tests.h
        GraphicalAspects/Tests/tests.cpp
        GraphicalAspects/Tests/tests.h
        GraphicalAspects/VertexProcessor/VertexProcessor.cpp
        GraphicalAspects/VertexProcessor/VertexProcessor.h
        GraphicalAspects/main.cpp
        GraphicalAspects/utils.h GraphicalAspects/Light/Light.h GraphicalAspects/Light/light.cpp GraphicalAspects/Texture/texture.h GraphicalAspects/Texture/texture.cpp GraphicalAspects/Timer/timer.cpp GraphicalAspects/Timer/timer.h)

#target_link_libraries(GraphicalAspects ${SDL2_LIBRARIES})