/** @file
    @brief Linux-specific implementation.

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

#ifndef INCLUDED_DisplayConfiguration_Linux_h_GUID_68A7665C_095F_4ED8_BD4A_B28BAA430212
#define INCLUDED_DisplayConfiguration_Linux_h_GUID_68A7665C_095F_4ED8_BD4A_B28BAA430212

// Internal Includes
#include "DisplayConfiguration.h"

#include "Display.h"
#include "DisplayEnumerator.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace osvr {
namespace display {

bool setDesktopOrientation(const Display& display, DesktopOrientation orientation)
{
    return false;
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayConfiguration_Linux_h_GUID_68A7665C_095F_4ED8_BD4A_B28BAA430212

