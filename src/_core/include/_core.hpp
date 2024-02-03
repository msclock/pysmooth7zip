#pragma once

#include "_version.hpp"

#include <bit7z/bit7z.hpp>

namespace _core {
#ifdef WIN32
constexpr auto default_7zip_library = "lib7zip.dll";
#else
constexpr auto default_7zip_library = "lib7zip.so";
#endif
} // namespace _core
