/** @file
    @brief Unit tests for converting EDID vendor ID value to three-letter manufacturer ID.

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Internal Includes
#include <osvr/Display/Display.h>

// Library/third-party includes
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// Standard includes
// - none

TEST_CASE("decodeEdidVendorId", "Examples")
{
    using osvr::display::decodeEdidVendorId;
    CHECK("SVR" == decodeEdidVendorId(0xd24e));
}

TEST_CASE("encodeEdidVendorId", "Examples")
{
    using osvr::display::encodeEdidVendorId;
    CHECK(0xd24e == encodeEdidVendorId("SVR"));
}

TEST_CASE("encodeEdidVendorId", "InvalidInputDigits")
{
    CHECK_THROWS_AS(osvr::display::encodeEdidVendorId("S00"), std::invalid_argument);
}

TEST_CASE("encodeEdidVendorId", "InvalidInputTooLong")
{
    CHECK_THROWS_AS(osvr::display::encodeEdidVendorId("Too long"), std::invalid_argument);
}

TEST_CASE("encodeEdidVendorId", "LowercaseConversion")
{
    CHECK(0xd24e == osvr::display::encodeEdidVendorId("svr"));
}

