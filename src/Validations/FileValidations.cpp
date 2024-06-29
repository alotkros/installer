#include "FileValidations.h"
#include <windows.h>

std::expected<void, FileError> validateFilePath(const std::wstring& filePath) {
    DWORD fileAttributes = GetFileAttributes(filePath.c_str());

    bool isPathValid = fileAttributes != INVALID_FILE_ATTRIBUTES;
    if (!isPathValid) {
        std::wstring errorReason = std::format(
            L"The path: {} is not a valid path. Last error code: {}", filePath, GetLastError());
        return std::unexpected(FileError(errorReason, FileErrorType::InvalidPathError));
    }

    bool isFilePath = !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    if (!isFilePath) {
        std::wstring errorReason = std::format(L"The file path: {} is not a file.", filePath);
        return std::unexpected(FileError(errorReason, FileErrorType::NotADirectoryError));
    }

    return {};
}

std::expected<void, FileError> validateDirectoryPath(const std::wstring& dirPath) {
    DWORD dirAttributes = GetFileAttributes(dirPath.c_str());
    bool isPathValid = dirAttributes != INVALID_FILE_ATTRIBUTES;

    if (!isPathValid) {
        std::wstring errorReason = std::format(
            L"The path: {} is not a valid path. Last error code: {}", dirPath, GetLastError());
        return std::unexpected(FileError(errorReason, FileErrorType::InvalidPathError));
    }

    bool isDirPath = dirAttributes & FILE_ATTRIBUTE_DIRECTORY;
    if (!isDirPath) {
        std::wstring errorReason =
            std::format(L"The directory path: {} is not a directory.", dirPath);
        return std::unexpected(FileError(errorReason, FileErrorType::NotADirectoryError));
    }

    return {};
}
