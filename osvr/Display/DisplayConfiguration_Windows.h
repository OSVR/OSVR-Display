/** @file
    @brief Windows-specific implementation.

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

#ifndef INCLUDED_DisplayConfiguration_Windows_h_GUID_3489E4D8_2350_43C4_AE55_C8C9DD53404A
#define INCLUDED_DisplayConfiguration_Windows_h_GUID_3489E4D8_2350_43C4_AE55_C8C9DD53404A


// Internal Includes
#include "DisplayConfiguration.h"

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
#include <array>

namespace osvr {
namespace display {

/**
 * Find the rotation to apply to the display to achieve the desired orientation.
 */
Rotation calculateRotation(const Display& display, DesktopOrientation desired_orientation)
{
    const auto current_orientation = getDesktopOrientation(display);

    // Determine the rotation necessary to go from the current orientation to
    // the desired orientation.

    // If the current and desired orientations are same, then the current
    // rotation is perfectly fine.
    if (current_orientation == desired_orientation)
        return display.rotation;

    return current_orientation - desired_orientation;
}

bool setDesktopOrientation(const Display& display, DesktopOrientation orientation)
{
    PathInfoList path_info;
    ModeInfoList mode_info;
    std::tie(path_info, mode_info) = detail::getDisplayInformation();

    const auto path_info_iter = detail::find(path_info, mode_info, display);
    if (path_info_iter == path_info.end()) {
        std::cerr << "Failed to find specified display." << std::endl;
        return false;
    }

    const auto current_orientation = getDesktopOrientation(display);
    const auto rotation = current_orientation - orientation;

    auto path_info_array = std::array<DISPLAYCONFIG_PATH_INFO, 1> {*path_info_iter};
    path_info_array[0].targetInfo.rotation = detail::rotation_cast(rotation);
    SetDisplayConfig(path_info_array.size(), path_info_array.data(),
                     0, nullptr,
                     SDC_APPLY | SDC_USE_SUPPLIED_DISPLAY_CONFIG);
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayConfiguration_Windows_h_GUID_3489E4D8_2350_43C4_AE55_C8C9DD53404A

