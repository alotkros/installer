#include "InstalledFile.h"
#include "Errors.h"
#include <format>
#include <iostream>
#include <windows.h>

std::expected<void, FileError> InstalledFile::clean() {
    std::wcout << "Deleting file: " << m_filePath << std::endl;
    BOOL deleteFileStatus = DeleteFile(m_filePath.c_str());

    if (!deleteFileStatus) {
        std::wstring errorReason = std::format(L"Failed to delete file {} due to error code: {}",
                                               m_filePath, GetLastError());
        return std::unexpected(FileError(errorReason, FileErrorType::DeleteFileError));
    }

    return {};
}
