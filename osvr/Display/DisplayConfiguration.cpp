/** @file
    @brief Implementation

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
#include "DisplayConfiguration.h"

#include "Display.h"

// Library/third-party includes
#include <osvr/Util/PlatformConfig.h>

// Standard includes
// - none

#if defined(OSVR_WINDOWS)
#include "DisplayConfiguration_Windows.h"
#elif defined(OSVR_LINUX)
#include "DisplayConfiguration_Linux.h"
#elif defined(OSVR_MACOSX)
#include "DisplayConfiguration_MacOSX.h"
#else
#error "DisplayConfiguration functions not yet implemented for this platform!"
namespace osvr {
namespace display {

bool setDesktopOrientation(const Display&, DesktopOrientation)
{
    return false;
}

} // namespace display
} // namespace osvr
#endif

