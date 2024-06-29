#include "InstalledDirectory.h"
#include <iostream>
#include <windows.h>

std::expected<void, FileError> InstalledDirectory::clean() {
    std::wcout << "Deleting directory: " << m_dirPath << std::endl;
    BOOL removeDirectoryStatus = RemoveDirectory(m_dirPath.c_str());

    if (!removeDirectoryStatus) {
        std::wstring errorReason = std::format(
            L"Failed to delete directory {} due to error code: {}", m_dirPath, GetLastError());
        return std::unexpected(FileError(errorReason, FileErrorType::DeleteDirectoryError));
    }

    return {};
}
