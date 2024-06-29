#pragma once

#include "Errors.h"
#include <expected>

std::expected<void, FileError> validateDirectoryPath(const std::wstring& dirPath);

std::expected<void, FileError> validateFilePath(const std::wstring& filePath);
