#pragma once

#include "Transaction/InstalledResource.h"
#include <string>

class InstalledDirectory : public InstalledResource {
public:
    InstalledDirectory(std::wstring dirPath) : InstalledResource(), m_dirPath(dirPath) {}

    std::expected<void, FileError> clean() override;
    ~InstalledDirectory() override {}

private:
    std::wstring m_dirPath;
};
