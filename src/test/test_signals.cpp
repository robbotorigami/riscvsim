/*
 * test_signals.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cyborg9
 */

#include "test/catch.hpp"
#include "cpucore/Signals.h"

#include <stdint.h>


TEST_CASE("Test that the mux functions correctly", "[signals][mux]"){
	Signal<bool> control;
	Signal<uint32_t> input1, input2, output;
	Mux<uint32_t> mux(input1, input2, control, output);

	SECTION("Ensure that both inputs make it through"){
		input1.setData(0xAA);
		input2.setData(0xBB);
		control.setData(false);
		REQUIRE(output.getData() == 0xAA);
		control.setData(true);
		REQUIRE(output.getData() == 0xBB);
	}
}


