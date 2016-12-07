/** @file
    @brief Unit tests for orientation and rotation math functions in Display.h

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
#include <osvr/Display/DisplayIO.h>

// Library/third-party includes
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// Standard includes
// - none

using R = ::osvr::display::Rotation;
using O = ::osvr::display::DesktopOrientation;
using SO = ::osvr::display::ScanOutOrigin;

TEST_CASE("Difference between orientations")
{
    CHECK(R::Zero == O::Landscape - O::Landscape);
    CHECK(R::Zero == O::LandscapeFlipped - O::LandscapeFlipped);
    CHECK(R::Zero == O::Portrait - O::Portrait);
    CHECK(R::Zero == O::PortraitFlipped - O::PortraitFlipped);

    CHECK(R::Ninety == O::Landscape - O::Portrait);
    CHECK(R::Ninety == O::PortraitFlipped - O::Landscape);
    CHECK(R::Ninety == O::LandscapeFlipped - O::PortraitFlipped);
    CHECK(R::Ninety == O::Portrait - O::LandscapeFlipped);

    CHECK(R::OneEighty == O::Landscape - O::LandscapeFlipped);
    CHECK(R::OneEighty == O::LandscapeFlipped - O::Landscape);
    CHECK(R::OneEighty == O::Portrait - O::PortraitFlipped);
    CHECK(R::OneEighty == O::PortraitFlipped - O::Portrait);

    CHECK(R::TwoSeventy == O::Portrait - O::Landscape);
    CHECK(R::TwoSeventy == O::LandscapeFlipped - O::Portrait);
    CHECK(R::TwoSeventy == O::PortraitFlipped  - O::LandscapeFlipped);
    CHECK(R::TwoSeventy == O::Landscape - O::PortraitFlipped);
}

TEST_CASE("Add rotation to orientation")
{
    CHECK(O::Landscape == O::Landscape + R::Zero);
    CHECK(O::LandscapeFlipped == O::LandscapeFlipped + R::Zero);
    CHECK(O::Portrait == O::Portrait + R::Zero);
    CHECK(O::PortraitFlipped == O::PortraitFlipped + R::Zero);

    // Flip operands
    CHECK(O::Landscape == R::Zero + O::Landscape);
    CHECK(O::LandscapeFlipped == R::Zero + O::LandscapeFlipped);
    CHECK(O::Portrait == R::Zero + O::Portrait);
    CHECK(O::PortraitFlipped == R::Zero + O::PortraitFlipped);

    CHECK(O::PortraitFlipped == O::Landscape + R::Ninety);
    CHECK(O::Portrait == O::LandscapeFlipped + R::Ninety);
    CHECK(O::Landscape == O::Portrait + R::Ninety);
    CHECK(O::LandscapeFlipped == O::PortraitFlipped + R::Ninety);

    // Flip operands
    CHECK(O::PortraitFlipped == R::Ninety + O::Landscape);
    CHECK(O::Portrait == R::Ninety + O::LandscapeFlipped);
    CHECK(O::Landscape == R::Ninety + O::Portrait);
    CHECK(O::LandscapeFlipped == R::Ninety + O::PortraitFlipped);

    CHECK(O::LandscapeFlipped == O::Landscape + R::OneEighty);
    CHECK(O::Landscape == O::LandscapeFlipped + R::OneEighty);
    CHECK(O::PortraitFlipped == O::Portrait + R::OneEighty);
    CHECK(O::Portrait == O::PortraitFlipped + R::OneEighty);

    // Flip operands
    CHECK(O::LandscapeFlipped == R::OneEighty + O::Landscape);
    CHECK(O::Landscape == R::OneEighty + O::LandscapeFlipped);
    CHECK(O::PortraitFlipped == R::OneEighty + O::Portrait);
    CHECK(O::Portrait == R::OneEighty + O::PortraitFlipped);

    CHECK(O::Portrait == O::Landscape + R::TwoSeventy);
    CHECK(O::PortraitFlipped == O::LandscapeFlipped + R::TwoSeventy);
    CHECK(O::LandscapeFlipped == O::Portrait + R::TwoSeventy);
    CHECK(O::Landscape == O::PortraitFlipped + R::TwoSeventy);

    // Flip operands
    CHECK(O::Portrait == R::TwoSeventy + O::Landscape);
    CHECK(O::PortraitFlipped == R::TwoSeventy + O::LandscapeFlipped);
    CHECK(O::LandscapeFlipped == R::TwoSeventy + O::Portrait);
    CHECK(O::Landscape == R::TwoSeventy + O::PortraitFlipped);
}

TEST_CASE("Subtract rotation from orientation")
{
    CHECK(O::Landscape == O::Landscape - R::Zero);
    CHECK(O::LandscapeFlipped == O::LandscapeFlipped - R::Zero);
    CHECK(O::Portrait == O::Portrait - R::Zero);
    CHECK(O::PortraitFlipped == O::PortraitFlipped - R::Zero);

    CHECK(O::Portrait == O::Landscape - R::Ninety);
    CHECK(O::PortraitFlipped == O::LandscapeFlipped - R::Ninety);
    CHECK(O::LandscapeFlipped == O::Portrait - R::Ninety);
    CHECK(O::Landscape == O::PortraitFlipped - R::Ninety);

    CHECK(O::LandscapeFlipped == O::Landscape - R::OneEighty);
    CHECK(O::Landscape == O::LandscapeFlipped - R::OneEighty);
    CHECK(O::PortraitFlipped == O::Portrait - R::OneEighty);
    CHECK(O::Portrait == O::PortraitFlipped - R::OneEighty);

    CHECK(O::PortraitFlipped == O::Landscape - R::TwoSeventy);
    CHECK(O::Portrait == O::LandscapeFlipped - R::TwoSeventy);
    CHECK(O::Landscape == O::Portrait - R::TwoSeventy);
    CHECK(O::LandscapeFlipped == O::PortraitFlipped - R::TwoSeventy);
}

TEST_CASE("Negate rotation")
{
    CHECK(R::Zero == -R::Zero);
    CHECK(R::TwoSeventy == -R::Ninety);
    CHECK(R::OneEighty == -R::OneEighty);
    CHECK(R::Ninety == -R::TwoSeventy);
}

TEST_CASE("Add scan out origin and rotation")
{
    CHECK(O::Landscape == SO::UpperLeft + R::Zero);
    CHECK(O::PortraitFlipped == SO::UpperLeft + R::Ninety);
    CHECK(O::LandscapeFlipped == SO::UpperLeft + R::OneEighty);
    CHECK(O::Portrait == SO::UpperLeft + R::TwoSeventy);

    CHECK(O::Portrait == SO::UpperRight + R::Zero);
    CHECK(O::Landscape == SO::UpperRight + R::Ninety);
    CHECK(O::PortraitFlipped == SO::UpperRight + R::OneEighty);
    CHECK(O::LandscapeFlipped == SO::UpperRight + R::TwoSeventy);

    CHECK(O::LandscapeFlipped == SO::LowerRight + R::Zero);
    CHECK(O::Portrait == SO::LowerRight + R::Ninety);
    CHECK(O::Landscape == SO::LowerRight + R::OneEighty);
    CHECK(O::PortraitFlipped == SO::LowerRight + R::TwoSeventy);

    CHECK(O::PortraitFlipped == SO::LowerLeft + R::Zero);
    CHECK(O::LandscapeFlipped == SO::LowerLeft + R::Ninety);
    CHECK(O::Portrait == SO::LowerLeft + R::OneEighty);
    CHECK(O::Landscape == SO::LowerLeft + R::TwoSeventy);
}

TEST_CASE("Convert desktop orientation to scan out origin")
{
    CHECK(SO::UpperLeft ==  to_ScanOutOrigin(O::Landscape));
    CHECK(SO::UpperRight == to_ScanOutOrigin(O::PortraitFlipped));
    CHECK(SO::LowerRight == to_ScanOutOrigin(O::LandscapeFlipped));
    CHECK(SO::LowerLeft ==  to_ScanOutOrigin(O::Portrait));
}

TEST_CASE("rotation scan out origin")
{
    CHECK(SO::UpperLeft ==  to_ScanOutOrigin(SO::UpperLeft + R::Zero));
    CHECK(SO::UpperRight == to_ScanOutOrigin(SO::UpperLeft + R::Ninety));
    CHECK(SO::LowerRight == to_ScanOutOrigin(SO::UpperLeft + R::OneEighty));
}

TEST_CASE("Convert integer to rotation enum value")
{
    using osvr::display::to_Rotation;
    CHECK(R::Zero == to_Rotation(0));
    CHECK(R::Ninety == to_Rotation(90));
    CHECK(R::Ninety == to_Rotation(-270));
    CHECK(R::OneEighty == to_Rotation(180));
    CHECK(R::OneEighty == to_Rotation(-180));
    CHECK(R::TwoSeventy == to_Rotation(270));
    CHECK(R::TwoSeventy == to_Rotation(-90));
    CHECK_THROWS_AS(to_Rotation(-1), std::invalid_argument);
    CHECK_THROWS_AS(to_Rotation(1), std::invalid_argument);
}

