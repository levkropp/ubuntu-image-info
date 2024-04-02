cmake_minimum_required (VERSION 3.8)
project ("ubuntu_image_info")

#Using c++17
set(CMAKE_CXX_STANDARD 17)

#Include include/
include_directories(include)

#Include nlohmann/json
include_directories(external/json)


# Add source to this project's executable.
add_executable (ubuntu_image_info "src/main.cpp" "include/ubuntu_image_info.h" "src/ubuntu_image_info.cpp")

if (WIN32) #curl installed with Visual Studio 2022 vcpkg is required

    include("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")

    find_package(CURL CONFIG REQUIRED)
    target_link_libraries(ubuntu_image_info PRIVATE CURL::libcurl)

else()

    find_package(CURL REQUIRED)
    include_directories(${CURL_INCLUDE_DIRS})

    target_link_libraries(ubuntu_image_info ${CURL_LIBRARIES})

endif()



# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ubuntu_image_info PROPERTY CXX_STANDARD 20)
endif()

