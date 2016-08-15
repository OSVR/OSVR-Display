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

// Internal Includes
#include <osvr/Display/Display.h>

// Library/third-party includes
// - none

// Standard includes
#include <cmath>
#include <cstdint>
#include <string>

namespace osvr {
namespace display {

bool DisplaySize::operator==(const DisplaySize& other) const
{
    if (width != other.width) return false;
    if (height != other.height) return false;

    return true;
}

bool DisplaySize::operator!=(const DisplaySize& other) const
{
    return !(*this == other);
}

bool DisplayPosition::operator==(const DisplayPosition& other) const
{
    if (x != other.x) return false;
    if (y != other.y) return false;

    return true;
}

bool DisplayPosition::operator!=(const DisplayPosition& other) const
{
    return !(*this == other);
}

bool DisplayAdapter::operator==(const DisplayAdapter& other) const
{
    if (description != other.description) return false;

    return true;
}

bool DisplayAdapter::operator!=(const DisplayAdapter& other) const
{
    return !(*this == other);
}

Rotation operator-(const DesktopOrientation lhs, const DesktopOrientation rhs)
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

DesktopOrientation operator+(DesktopOrientation orientation, Rotation rotation)
{
    return static_cast<DesktopOrientation>((static_cast<int>(orientation) + static_cast<int>(rotation)) % 4);
}

DesktopOrientation operator+(Rotation rotation, DesktopOrientation orientation)
{
    return orientation + rotation;
}

DesktopOrientation operator-(DesktopOrientation orientation, Rotation rotation)
{
    return static_cast<DesktopOrientation>((static_cast<int>(orientation) - static_cast<int>(rotation) + 4) % 4);
}

DesktopOrientation operator+(ScanOutOrigin origin, Rotation rotation)
{
    int shift = 0;
    if (ScanOutOrigin::UpperLeft == origin) {
        shift = 0;
    } else if (ScanOutOrigin::LowerLeft == origin) {
        shift = 1;
    } else if (ScanOutOrigin::LowerRight == origin) {
        shift = 2;
    } else if (ScanOutOrigin::UpperRight == origin) {
        shift = 3;
    }

    if (Rotation::Zero == rotation) {
        shift += 0;
    } else if (Rotation::Ninety == rotation) {
        shift += 1;
    } else if (Rotation::OneEighty == rotation) {
        shift += 2;
    } else if (Rotation::TwoSeventy == rotation) {
        shift += 3;
    }

    const auto orientation = static_cast<DesktopOrientation>((static_cast<int>(DesktopOrientation::Landscape) + shift) % 4);

    return orientation;
}

DesktopOrientation operator+(Rotation rotation, ScanOutOrigin origin)
{
    return origin + rotation;
}

DesktopOrientation operator-(ScanOutOrigin origin, Rotation rotation)
{
    // FIXME
    int shift = 0;
    if (ScanOutOrigin::UpperLeft == origin) {
        shift = 0;
    } else if (ScanOutOrigin::LowerLeft == origin) {
        shift = 1;
    } else if (ScanOutOrigin::LowerRight == origin) {
        shift = 2;
    } else if (ScanOutOrigin::UpperRight == origin) {
        shift = 3;
    }

    if (Rotation::Zero == rotation) {
        shift += 0;
    } else if (Rotation::Ninety == rotation) {
        shift += 1;
    } else if (Rotation::OneEighty == rotation) {
        shift += 2;
    } else if (Rotation::TwoSeventy == rotation) {
        shift += 3;
    }

    const auto orientation = static_cast<DesktopOrientation>((static_cast<int>(DesktopOrientation::Landscape) + shift) % 4);

    return orientation;
}

Rotation operator-(const Rotation rotation)
{
    return static_cast<Rotation>((4 - static_cast<int>(rotation)) % 4);
}

bool Display::operator==(const Display& other) const
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

bool Display::operator!=(const Display& other) const
{
    return !(*this == other);
}

OSVR_DISPLAY_EXPORT std::string to_string(const Rotation rotation)
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

OSVR_DISPLAY_EXPORT std::string to_string(const DesktopOrientation orientation)
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

OSVR_DISPLAY_EXPORT std::string to_string(const ScanOutOrigin origin)
{
    switch (origin) {
    case ScanOutOrigin::UpperLeft:
        return "Upper-left";
    case ScanOutOrigin::UpperRight:
        return "Upper-right";
    case ScanOutOrigin::LowerRight:
        return "Lower-right";
    case ScanOutOrigin::LowerLeft:
        return "Lower-left";
    default:
        return "Unknown scan-out origin: " + std::to_string(static_cast<int>(origin));
    }
}

} // end namespace display
} // end namespace osvr

