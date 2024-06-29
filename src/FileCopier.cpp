#include "FileCopier.h"
#include "Transaction/Resources/InstalledFile.h"
#include "Validations/FileValidations.h"
#include <iostream>
#include <shlwapi.h>
#include <windows.h>

FileCopier::FileCopier(const std::wstring& srcDir, const std::wstring& destDir,
                       InstallTransaction& installTransaction)
    : m_srcDir(srcDir),
      m_destDir(destDir),
      m_transaction(installTransaction) {}

std::expected<void, FileError> FileCopier::copyFile(const std::wstring& fileName) {
    std::expected<std::wstring, FileError> srcFilePath = resolveFilePath(m_srcDir, fileName);
    if (!srcFilePath) {
        return std::unexpected(srcFilePath.error());
    }

    auto srcFilePathValidationResult = validateFilePath(srcFilePath.value());
    if (!srcFilePathValidationResult) {
        return std::unexpected(srcFilePathValidationResult.error());
    }

    std::expected<std::wstring, FileError> destFilePath = resolveFilePath(m_destDir, fileName);
    if (!destFilePath) {
        return std::unexpected(destFilePath.error());
    }

    BOOL copyFileStatus = CopyFile(srcFilePath->c_str(), destFilePath->c_str(), true);

    std::wcout << "Copying file " << srcFilePath.value() << L" to " << destFilePath.value()
               << std::endl;

    if (copyFileStatus == 0) {
        std::wstring errorReason =
            std::format(L"Error {} has occurred while copying {} to {}", GetLastError(),
                        srcFilePath.value(), destFilePath.value());
        return std::unexpected(FileError(errorReason, FileErrorType::CopyFileError));
    }

    m_transaction.addResource<InstalledFile>(destFilePath.value());

    return {};
}

std::expected<std::wstring, FileError> FileCopier::resolveFilePath(const std::wstring& dirPath,
                                                                   const std::wstring& fileName) {
    std::wstring resolvedFilePath;
    resolvedFilePath.resize(MAX_PATH);

    if (PathCombine(resolvedFilePath.data(), dirPath.c_str(), fileName.c_str()) == NULL) {
        std::wstring errorReason =
            std::format(L"Could not resolve path for file {} in dir {}", dirPath, fileName);
        return std::unexpected(FileError(errorReason, FileErrorType::ResolveFilePathError));
    }

    return resolvedFilePath;
}
