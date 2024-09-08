# cmake_minimum_required(VERSION 3.12)
# PROJECT(YIBO_SERVER LANGUAGES CXX)

# #CPP VERSION CPP-17
# set(CMAKE_CXX_STANDARD 17)

# #执行目标 ./run
# set(EXECUTE_OBJ run)    

# #设置执行目标的输出路径
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# #添加 ./main.cpp
# # aux_source_directory(log_info SUB_SOURCE)

# # aux_source_directory(. SOURCE)

# #添加 log_info 子文件夹至编译路径
# # aux_source_directory(log_info )

# include_directories(include log_info)
# # include_directories("./log_info")

# # message(${SOURCE} ${SUB_SOURCE})


# # ./run <- main.cpp 
# add_executable(${EXECUTE_OBJ} main.cpp log_info/log_info.cpp)

# #添加头文件路径
# # target_include_directories(${EXECUTE_OBJ} PUBLIC "./include")

# #添加 log_info 子文件夹至头文件
# # target_include_directories(${EXECUTE_OBJ} PUBLIC "./log_info")

cmake_minimum_required(VERSION 3.12)

PROJECT(YIBO_SERVER LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTE_OBJ run)

#头文件夹添加
include_directories(include 
                    server
                    bussiness
                    socket)

#源码添加
aux_source_directory(. SOURCE)

aux_source_directory(include SOURCE_INCLUDE)

aux_source_directory(server SOURCE_SERVER)

aux_source_directory(bussiness SOURCE_BUSSINESS)

aux_source_directory(socket SOURCE_SOCKET)

#执行目标
add_executable(${EXECUTE_OBJ} 
                ${SOURCE} 
                ${SOURCE_INCLUDE}
                ${SOURCE_SERVER}
                ${SOURCE_BUSSINESS}
                ${SOURCE_SOCKET})