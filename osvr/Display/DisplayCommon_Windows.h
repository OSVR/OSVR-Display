/** @file
    @brief Common Windows-specific functions.

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

#ifndef INCLUDED_DisplayCommon_Windows_h_GUID_C5BDCECD_5E8E_42C9_BB0F_E6523A96C4D5
#define INCLUDED_DisplayCommon_Windows_h_GUID_C5BDCECD_5E8E_42C9_BB0F_E6523A96C4D5


// Internal Includes
#include <osvr/Display/DisplayEnumerator.h>

#include <osvr/Display/Display.h>
#include <osvr/Display/Export.h>

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

namespace osvr {
namespace display {

using PathInfoList = std::vector<DISPLAYCONFIG_PATH_INFO>;
using ModeInfoList = std::vector<DISPLAYCONFIG_MODE_INFO>;

namespace detail {

// Forward declarations
OSVR_DISPLAY_EXPORT std::pair<UINT32, UINT32> getBufferSizes(const UINT32 query_flags);
OSVR_DISPLAY_EXPORT std::pair<PathInfoList, ModeInfoList> getDisplayInformation();
OSVR_DISPLAY_EXPORT Display getDisplay(const DISPLAYCONFIG_PATH_INFO& path_info, const ModeInfoList& mode_info);
OSVR_DISPLAY_EXPORT DisplayAdapter getDisplayAdapter(const DISPLAYCONFIG_PATH_INFO& path_info, const ModeInfoList& mode_info);
OSVR_DISPLAY_EXPORT std::string getAdapterName(const DISPLAYCONFIG_PATH_INFO& path_info);
OSVR_DISPLAY_EXPORT std::string to_string(const std::wstring& s);
OSVR_DISPLAY_EXPORT std::string getMonitorName(const DISPLAYCONFIG_PATH_INFO& path_info);
OSVR_DISPLAY_EXPORT DisplaySize getCurrentResolution(const DISPLAYCONFIG_PATH_INFO& path_info, const std::vector<DISPLAYCONFIG_MODE_INFO>& mode_info);
OSVR_DISPLAY_EXPORT DisplayPosition getPosition(const DISPLAYCONFIG_PATH_INFO& path_info, const std::vector<DISPLAYCONFIG_MODE_INFO>& mode_info);
OSVR_DISPLAY_EXPORT Rotation getRotation(const DISPLAYCONFIG_PATH_INFO& path_info);
OSVR_DISPLAY_EXPORT double getRefreshRate(const DISPLAYCONFIG_PATH_INFO& path_info);
OSVR_DISPLAY_EXPORT std::pair<uint32_t, uint32_t> getEDIDInfo(const DISPLAYCONFIG_PATH_INFO& path_info);
OSVR_DISPLAY_EXPORT void checkResult(const std::string& function_name, LONG result);
OSVR_DISPLAY_EXPORT PathInfoList::iterator find(PathInfoList& path_info, const ModeInfoList& mode_info, const Display& display);

inline std::pair<UINT32, UINT32> getBufferSizes(const UINT32 query_flags)
{
    // Get the sizes of the path and mode buffers
    UINT32 num_path = 0;
    UINT32 num_mode_info = 0;
    const auto get_buffer_sizes_ret = GetDisplayConfigBufferSizes(query_flags, &num_path, &num_mode_info);
    if (get_buffer_sizes_ret != ERROR_SUCCESS) {
        switch (get_buffer_sizes_ret) {
        case ERROR_INVALID_PARAMETER:
            {
                const std::string msg = "An internal error occurred. GetDisplayConfigBufferSizes() returned ERROR_INVALID_PARAMETER. Please file a bug report at <https://github.com/osvr/SteamVR-OSVR>.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_NOT_SUPPORTED:
            {
                const std::string msg = "DisplayEnumerator requires Windows 7 or above and a graphics driver that was written according to the Windows Display Driver Model (WDDM).. Please file a bug report at <https://github.com/osvr/SteamVR-OSVR>.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_ACCESS_DENIED:
            {
                const std::string msg = "Access denied to the console session. SteamVR-OSVR won't run on a remote session.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_GEN_FAILURE:
            {
                const std::string msg = "An unspecified error occurred while calling GetDisplayConfigBufferSizes(). Please file a bug report at <https://github.com/osvr/SteamVR-OSVR>.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        }
    }

    return std::make_pair(std::move(num_path), std::move(num_mode_info));
}


inline std::pair<PathInfoList, ModeInfoList> getDisplayInformation()
{
    const UINT32 query_flags = QDC_ONLY_ACTIVE_PATHS;
    auto buffer_sizes = getBufferSizes(query_flags);

    auto num_path = buffer_sizes.first;
    auto num_mode_info = buffer_sizes.second;

    std::vector<DISPLAYCONFIG_PATH_INFO> path_info(num_path);
    std::vector<DISPLAYCONFIG_MODE_INFO> mode_info(num_mode_info);

    const int max_retries = 3;
    for (int retry = 0; retry < max_retries; ++retry) {
        const auto query_display_config_ret = QueryDisplayConfig(query_flags, &num_path, path_info.data(), &num_mode_info, mode_info.data(), nullptr);
        switch (query_display_config_ret) {
        case ERROR_INVALID_PARAMETER:
            {
                const std::string msg = "The combination of parameters and flags that are specified is invalid.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_NOT_SUPPORTED:
            {
                const std::string msg = "The system is not running a graphics driver that was written according to the Windows Display Driver Model (WDDM). The function is only supported on a system with a WDDM driver running.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_ACCESS_DENIED:
            {
                const std::string msg = "The caller does not have access to the console session. This error occurs if the calling process does not have access to the current desktop or is running on a remote session.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_GEN_FAILURE:
            {
                const std::string msg = "An unspecified error occurred.";
                std::cerr << msg << std::endl;
                throw std::runtime_error(msg);
            }
        case ERROR_INSUFFICIENT_BUFFER:
            {
                // Retry...
                buffer_sizes = getBufferSizes(query_flags);
                continue;
            }
        }

        break;
    }

    return {std::move(path_info), std::move(mode_info)};
}

inline Display getDisplay(const DISPLAYCONFIG_PATH_INFO& path_info, const ModeInfoList& mode_info)
{
    Display display;
    display.adapter = getDisplayAdapter(path_info, mode_info);
    display.name = getMonitorName(path_info);
    display.size = getCurrentResolution(path_info, mode_info);
    display.position = getPosition(path_info, mode_info);
    display.rotation = getRotation(path_info);
    display.verticalRefreshRate = getRefreshRate(path_info);
    display.attachedToDesktop = true; // TODO
    const auto edid_info = getEDIDInfo(path_info);
    display.edidVendorId = edid_info.first;
    display.edidProductId = edid_info.second;

    return display;
}

inline std::pair<uint32_t, uint32_t> getEDIDInfo(const DISPLAYCONFIG_PATH_INFO& path_info)
{
    DISPLAYCONFIG_TARGET_DEVICE_NAME target_name = {};
    target_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    target_name.header.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME);
    target_name.header.adapterId = path_info.targetInfo.adapterId;
    target_name.header.id = path_info.targetInfo.id;
    const auto ret = DisplayConfigGetDeviceInfo(&target_name.header);
    checkResult("getEDIDInfo()", ret);

    if (target_name.flags.edidIdsValid) {
        return {target_name.edidManufactureId, target_name.edidProductCodeId};
    } else {
        return {0x00, 0x00};
    }
}

inline double getRefreshRate(const DISPLAYCONFIG_PATH_INFO& path_info)
{
    const auto rational = path_info.targetInfo.refreshRate;
    const auto numerator = static_cast<double>(rational.Numerator);
    const auto denominator = static_cast<double>(rational.Denominator);
    const auto refresh_rate = numerator / denominator;
    return refresh_rate;
}

inline Rotation getRotation(const DISPLAYCONFIG_PATH_INFO& path_info)
{
    switch (path_info.targetInfo.rotation) {
    case DISPLAYCONFIG_ROTATION_IDENTITY:
        return Rotation::Zero;
    case DISPLAYCONFIG_ROTATION_ROTATE90:
        return Rotation::Ninety;
    case DISPLAYCONFIG_ROTATION_ROTATE180:
        return Rotation::OneEighty;
    case DISPLAYCONFIG_ROTATION_ROTATE270:
        return Rotation::TwoSeventy;
    default:
        return Rotation::Zero;
    }
}

inline DisplaySize getCurrentResolution(const DISPLAYCONFIG_PATH_INFO& path_info, const std::vector<DISPLAYCONFIG_MODE_INFO>& mode_info)
{
    const auto source_info = path_info.sourceInfo;
    if (DISPLAYCONFIG_PATH_MODE_IDX_INVALID != source_info.modeInfoIdx) {
        const auto mode = mode_info.at(source_info.modeInfoIdx);
        const auto source_mode = mode.sourceMode;
        return {source_mode.width, source_mode.height};
    }

    return {0, 0};
}

inline DisplayPosition getPosition(const DISPLAYCONFIG_PATH_INFO& path_info, const std::vector<DISPLAYCONFIG_MODE_INFO>& mode_info)
{
    const auto source_info = path_info.sourceInfo;
    if (DISPLAYCONFIG_PATH_MODE_IDX_INVALID != source_info.modeInfoIdx) {
        const auto mode = mode_info.at(source_info.modeInfoIdx);
        const auto source_mode = mode.sourceMode;
        return {source_mode.position.x, source_mode.position.y};
    }

    return {0, 0};
}

inline std::string getMonitorName(const DISPLAYCONFIG_PATH_INFO& path_info)
{
    DISPLAYCONFIG_TARGET_DEVICE_NAME target_name = {};
    target_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    target_name.header.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME);
    target_name.header.adapterId = path_info.targetInfo.adapterId;
    target_name.header.id = path_info.targetInfo.id;
    const auto ret = DisplayConfigGetDeviceInfo(&target_name.header);
    checkResult("getMonitorName()", ret);

    if (target_name.flags.friendlyNameFromEdid) {
        return to_string(target_name.monitorFriendlyDeviceName);
    } else {
        return "";
    }
}

inline void checkResult(const std::string& function_name, LONG result)
{
    switch (result) {
    case ERROR_SUCCESS:
        // do nothing
        break;
    case ERROR_INVALID_PARAMETER:
        throw std::runtime_error(function_name + ": The combination of parameters and flags specified are invalid.");
    case ERROR_NOT_SUPPORTED:
        throw std::runtime_error(function_name + ": The system is not running a graphics driver that was written according to the Windows Display Driver Model (WDDM). The function is only supported on a system with a WDDM driver running.");
    case ERROR_ACCESS_DENIED:
        throw std::runtime_error(function_name + ": The caller does not have access to the console session. This error occurs if the calling process does not have access to the current desktop or is running on a remote session.");
    case ERROR_INSUFFICIENT_BUFFER:
        throw std::runtime_error(function_name + ": The size of the packet that the caller passes is not big enough for the information that the caller requests.");
    case ERROR_GEN_FAILURE:
        throw std::runtime_error(function_name + ": An unspecified error occurred.");
    default:
        // do nothing
        break;
    }
}

inline DisplayAdapter getDisplayAdapter(const DISPLAYCONFIG_PATH_INFO& path_info, const ModeInfoList& mode_info)
{
    DisplayAdapter adapter;
    adapter.description = getAdapterName(path_info);

    return adapter;
}

inline std::string getAdapterName(const DISPLAYCONFIG_PATH_INFO& path_info)
{
    auto source_info = path_info.sourceInfo;
    auto adapter_id = source_info.adapterId;

    DISPLAYCONFIG_ADAPTER_NAME adapter_name = {};
    adapter_name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    adapter_name.header.adapterId = adapter_id;
    adapter_name.header.size = sizeof(DISPLAYCONFIG_ADAPTER_NAME);
    const auto ret = DisplayConfigGetDeviceInfo(&adapter_name.header);
    checkResult("getAdapterName()", ret);

    return to_string(adapter_name.adapterDevicePath);
}

inline std::string to_string(const std::wstring& s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(s);
}

/**
 * Searches the provided PathInfoList for the specified Display. Upon finding
 * it, returns an iterator pointing to that display in the list. If it fails, it
 * returns the past-the-end iterator (@c end()).
 */
