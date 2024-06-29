#include "ArgumentsParser.h"
#include "Parser/ArgumentsParser.h"

std::expected<const InstallationArguments, ParsingError>
ArgumentsParser::parseArgs(int argc, wchar_t* argv[], size_t amountOfFiles) {
    const size_t fileNamesStartArgvIndex = ArgumentsParser::SOURCE_DIR_ARGV_INDEX + 1;
    const size_t fileNamesEndArgvIndex = fileNamesStartArgvIndex + (amountOfFiles - 1);

    const size_t destDirArgvIndex = fileNamesEndArgvIndex + 1;
    const size_t expectedAmountOfArguments = destDirArgvIndex + 1;

    if (argc < expectedAmountOfArguments) {
        return std::unexpected(ParsingError(L"Not enough arguments were passed to the program.",
                                            ParsingErrorType::NotEnoughArguments));
    }

    std::wstring srcDir = argv[ArgumentsParser::SOURCE_DIR_ARGV_INDEX];

    std::vector<std::wstring> fileNames =
        parseFileNamesFromArgs(argv, amountOfFiles, fileNamesStartArgvIndex, fileNamesEndArgvIndex);

    std::wstring destDir = argv[destDirArgvIndex];

    return InstallationArguments(srcDir, destDir, fileNames);
}

const std::vector<std::wstring>
ArgumentsParser::parseFileNamesFromArgs(wchar_t* argv[], const size_t amountOfFiles,
                                        const size_t fileNamesStartArgvIndex,
                                        const size_t fileNamesEndArgvIndex) {
    std::vector<std::wstring> fileNames;
    fileNames.reserve(amountOfFiles);

    std::wstring fileName;
    for (size_t idx = fileNamesStartArgvIndex; idx <= fileNamesEndArgvIndex; idx++) {
        fileNames.push_back(argv[idx]);
    }

    return fileNames;
}
