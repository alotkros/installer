#pragma once

#include "Errors.h"
#include "Parser/InstallationArguments.h"
#include "Transaction/InstallTransaction.h"
#include "Transaction/Resources/InstalledDirectory.h"
#include "Transaction/Resources/InstalledFile.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>

class Installer {
public:
    std::expected<void, InstallationError>
    install(const InstallationArguments& installationArguments);

private:
    std::expected<void, FileError> createDirectory(InstallTransaction& transaction,
                                                   const std::wstring& dirPath);
};
