/** @file
    @brief OS X-specific implementation of getDisplays().

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

#ifndef INCLUDED_DisplayEnumerator_MacOSX_h_GUID_C1F03499_42F5_4CD5_AECF_F9CAFD07E99F
#define INCLUDED_DisplayEnumerator_MacOSX_h_GUID_C1F03499_42F5_4CD5_AECF_F9CAFD07E99F

// Internal Includes
#include "DisplayEnumerator.h"

#include "Display.h"
#include "DisplayCommon_MacOSX.h"

// Library/third-party includes
#include <CoreGraphics/CoreGraphics.h>
#include <IOKit/graphics/IOGraphicsLib.h>

// Standard includes
#include <vector>
#include <iostream>

namespace osvr {
namespace display {

std::vector<Display> getDisplays()
{
    std::vector<Display> displays;

    auto max_displays = detail::getNumDisplays();

    std::vector<CGDirectDisplayID> display_ids(max_displays);
    uint32_t num_displays = 0;
    auto ret = CGGetOnlineDisplayList(max_displays, display_ids.data(), &num_displays);
    if (kCGErrorSuccess != ret) {
        std::cerr << "Error getting list of online display IDs: " << ret << std::endl;
    }

    for (const auto& display_id : display_ids) {
        try {
            const auto display = detail::getDisplay(display_id);
            displays.emplace_back(std::move(display));
        } catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << ".";
            std::cerr << "Ignoring this display." << std::endl;
        }
    }

    return displays;
}

DesktopOrientation getDesktopOrientation(const Display& display)
{
    // OS X reports the resolution values in terms of orientation
    // (e.g., 1080x1920 in portrait orientation, but 1920x1080 in landscape
    // orientation).
    const auto rotation = display.rotation;
    const auto is_landscape = display.size.height < display.size.width;

    if (osvr::display::Rotation::Zero == rotation) {
        return (is_landscape ? DesktopOrientation::Landscape : DesktopOrientation::Portrait);
    } else if (osvr::display::Rotation::Ninety == rotation) {
        return (is_landscape ? DesktopOrientation::Landscape : DesktopOrientation::PortraitFlipped);
    } else if (osvr::display::Rotation::OneEighty == rotation) {
        return (is_landscape ? DesktopOrientation::LandscapeFlipped : DesktopOrientation::PortraitFlipped);
    } else if (osvr::display::Rotation::TwoSeventy == rotation) {
        return (is_landscape ? DesktopOrientation::LandscapeFlipped : DesktopOrientation::Portrait);
    } else {
        std::cerr << "Invalid rotation value: " << static_cast<int>(rotation) << ".";
        return DesktopOrientation::Landscape;
    }
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayEnumerator_MacOSX_h_GUID_C1F03499_42F5_4CD5_AECF_F9CAFD07E99F

