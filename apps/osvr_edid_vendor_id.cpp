/** @file
    @brief Utility for encoding/decoding EDID vendor IDs

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
// - none

// Library/third-party includes
#include <osvr/Display/Display.h>

// Standard includes
#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>

void print_usage(const std::string& name)
{
    std::cout
        << name << " encodes and decodes EDID vendor IDs (equivalent to PNP IDs).\n\n"
        << "Usage:\n"
        << "  " << name << " encode <string>\n"
        << "  " << name << " decode <value>\n"
        << "  " << name << " (-h | --help)\n"
        << "\n"
        << "Options:\n"
        << "  -h | --help   Show this usage info\n"
        << std::endl;
}

void print_error(const std::string& name, const std::string& err)
{
    std::cerr << "Error: " << err << std::endl;
    print_usage(name);
    std::exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const auto cmd = std::string { argv[1] };
    if ("-h" == cmd || "--help" == cmd) {
        print_usage(argv[0]);
    } else if ("encode" == cmd) {
        if (argc < 3) {
            print_error(argv[0], "Provide the vendor ID string to encode.");
        }

        try {
            const auto vid = osvr::display::encodeEdidVendorId(argv[2]);
            std::cout << std::hex << std::showbase << std::setw(4) << vid << " = "
                << std::dec << vid << " = "
                << "\"" << argv[2] << "\""
                << std::endl;
        } catch (const std::exception& e) {
            print_error(argv[0], e.what());
        }
    } else if ("decode" == cmd) {
        if (argc < 3) {
            print_error(argv[0], "Provide the vendor ID string to decode.");
        }

        try {
            const auto vid = static_cast<uint32_t>(std::stoi(argv[2], 0, 0));
            std::cout << std::hex << std::showbase << std::setw(4) << vid << " = "
                << std::dec << vid << " = "
                << "\"" << osvr::display::decodeEdidVendorId(vid) << "\""
                << std::endl;
        } catch (const std::exception& e) {
            print_error(argv[0], e.what());
        }
    } else {
        print_error(argv[0], "Invalid command [" + cmd + "].");
    }

    return EXIT_SUCCESS;
}

