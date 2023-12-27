add_library(${PROJECT_NAME} SHARED)

set_compiler_flags(${PROJECT_NAME})

if (${PROJECT_NAME}_PRECOMPILED_HEADERS)
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}.hpp)
endif ()

set(BASE_FILES
        Base/Log.hpp
        Base/Log.cpp
        Base/TypeName.hpp
)

set(CORE_FILES
        Core/Defines.hpp
        Core/Core.cpp
        Core/Core.hpp
        Core/Macros.hpp
)

set(MATH_FILES
        Math/Numerical.hpp
)

source_group("Base" FILES ${BASE_FILES})
source_group("Core" FILES ${CORE_FILES})
source_group("Math" FILES ${MATH_FILES})

target_sources(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}.hpp
        ${CORE_FILES}
        ${BASE_FILES}
        ${MATH_FILES}
)

target_compile_features(${PROJECT_NAME}
        PUBLIC cxx_std_23
        PRIVATE cxx_std_23
)

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG>
        # Windows
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
        $<$<PLATFORM_ID:Windows>:UNICODE>
        # MSVC C++ 
        $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>
        $<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        $<$<CXX_COMPILER_ID:MSVC>:_ENABLE_EXTENDED_ALIGNED_STORAGE>
        $<$<CXX_COMPILER_ID:MSVC>:_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING>
        # Clang.
        $<$<CXX_COMPILER_ID:Clang>:_MSC_EXTENSIONS> # enable MS extensions
        PRIVATE
        $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>
        ${PROJECT_NAME_UPPERCASE}_DLL
)

target_compile_options(${PROJECT_NAME}
        PUBLIC
        # MSVC
        $<$<CXX_COMPILER_ID:MSVC>:/DEBUG>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME_UPPERCASE}_RUNTIME_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME_UPPERCASE}_LIBRARY_OUTPUT_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})