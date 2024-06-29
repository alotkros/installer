#pragma once

#include "Errors.h"
#include "Transaction/InstallTransaction.h"
#include <expected>
#include <optional>
#include <string>

class FileCopier {
public:
    FileCopier(const std::wstring& srcDir, const std::wstring& destDir,
               InstallTransaction& installTransaction);

    std::expected<void, FileError> copyFile(const std::wstring& fileName);

private:
    const std::wstring m_srcDir;
    const std::wstring m_destDir;
    InstallTransaction& m_transaction;

private:
    std::expected<std::wstring, FileError> resolveFilePath(const std::wstring& dirPath,
                                                           const std::wstring& fileName);
};