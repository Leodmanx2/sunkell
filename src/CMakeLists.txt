# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

add_library(sunkell engine.cpp subsystem.cpp)

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
