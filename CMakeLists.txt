cmake_minimum_required(VERSION 3.27)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# --------------------------------------------------------------
# 项目名称
# --------------------------------------------------------------
project(Iris
        LANGUAGES CXX C
        VERSION 0.0.1)

# --------------------------------------------------------------
# 配置选项
# --------------------------------------------------------------

# 定义项目名的大写/小写
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)

# 包含 cmake 工具
include(CompilerFlags)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# 检查当前的系统
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(${PROJECT_NAME_UPPERCASE}_PLATFORM "Windows")
    set(${PROJECT_NAME_UPPERCASE}_IN_WINDOWS TRUE)
else ()
    message(WARNING "当前程序仅支持 Windows 平台")
endif ()

# 全局编译选项
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# --------------------------------------------------------------
# 全局设置
# --------------------------------------------------------------

# 是否启用预编译头
set(${PROJECT_NAME_UPPERCASE}_PRECOMPILED_HEADERS ON CACHE BOOL "启用预编译头")

set(${PROJECT_NAME_UPPERCASE}_BUILD_TESTS ON CACHE BOOL "开启构建项目测试")

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)

# 输出目录
set(${PROJECT_NAME_UPPERCASE}_RUNTIME_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(${PROJECT_NAME_UPPERCASE}_LIBRARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_CONFIGURATION_TYPES)
    # 多配置
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING "" FORCE)
else ()
    # 单配置
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of build")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;MinSizeRel;RelWithDebInfo")
endif ()

if (CMAKE_CONFIGURATION_TYPES)
    set(${PROJECT_NAME_UPPERCASE}_OUTPUT_DIR ${${PROJECT_NAME_UPPERCASE}_RUNTIME_OUTPUT_DIR}/$<CONFIG>)
else ()
    set(${PROJECT_NAME_UPPERCASE}_OUTPUT_DIR ${${PROJECT_NAME_UPPERCASE}_RUNTIME_OUTPUT_DIR})
endif ()

# --------------------------------------------------------------
# 一些工具
# --------------------------------------------------------------
# 拷贝数据文件
add_custom_target(copy_data_folder ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Data ${${PROJECT_NAME_UPPERCASE}_OUTPUT_DIR}/Data)
set_target_properties(copy_data_folder PROPERTIES FOLDER "Misc")

# --------------------------------------------------------------
# 添加项目
# --------------------------------------------------------------

######################################
# 主项目库
add_subdirectory(Source/Iris)

add_dependencies(Iris copy_data_folder)

######################################
# 测试
if (${PROJECT_NAME_UPPERCASE}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif ()