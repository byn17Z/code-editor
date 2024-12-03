# 设置库名称
project(Lexical)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR})

# 添加源文件
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

# 添加库
add_library(Lexical ${SOURCES})