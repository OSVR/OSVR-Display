/** @file
    @brief Windows-specific implementation of getDisplays().

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

#ifndef INCLUDED_DisplayEnumerator_Windows_h_GUID_E1608541_438C_4A60_AB12_7650DA2EE279
#define INCLUDED_DisplayEnumerator_Windows_h_GUID_E1608541_438C_4A60_AB12_7650DA2EE279

// Internal Includes
#include "DisplayEnumerator.h"

#include "Display.h"
#include "DisplayCommon_Windows.h"

// Library/third-party includes
#include <Windows.h>

// Standard includes
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#include <cmath>
#include <tuple>

namespace osvr {
namespace display {

OSVR_DISPLAY_EXPORT std::vector<Display> getDisplays()
{
    std::vector<Display> displays;

    PathInfoList path_info;
    ModeInfoList mode_info;
    std::tie(path_info, mode_info) = detail::getDisplayInformation();

    for (const auto& path : path_info) {
        try {
            const auto display = detail::getDisplay(path, mode_info);
            displays.emplace_back(std::move(display));
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << ".";
            std::cout << "Ignoring this display." << std::endl;
        }
    }

    return displays;
}

DesktopOrientation getDesktopOrientation(const Display& display)
{
    // TODO test in Windows: AMD

    // Windows reports the hardware resolution and rotation. We need
    // to apply the rotation to get the desktop orientation.
    const auto rotation = display.rotation;
    const auto is_hardware_landscape = display.size.height < display.size.width;

    if (Rotation::Zero == rotation) {
        return (is_hardware_landscape ? DesktopOrientation::Landscape : DesktopOrientation::Portrait);
    } else if (Rotation::Ninety == rotation) {
        return (is_hardware_landscape ? DesktopOrientation::PortraitFlipped : DesktopOrientation::Landscape);
    } else if (Rotation::OneEighty == rotation) {
        return (is_hardware_landscape ? DesktopOrientation::LandscapeFlipped : DesktopOrientation::PortraitFlipped);
    } else if (Rotation::TwoSeventy == rotation) {
        return (is_hardware_landscape ? DesktopOrientation::Portrait : DesktopOrientation::LandscapeFlipped);
    }
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayEnumerator_Windows_h_GUID_E1608541_438C_4A60_AB12_7650DA2EE279

