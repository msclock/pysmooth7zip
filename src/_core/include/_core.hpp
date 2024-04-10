#pragma once

#include "_version.hpp"

#include <bit7z/bit7z.hpp>

namespace _core {
#ifdef WIN32
constexpr auto default_lib7zip = "7zip.dll";
#else
constexpr auto default_lib7zip = "lib7zip.so";
#endif
} // namespace _core
