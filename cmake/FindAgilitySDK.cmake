# FindAgilitySDK.cmake

# Define a CMake module to find the Agility SDK

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.21)

set(AgilitySDK_Found FALSE CACHE BOOL "Agility SDK exists" FORCE)
set(AgilitySdk_Version "1.614.0" CACHE STRING "Agility SDK version" FORCE)
set(AgilitySdk_Path "${PROJECT_EXTERNAL_SOURCE_DIR}/agility_sdk/${AgilitySdk_Version}/" CACHE PATH "Agility SDK path" FORCE)
set(AgilitySdk_Include "" CACHE PATH "Agility SDK include path" FORCE)
set(AgilitySdk_Lib "" CACHE PATH "Agility SDK library path" FORCE)


# Define a function to download the Agility SDK using PowerShell
function(download_agility_sdk)
    # Define the PowerShell script to download the Agility SDK
    find_path(AGILITY_SDK_INCLUDE_DIR_CHECK NAMES d3d12.h PATHS ${AgilitySdk_Path}/build/native/include/ NO_CACHE)

    if(AGILITY_SDK_INCLUDE_DIR_CHECK)
        return()
    endif()

    message("Downloading Agility SDK...")
    set(download_script "
        \$url = 'https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/1.614.0'
        \$output = 'agility_sdk.zip'
        Invoke-WebRequest -Uri \$url -OutFile \$output
        Expand-Archive -Path \$output -DestinationPath ${AgilitySdk_Path}
        Remove-Item -Path \$output
    ")

    # Execute the PowerShell script
    execute_process(
        COMMAND powershell -Command "${download_script}"
        RESULT_VARIABLE result
    )

    # Check if the download was successful
    if(result EQUAL 0)
        message(STATUS "Agility SDK downloaded successfully in ${AgilitySdk_Path}")
    else()
        message(FATAL_ERROR "Failed to download Agility SDK")
    endif()
endfunction()

# Define a function to find the Agility SDK
function(find_agility_sdk)
    # Search for the Agility SDK
    message("Searching in ${AgilitySdk_Path}/build/native/include")

    download_agility_sdk()
    find_path(AGILITY_SDK_INCLUDE_DIR NAMES d3d12.h PATHS ${AgilitySdk_Path}/build/native/include/ NO_CACHE)

    # Check if the Agility SDK is found
    if(AGILITY_SDK_INCLUDE_DIR)
        message(STATUS "Agility SDK found: ${AGILITY_SDK_INCLUDE_DIR}")
        set(${AgilitySDK_Found} TRUE CACHE BOOL "Agility SDK exists" FORCE)
        set(AgilitySdk_Include ${AgilitySdk_Path}/build/native/include/ CACHE PATH "Agility SDK include path" FORCE)
        set(AgilitySdk_Lib ${AgilitySdk_Path}/build/native/bin/x64/ CACHE PATH "Agility SDK library path" FORCE)
    else()
        message(FATAL_ERROR "Agility SDK not found")
    endif()
endfunction()

# Call the function to find the Agility SDK
find_agility_sdk()