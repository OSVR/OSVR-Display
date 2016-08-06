/** @file
    @brief OS X-specific implementation.

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

#ifndef INCLUDED_DisplayConfiguration_MacOSX_h_GUID_ED423916_5427_4155_B5B7_71BB64A97150
#define INCLUDED_DisplayConfiguration_MacOSX_h_GUID_ED423916_5427_4155_B5B7_71BB64A97150



// Internal Includes
#include "DisplayConfiguration.h"

#include "Display.h"
#include "DisplayEnumerator.h"
#include "DisplayCommon_MacOSX.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace osvr {
namespace display {

bool setDesktopOrientation(const Display& display, DesktopOrientation orientation)
{
    // TODO
    return false;
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayConfiguration_MacOSX_h_GUID_ED423916_5427_4155_B5B7_71BB64A97150

