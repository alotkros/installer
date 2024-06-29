#pragma once

#include "Errors.h"
#include <expected>

class InstalledResource {
public:
    InstalledResource() = default;

    InstalledResource(const InstalledResource&) = delete;
    InstalledResource& operator=(const InstalledResource&) = delete;

    virtual std::expected<void, FileError> clean() = 0;
    virtual ~InstalledResource() = default;
};
