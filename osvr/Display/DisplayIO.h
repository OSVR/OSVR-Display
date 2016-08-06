/** @file
    @brief I/O functions for printing enum values

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

#ifndef INCLUDED_DisplayIO_h_GUID_3C0105D1_4C9C_47F8_82B9_88A7C6170EAD
#define INCLUDED_DisplayIO_h_GUID_3C0105D1_4C9C_47F8_82B9_88A7C6170EAD

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <iostream>

namespace osvr {
namespace display {

inline std::ostream& operator<<(std::ostream& ostr, const Rotation rotation)
{
    ostr << to_string(rotation);
    return ostr;
}

inline std::ostream& operator<<(std::ostream& ostr, const DesktopOrientation orientation)
{
    ostr << to_string(orientation);
    return ostr;
}

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayIO_h_GUID_3C0105D1_4C9C_47F8_82B9_88A7C6170EAD
