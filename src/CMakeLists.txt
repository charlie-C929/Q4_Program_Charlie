# 查找在此路径下的所有源文件
aux_source_directory (. SRC_LIST)

# 使用给定的源文件，为工程引入一个可执行文件
add_executable (demo ${SRC_LIST})

# 引用Eigen库，如果在win10下找不到eigen库，则将下面一行的#删掉
# set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

#这里设定把生成的可执行文件放到根目录下的bin目录下
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)