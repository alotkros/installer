#pragma once

#include "Transaction/InstalledResource.h"
#include <expected>
#include <string>

class InstalledFile : public InstalledResource {
public:
    InstalledFile(const std::wstring filePath) : InstalledResource(), m_filePath(filePath) {}
    std::expected<void, FileError> clean() override;

    ~InstalledFile() override {}

private:
    const std::wstring m_filePath;
};