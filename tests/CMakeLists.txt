# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

if(BUILD_TESTING)
	find_package(doctest REQUIRED)
	add_executable(run_tests test_runner.cpp)
	target_link_libraries(run_tests PRIVATE doctest::doctest sunkell)
	add_test(NAME tests COMMAND run_tests)
endif()
