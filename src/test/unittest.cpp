/*
 * test_simple.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: cyborg9
 */
#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"

#include "util/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

TEST_CASE("Simple Test", "[dummy]"){
	REQUIRE(1 == 1);
}

