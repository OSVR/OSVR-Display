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

    OSVR_DISPLAY_EXPORT bool operator==(const DisplaySize& other) const
    {
        if (width != other.width) return false;
        if (height != other.height) return false;

        return true;
    }

    OSVR_DISPLAY_EXPORT bool operator!=(const DisplaySize& other) const
    {
        return !(*this == other);
    }
};

struct DisplayPosition {
    int32_t x;
    int32_t y;

    OSVR_DISPLAY_EXPORT bool operator==(const DisplayPosition& other) const
    {
        if (x != other.x) return false;
        if (y != other.y) return false;

        return true;
    }

    OSVR_DISPLAY_EXPORT bool operator!=(const DisplayPosition& other) const
    {
        return !(*this == other);
    }
};

struct DisplayAdapter {
    std::string description;

    OSVR_DISPLAY_EXPORT bool operator==(const DisplayAdapter& other) const
    {
        if (description != other.description) return false;

        return true;
    }

    OSVR_DISPLAY_EXPORT bool operator!=(const DisplayAdapter& other) const
    {
        return !(*this == other);
    }
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

/** \name Operators to apply rotations to desktop orientations and calculate
 * the rotational differences between two orientations.
 */
//@{
/**
 * Calculate the rotation needed to from lhs to rhs.
 */
OSVR_DISPLAY_EXPORT inline Rotation operator-(const DesktopOrientation lhs, const DesktopOrientation rhs)
{
    const auto difference = (4 + static_cast<int>(lhs) - static_cast<int>(rhs)) % 4;
    switch (difference) {
    case 0:
        return Rotation::Zero;
    case 1:
        return Rotation::Ninety;
    case 2:
        return Rotation::OneEighty;
    case 3:
        return Rotation::TwoSeventy;
    default:
        // ERROR! Shouldn't get here. Check to see if the Rotation or
        // DesktopOrientation enums have changed.
        return Rotation::Zero;
    }
}

/**
 * Calculate the new DesktopOrientation after a Rotation has been applied to it.
 */
OSVR_DISPLAY_EXPORT inline DesktopOrientation operator+(DesktopOrientation orientation, Rotation rotation)
{
    return static_cast<DesktopOrientation>((static_cast<int>(orientation) + static_cast<int>(rotation)) % 4);
}

OSVR_DISPLAY_EXPORT inline DesktopOrientation operator+(Rotation rotation, DesktopOrientation orientation)
{
    return orientation + rotation;
}

/**
 * Calculate the new DesktopOrientation after a reverse Rotation has been applied to it.
 */
OSVR_DISPLAY_EXPORT inline DesktopOrientation operator-(DesktopOrientation orientation, Rotation rotation)
{
    return static_cast<DesktopOrientation>((static_cast<int>(orientation) - static_cast<int>(rotation) + 4) % 4);
}
//@}


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

    OSVR_DISPLAY_EXPORT bool operator==(const Display& other) const
    {
        if (adapter != other.adapter) return false;
        if (name != other.name) return false;
        if (size != other.size) return false;
        if (position != other.position) return false;
        if (rotation != other.rotation) return false;
        if (verticalRefreshRate != other.verticalRefreshRate) return false;
        if (attachedToDesktop != other.attachedToDesktop) return false;
        if (edidProductId != other.edidProductId) return false;
        if (edidVendorId != other.edidVendorId) return false;

        return true;
    }

    OSVR_DISPLAY_EXPORT bool operator!=(const Display& other) const
    {
        return !(*this == other);
    }
};

OSVR_DISPLAY_EXPORT inline std::string to_string(const Rotation rotation)
{
    switch (rotation) {
    case osvr::display::Rotation::Zero:
        return "0 degrees counter-clockwise";
    case osvr::display::Rotation::Ninety:
        return "90 degrees counter-clockwise";
    case osvr::display::Rotation::OneEighty:
        return "180 degrees counter-clockwise";
    case osvr::display::Rotation::TwoSeventy:
        return "270 degrees counter-clockwise";
    default:
        return "Unknown rotation: " + std::to_string(static_cast<int>(rotation));
    }
}

OSVR_DISPLAY_EXPORT inline std::string to_string(const DesktopOrientation orientation)
{
    switch (orientation) {
    case osvr::display::DesktopOrientation::Landscape:
        return "Landscape";
    case osvr::display::DesktopOrientation::Portrait:
        return "Portrait";
    case osvr::display::DesktopOrientation::LandscapeFlipped:
        return "Landscape (flipped)";
    case osvr::display::DesktopOrientation::PortraitFlipped:
        return "Portrait (flipped)";
    default:
        return "Unknown orientation: " + std::to_string(static_cast<int>(orientation));
    }
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_Display_h_GUID_ED98FB68_A0E9_480B_9CF0_8C6D444DEB7E

