macro(declare_project project_name)
    project(${project_name})
    set(PROJECT_TARGET_NAME ${PROJECT_PREFIX}${project_name}${PROJECT_TARGET_SUFFIX})
endmacro()

macro(append_target_folder project_folder)
    set(PROJECT_TARGET_FOLDER ${PROJECT_TARGET_FOLDER}/${project_folder})
endmacro()

macro(append_src_group_folder group_name)
    set(PROJECT_TARGET_SOURCE_FILTER ${PROJECT_TARGET_SOURCE_FILTER}/${group_name})
endmacro()

macro(include_src source_name)
    set(PROJECT_TARGET_SOURCES ${PROJECT_TARGET_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/${source_name})
    set(PROJECT_GROUP_SOURCES ${PROJECT_GROUP_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/${source_name})
endmacro()

macro(include_source_list_from_file cmake_file_name)
    set(PROJECT_TARGET_FOLDER_TEMP ${PROJECT_TARGET_FOLDER})
    set(PROJECT_TARGET_SOURCE_FILTER_TEMP ${PROJECT_TARGET_SOURCE_FILTER})
    set(PROJECT_GROUP_SOURCES "")

    include(${CMAKE_CURRENT_LIST_DIR}/${cmake_file_name})

    set(PROJECT_TARGET_FOLDER ${PROJECT_TARGET_FOLDER_TEMP})
    set(PROJECT_TARGET_SOURCE_FILTER ${PROJECT_TARGET_SOURCE_FILTER_TEMP})
endmacro()

macro(group_sources group_name)
    message("Adding ${PROJECT_GROUP_SOURCES} to source group : ${PROJECT_TARGET_SOURCE_FILTER}/${group_name}")
    if(WIN32)
        source_group(${PROJECT_TARGET_SOURCE_FILTER}/${group_name} FILES ${PROJECT_GROUP_SOURCES})
        set(PROJECT_GROUP_SOURCES "")
    endif()
endmacro()

macro(group_target group_name)
    set(PROJECT_TARGET_FOLDER ${PROJECT_TARGET_FOLDER}/${group_name})
    set_target_properties(${PROJECT_TARGET_NAME} PROPERTIES FOLDER ${PROJECT_TARGET_FOLDER})
endmacro()

macro(make_library_target)
    add_library(${PROJECT_TARGET_NAME} ${PROJECT_TARGET_SOURCES})
endmacro()

macro(make_executable_target)
    add_executable(${PROJECT_TARGET_NAME} ${PROJECT_TARGET_SOURCES})
endmacro()
