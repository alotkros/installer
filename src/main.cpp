#include "Installer.h"
#include "Parser/ArgumentsParser.h"
#include <iostream>
#include <string>
#include <vector>

constexpr int AMOUNT_OF_FILES = 3;

int wmain(int argc, wchar_t* argv[]) {
    std::expected<const InstallationArguments, ParsingError> installationArguments =
        ArgumentsParser::parseArgs(argc, argv, AMOUNT_OF_FILES);

    if (!installationArguments) {
        ParsingError parsingArgsError = installationArguments.error();
        std::wcout << L"Error has occurred whilst parsing the arguments for the program: "
                   << parsingArgsError.message << std::endl;
        return EXIT_FAILURE;
    }

    Installer installer;
    std::expected<void, InstallationError> installationResult =
        installer.install(installationArguments.value());

    if (!installationResult) {
        std::wcout << L"Error has occurred during the installation: "
                   << installationResult.error().message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
