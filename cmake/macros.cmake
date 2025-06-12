macro(declare_target target_name)
    project(${target_name})
    set(PROJECT_TARGET_NAME ${PROJECT_TARGET_PREFIX}${target_name}${PROJECT_TARGET_SUFFIX})
endmacro()

macro(append_target_folder project_folder)
    set(PROJECT_TARGET_VS_SOLUTION_FOLDER_SCOPED ${PROJECT_TARGET_VS_SOLUTION_FOLDER})
    if(DEFINED PROJECT_TARGET_VS_SOLUTION_FOLDER)
        set(PROJECT_TARGET_VS_SOLUTION_FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER}/${project_folder})
    else()
        set(PROJECT_TARGET_VS_SOLUTION_FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER}/${project_folder})
    endif()
endmacro()

macro(revert_target_folder)
    set(PROJECT_TARGET_VS_SOLUTION_FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER_SCOPED})
    set(PROJECT_TARGET_VS_SOLUTION_FOLDER_SCOPED "" )
endmacro()

macro(include_src source_name)
    set(PROJECT_TARGET_SOURCES ${PROJECT_TARGET_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/${source_name})
    set(PROJECT_GROUP_SOURCES ${PROJECT_GROUP_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/${source_name})
endmacro()

macro(include_source_from_var source_variable)
    set(PROJECT_TARGET_SOURCES ${PROJECT_TARGET_SOURCES} ${source_variable})
endmacro()

macro(include_source_list_from_file cmake_file_name)
    set(PROJECT_TARGET_VS_SOLUTION_FOLDER_TEMP ${PROJECT_TARGET_VS_SOLUTION_FOLDER})
    set(PROJECT_TARGET_VS_SOURCE_GROUP_FILTER_TEMP ${PROJECT_TARGET_VS_SOURCE_GROUP_FILTER})
    set(PROJECT_GROUP_SOURCES "")

    include(${CMAKE_CURRENT_LIST_DIR}/${cmake_file_name})

    set(PROJECT_TARGET_VS_SOLUTION_FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER_TEMP})
    set(PROJECT_TARGET_VS_SOURCE_GROUP_FILTER ${PROJECT_TARGET_VS_SOURCE_GROUP_FILTER_TEMP})
endmacro()

macro(group_sources group_name)
    if(WIN32)
        source_group(${PROJECT_TARGET_VS_SOURCE_GROUP_FILTER}/${group_name} FILES ${PROJECT_GROUP_SOURCES})
        set(PROJECT_GROUP_SOURCES "")
    endif()
endmacro()

macro(group_target group_name)
    set(PROJECT_TARGET_VS_SOLUTION_FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER}/${group_name})
    set_target_properties(${PROJECT_TARGET_NAME} PROPERTIES FOLDER ${PROJECT_TARGET_VS_SOLUTION_FOLDER})
endmacro()

macro(make_library_target)
    message(DEBUG "Creating library target: ${PROJECT_TARGET_NAME}")
    add_library(${PROJECT_TARGET_NAME} ${PROJECT_TARGET_SOURCES})
endmacro()

macro(make_shared_library_target)
    message(DEBUG "Creating shared library target: ${PROJECT_TARGET_NAME}")
    add_library(${PROJECT_TARGET_NAME} SHARED ${PROJECT_TARGET_SOURCES})
endmacro()

macro(make_executable_target)
    add_executable(${PROJECT_TARGET_NAME} ${PROJECT_TARGET_SOURCES})
endmacro()

macro(make_win32_executable_target)
    add_executable(${PROJECT_TARGET_NAME} WIN32 ${PROJECT_TARGET_SOURCES})
endmacro()

macro(link_target lib_name)
    target_link_libraries(${PROJECT_TARGET_NAME} ${lib_name})
endmacro()
