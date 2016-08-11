/** @file
    @brief Display struct and related types.

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

#ifndef INCLUDED_Display_h_GUID_ED98FB68_A0E9_480B_9CF0_8C6D444DEB7E
#define INCLUDED_Display_h_GUID_ED98FB68_A0E9_480B_9CF0_8C6D444DEB7E

// Internal Includes
#include <osvr/Display/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <cmath>
#include <cstdint>
#include <string>

namespace osvr {
namespace display {

struct DisplaySize {
    uint32_t width;
    uint32_t height;

    OSVR_DISPLAY_EXPORT bool operator==(const DisplaySize& other) const;
    OSVR_DISPLAY_EXPORT bool operator!=(const DisplaySize& other) const;
};

struct DisplayPosition {
    int32_t x;
    int32_t y;

    OSVR_DISPLAY_EXPORT bool operator==(const DisplayPosition& other) const;
    OSVR_DISPLAY_EXPORT bool operator!=(const DisplayPosition& other) const;
};

struct DisplayAdapter {
    std::string description;

    OSVR_DISPLAY_EXPORT bool operator==(const DisplayAdapter& other) const;
    OSVR_DISPLAY_EXPORT bool operator!=(const DisplayAdapter& other) const;
};

enum class Rotation {
    Zero,
    Ninety,
    OneEighty,
    TwoSeventy
};

enum class DesktopOrientation {
    Landscape,
    Portrait,
    LandscapeFlipped,
    PortraitFlipped
};

enum class ScanOutOrigin {
    LowerLeft,
    UpperLeft,
    LowerRight,
    UpperRight
};

/** \name Operators to apply rotations to desktop orientations and calculate
 * the rotational differences between two orientations.
 */
//@{
/**
 * Calculate the rotation needed to from lhs to rhs.
 */
OSVR_DISPLAY_EXPORT Rotation operator-(const DesktopOrientation lhs, const DesktopOrientation rhs);

/**
 * Calculate the new DesktopOrientation after a Rotation has been applied to it.
 */
OSVR_DISPLAY_EXPORT DesktopOrientation operator+(DesktopOrientation orientation, Rotation rotation);

OSVR_DISPLAY_EXPORT DesktopOrientation operator+(Rotation rotation, DesktopOrientation orientation);

/**
 * Calculate the new DesktopOrientation after a reverse Rotation has been applied to it.
 */
OSVR_DISPLAY_EXPORT DesktopOrientation operator-(DesktopOrientation orientation, Rotation rotation);
//@}

/**
 * Calculate the DesktopOrientation after a rotation has been applied to a
 * ScanOutOrigin.
 */
OSVR_DISPLAY_EXPORT DesktopOrientation operator+(ScanOutOrigin origin, Rotation rotation);
OSVR_DISPLAY_EXPORT DesktopOrientation operator+(Rotation rotation, ScanOutOrigin origin);

struct Display {
    DisplayAdapter adapter;
    std::string name;
    DisplaySize size;
    DisplayPosition position;
    Rotation rotation;
    double verticalRefreshRate;
    bool attachedToDesktop;
    uint32_t edidVendorId;
    uint32_t edidProductId;

    OSVR_DISPLAY_EXPORT bool operator==(const Display& other) const;
    OSVR_DISPLAY_EXPORT bool operator!=(const Display& other) const;
};

OSVR_DISPLAY_EXPORT std::string to_string(const Rotation rotation);
OSVR_DISPLAY_EXPORT std::string to_string(const DesktopOrientation orientation);
OSVR_DISPLAY_EXPORT std::string to_string(const ScanOutOrigin origin);

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_Display_h_GUID_ED98FB68_A0E9_480B_9CF0_8C6D444DEB7E

