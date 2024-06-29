#pragma once
#include <format>
#include <string>

template <class T>
concept EnumType = std::is_enum_v<T>;

// The concept helps to add a compile-type constraint to the templated type to only accept enums.
template <EnumType ErrorType>
struct Error {
    const std::wstring message;
    const ErrorType type;

    Error(const std::wstring message, const ErrorType type) : message(message), type(type) {}
};

enum class ParsingErrorType {
    NotEnoughArguments,
    InvalidSourceDirectory,
    SourceFileNotFound,
};

using ParsingError = Error<ParsingErrorType>;

enum class FileErrorType {
    InvalidPathError,
    NotADirectoryError,
    NotAFileError,
    ResolveFilePathError,
    CopyFileError,
    CreateDirectoryError,
    DeleteFileError,
    DeleteDirectoryError,
};

using FileError = Error<FileErrorType>;

enum class InstallationErrorType {
    FailedToCreateDestinationDirectory,
    CopyFilesError,
};

using InstallationError = Error<InstallationErrorType>;
