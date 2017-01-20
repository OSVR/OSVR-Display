/** @file
    @brief A command-line utility to query displays and change their settings.

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
#include <osvr/Display/DisplayEnumerator.h>

// Library/third-party includes
#include <docopt.h>

// Standard includes
#include <cstdlib>
#include <iostream>
#include <iomanip>

static const auto USAGE =
R"(osvr_display.

    Usage:
      osvr_display [list]
      osvr_display set <display> resolution <x> <y>
      osvr_display set <display> orientation <orientation>

    Options:
      -h --help     Show this screen.
      --version     Show version.
)";

int list_displays()
{
    auto displays = osvr::display::getDisplays();

    for (const auto& display : displays) {
        using std::cout;
        using std::endl;
        using std::setfill;
        using std::setw;
        using std::hex;
        using std::dec;

#if 0
Screen 0: minimum 1 x 1, current 1440 x 900, maximum 16384 x 16384
Virtual1 connected primary 1440x900+0+0 (normal left inverted right x axis y axis) 0mm x 0mm
   1440x900      60.00*+  59.89  
   2560x1600     59.99  
   1920x1440     60.00  
   1856x1392     60.00  
   1792x1344     60.00  
   1920x1200     59.88  
   1600x1200     60.00  
   1680x1050     59.95  
   1400x1050     59.98  
   1280x1024     60.02  
   1280x960      60.00  
   1360x768      60.02  
   1280x800      59.81  
   1152x864      75.00  
   1280x768      59.87  
   1024x768      60.00  
   800x600       60.32  
   640x480       59.94  
Virtual2 disconnected (normal left inverted right x axis y axis)
Virtual3 disconnected (normal left inverted right x axis y axis)
Virtual4 disconnected (normal left inverted right x axis y axis)
Virtual5 disconnected (normal left inverted right x axis y axis)
Virtual6 disconnected (normal left inverted right x axis y axis)
Virtual7 disconnected (normal left inverted right x axis y axis)
Virtual8 disconnected (normal left inverted right x axis y axis)
#endif

        cout << "Display: " << display.name << endl;
        cout << "  Adapter: " << display.adapter.description << endl;
        cout << "  Monitor name: " << display.name << endl;
        cout << "  Resolution: " << display.size.width << "x" << display.size.height << endl;
        cout << "  Position: (" << display.position.x << ", " << display.position.y << ")" << endl;
        cout << "  Rotation: " << to_string(display.rotation) << endl;
        cout << "  Orientation: " << to_string(osvr::display::getDesktopOrientation(display)) << endl;
        cout << "  Refresh rate: " << display.verticalRefreshRate << endl;
        cout << "  " << (display.attachedToDesktop ? "Extended mode" : "Direct mode") << endl;
        cout << "  EDID vendor ID: 0x" << setfill('0') << setw(4) << hex << display.edidVendorId << dec << " (" << osvr::display::decodeEdidVendorId(display.edidVendorId) << ")" << endl;
        cout << "  EDID product ID: 0x" << setfill('0') << setw(4) << hex << display.edidProductId << dec << endl;
        cout << "" << endl;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    auto args = docopt::docopt(USAGE, { argv + 1, argv + argc }, true, "osvr_display 0.1");

    //for (const auto& arg : args) {
    //    std::cout << arg.first << " = " << arg.second << std::endl;
    //}
    //std::cout << std::endl;

    if (args["list"]) {
        return list_displays();
    } else if (args["get"]) {
        return EXIT_SUCCESS;
    } else if (args["set"]) {
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

