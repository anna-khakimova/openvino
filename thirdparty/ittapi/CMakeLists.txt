# ******************************************************************************
# Copyright 2017-2021 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ******************************************************************************

if(ENABLE_PROFILING_ITT)
    if(DEFINED INTEL_VTUNE_DIR OR DEFINED ENV{INTEL_VTUNE_DIR})
        find_package(ITT
                     PATHS "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
                     NO_DEFAULT_PATH)
        if(NOT ITT_FOUND)
            message(WARNING "Profiling option enabled, but no ITT library was found under INTEL_VTUNE_DIR")
        endif()
    else()
        include(FetchContent)
        FetchContent_Declare(
            ext_ittapi
            GIT_REPOSITORY https://github.com/intel/ittapi.git
            GIT_TAG v3.18.6
        )

        FetchContent_GetProperties(ext_ittapi)
        if(NOT ext_ittapi_POPULATED)
            FetchContent_Populate(ext_ittapi)
            add_subdirectory(${ext_ittapi_SOURCE_DIR} ${ext_ittapi_BINARY_DIR})
        endif()

        target_compile_definitions(ittnotify INTERFACE ENABLE_PROFILING_ITT)
        if (UNIX)
            target_compile_options(ittnotify PRIVATE -Wno-undef)
        endif()

        openvino_developer_export_targets(COMPONENT openvino_common TARGETS ittnotify)
    endif()
endif()