inline PathInfoList::iterator find(PathInfoList& path_info, const ModeInfoList& mode_info, const Display& display)
{
    for (auto iter = begin(path_info); iter != end(path_info); ++iter) {
        const auto test_display = detail::getDisplay(*iter, mode_info);
        if (display == test_display) {
            return iter;
        }
    }

    return end(path_info);
}

inline DISPLAYCONFIG_ROTATION rotation_cast(const Rotation& r)
{
    switch (r) {
    case Rotation::Zero:
        return DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_IDENTITY;
    case Rotation::Ninety:
        return DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE90;
    case Rotation::OneEighty:
        return DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE180;
    case Rotation::TwoSeventy:
        return DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE270;
    }
}

inline Rotation rotation_cast(const DISPLAYCONFIG_ROTATION& r)
{
    switch (r) {
    case DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_IDENTITY:
        return Rotation::Zero;
    case DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE90:
        return Rotation::Ninety;
    case DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE180:
        return Rotation::OneEighty;
    case DISPLAYCONFIG_ROTATION::DISPLAYCONFIG_ROTATION_ROTATE270:
        return Rotation::TwoSeventy;
    }
}



} // end namespace detail

} // end namespace display
} // end namespace osvr

#endif // INCLUDED_DisplayCommon_Windows_h_GUID_C5BDCECD_5E8E_42C9_BB0F_E6523A96C4D5

