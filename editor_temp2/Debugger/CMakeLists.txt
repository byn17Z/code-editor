# 设置库名称
project(Debugger)



# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/header)

# 添加源文件
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 添加库
add_library(debugger_lib ${SOURCES})


