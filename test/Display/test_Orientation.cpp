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
#include "Display.h"
#include "DisplayIO.h"

// Library/third-party includes
#include <gtest/gtest.h>

// Standard includes
// - none

using R = ::osvr::display::Rotation;
using O = ::osvr::display::DesktopOrientation;

TEST(DifferenceBetweenOrientations, Identity)
{
    EXPECT_EQ(R::Zero, O::Landscape - O::Landscape);
    EXPECT_EQ(R::Zero, O::LandscapeFlipped - O::LandscapeFlipped);
    EXPECT_EQ(R::Zero, O::Portrait - O::Portrait);
    EXPECT_EQ(R::Zero, O::PortraitFlipped - O::PortraitFlipped);
}

TEST(DifferenceBetweenOrientations, Ninety)
{
    EXPECT_EQ(R::Ninety, O::Landscape - O::PortraitFlipped);
    EXPECT_EQ(R::Ninety, O::Portrait - O::Landscape);
    EXPECT_EQ(R::Ninety, O::LandscapeFlipped - O::Portrait);
    EXPECT_EQ(R::Ninety, O::PortraitFlipped - O::LandscapeFlipped);
}

TEST(DifferenceBetweenOrientations, OneEighty)
{
    EXPECT_EQ(R::OneEighty, O::Landscape - O::LandscapeFlipped);
    EXPECT_EQ(R::OneEighty, O::LandscapeFlipped - O::Landscape);
    EXPECT_EQ(R::OneEighty, O::Portrait - O::PortraitFlipped);
    EXPECT_EQ(R::OneEighty, O::PortraitFlipped - O::Portrait);
}

TEST(DifferenceBetweenOrientations, TwoSeventy)
{
    EXPECT_EQ(R::TwoSeventy, O::PortraitFlipped - O::Landscape);
    EXPECT_EQ(R::TwoSeventy, O::Landscape - O::Portrait);
    EXPECT_EQ(R::TwoSeventy, O::Portrait - O::LandscapeFlipped);
    EXPECT_EQ(R::TwoSeventy, O::LandscapeFlipped - O::PortraitFlipped);
}

TEST(AddRotationToOrientation, Zero)
{
    EXPECT_EQ(O::Landscape, O::Landscape + R::Zero);
    EXPECT_EQ(O::LandscapeFlipped, O::LandscapeFlipped + R::Zero);
    EXPECT_EQ(O::Portrait, O::Portrait + R::Zero);
    EXPECT_EQ(O::PortraitFlipped, O::PortraitFlipped + R::Zero);

    // Flip operands
    EXPECT_EQ(O::Landscape, R::Zero + O::Landscape);
    EXPECT_EQ(O::LandscapeFlipped, R::Zero + O::LandscapeFlipped);
    EXPECT_EQ(O::Portrait, R::Zero + O::Portrait);
    EXPECT_EQ(O::PortraitFlipped, R::Zero + O::PortraitFlipped);
}

TEST(AddRotationToOrientation, Ninety)
{
    EXPECT_EQ(O::Portrait, O::Landscape + R::Ninety);
    EXPECT_EQ(O::PortraitFlipped, O::LandscapeFlipped + R::Ninety);
    EXPECT_EQ(O::LandscapeFlipped, O::Portrait + R::Ninety);
    EXPECT_EQ(O::Landscape, O::PortraitFlipped + R::Ninety);

    // Flip operands
    EXPECT_EQ(O::Portrait, R::Ninety + O::Landscape);
    EXPECT_EQ(O::PortraitFlipped, R::Ninety + O::LandscapeFlipped);
    EXPECT_EQ(O::LandscapeFlipped, R::Ninety + O::Portrait);
    EXPECT_EQ(O::Landscape, R::Ninety + O::PortraitFlipped);
}

TEST(AddRotationToOrientation, OneEighty)
{
    EXPECT_EQ(O::LandscapeFlipped, O::Landscape + R::OneEighty);
    EXPECT_EQ(O::Landscape, O::LandscapeFlipped + R::OneEighty);
    EXPECT_EQ(O::PortraitFlipped, O::Portrait + R::OneEighty);
    EXPECT_EQ(O::Portrait, O::PortraitFlipped + R::OneEighty);

    // Flip operands
    EXPECT_EQ(O::LandscapeFlipped, R::OneEighty + O::Landscape);
    EXPECT_EQ(O::Landscape, R::OneEighty + O::LandscapeFlipped);
    EXPECT_EQ(O::PortraitFlipped, R::OneEighty + O::Portrait);
    EXPECT_EQ(O::Portrait, R::OneEighty + O::PortraitFlipped);
}

TEST(AddRotationToOrientation, TwoSeventy)
{
    EXPECT_EQ(O::PortraitFlipped, O::Landscape + R::TwoSeventy);
    EXPECT_EQ(O::Portrait, O::LandscapeFlipped + R::TwoSeventy);
    EXPECT_EQ(O::Landscape, O::Portrait + R::TwoSeventy);
    EXPECT_EQ(O::LandscapeFlipped, O::PortraitFlipped + R::TwoSeventy);

    // Flip operands
    EXPECT_EQ(O::PortraitFlipped, R::TwoSeventy + O::Landscape);
    EXPECT_EQ(O::Portrait, R::TwoSeventy + O::LandscapeFlipped);
    EXPECT_EQ(O::Landscape, R::TwoSeventy + O::Portrait);
    EXPECT_EQ(O::LandscapeFlipped, R::TwoSeventy + O::PortraitFlipped);
}

TEST(SubtractRotationFromOrientation, Zero)
{
    EXPECT_EQ(O::Landscape, O::Landscape - R::Zero);
    EXPECT_EQ(O::LandscapeFlipped, O::LandscapeFlipped - R::Zero);
    EXPECT_EQ(O::Portrait, O::Portrait - R::Zero);
    EXPECT_EQ(O::PortraitFlipped, O::PortraitFlipped - R::Zero);
}

TEST(SubtractRotationFromOrientation, Ninety)
{
    EXPECT_EQ(O::PortraitFlipped, O::Landscape - R::Ninety);
    EXPECT_EQ(O::Portrait, O::LandscapeFlipped - R::Ninety);
    EXPECT_EQ(O::Landscape, O::Portrait - R::Ninety);
    EXPECT_EQ(O::LandscapeFlipped, O::PortraitFlipped - R::Ninety);
}

TEST(SubtractRotationFromOrientation, OneEighty)
{
    EXPECT_EQ(O::LandscapeFlipped, O::Landscape - R::OneEighty);
    EXPECT_EQ(O::Landscape, O::LandscapeFlipped - R::OneEighty);
    EXPECT_EQ(O::PortraitFlipped, O::Portrait - R::OneEighty);
    EXPECT_EQ(O::Portrait, O::PortraitFlipped - R::OneEighty);
}

TEST(SubtractRotationFromOrientation, TwoSeventy)
{
    EXPECT_EQ(O::Portrait, O::Landscape - R::TwoSeventy);
    EXPECT_EQ(O::PortraitFlipped, O::LandscapeFlipped - R::TwoSeventy);
    EXPECT_EQ(O::LandscapeFlipped, O::Portrait - R::TwoSeventy);
    EXPECT_EQ(O::Landscape, O::PortraitFlipped - R::TwoSeventy);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

