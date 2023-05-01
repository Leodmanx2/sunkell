# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

add_library(sunkell
	common/math/vec2.cpp 
	common/math/vec3.cpp
	common/math/vec4.cpp
	common/math/mat2.cpp
	common/math/mat2.cpp)

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
