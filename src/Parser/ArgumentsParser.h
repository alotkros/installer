#pragma once

#include "Errors.h"
#include "InstallationArguments.h"
#include <expected>
#include <vector>

class ArgumentsParser {
public:
    static std::expected<const InstallationArguments, ParsingError>
    parseArgs(int argc, wchar_t* argv[], const size_t amountOfFiles);

private:
    constexpr static size_t SOURCE_DIR_ARGV_INDEX = 1;

private:
    static const std::vector<std::wstring>
    parseFileNamesFromArgs(wchar_t* argv[], const size_t amountOfFiles,
                           const size_t fileNamesStartArgvIndex,
                           const size_t fileNamesEndArgvIndex);
};
