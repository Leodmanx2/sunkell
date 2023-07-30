# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

add_library(sunkell
	common/math/vec2.cpp 
	common/math/vec3.cpp
	common/math/vec4.cpp
	common/math/mat2.cpp
	common/math/mat3.cpp
	common/math/mat4.cpp
	common/math/quat.cpp
	common/ecs/entity.cpp
	common/ecs/component.cpp
	common/ecs/system.cpp
	input.cpp)

# Try to add the Windows App SDK to the include path
# and link to the Universal Windows Platform if on Windows
if(WIN32)
	set(WINDOWS_APP_SDK_PATH "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22621.0\\cppwinrt")
	if(EXISTS ${WINDOWS_APP_SDK_PATH})
		include_directories(${WINDOWS_APP_SDK_PATH})
	endif()
	target_link_libraries(sunkell PRIVATE WindowsApp.lib)
else()
		message(WARNING "Windows App SDK not found at ${WINDOWS_APP_SDK_PATH}")
endif()

target_include_directories(sunkell PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE AND ENABLE_NONPORTABLE_OPTIMIZATIONS)
		target_compile_options(sunkell PRIVATE -march=native)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
	set_target_properties(sunkell PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
