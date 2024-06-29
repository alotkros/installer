#include "Installer.h"
#include "FileCopier.h"
#include "Transaction/InstallTransaction.h"
#include "Transaction/Resources/InstalledDirectory.h"
#include "Transaction/Resources/InstalledFile.h"
#include "Validations/FileValidations.h"
#include <exception>
#include <format>
#include <iostream>
#include <shlwapi.h>
#include <windows.h>

std::expected<void, InstallationError>
Installer::install(const InstallationArguments& installationArguments) {
    InstallTransaction transaction;

    if (!validateDirectoryPath(installationArguments.destDir)) {
        auto createdDirectory = createDirectory(transaction, installationArguments.destDir);
        std::wcout << "Created directory for installation at: " << installationArguments.destDir
                   << std::endl;

        if (!createdDirectory) {
            std::wcout << "Could not create the directory successfully due to: "
                       << createdDirectory.error().message << std::endl;
            return std::unexpected(
                InstallationError(createdDirectory.error().message,
                                  InstallationErrorType::FailedToCreateDestinationDirectory));
        }
    }

    FileCopier fileCopier(installationArguments.srcDir, installationArguments.destDir, transaction);

    for (auto& fileName : installationArguments.fileNames) {
        auto installedFileResult = fileCopier.copyFile(fileName);

        if (!installedFileResult) {
            return std::unexpected(InstallationError(installedFileResult.error().message,
                                                     InstallationErrorType::CopyFilesError));
        }
    }

    transaction.isSuccessful = true;

    std::wcout << "Finished the installation from: " << installationArguments.srcDir << " to "
               << installationArguments.destDir << " successfully." << std::endl;

    return {};
}

std::expected<void, FileError> Installer::createDirectory(InstallTransaction& transaction,
                                                          const std::wstring& dirPath) {
    BOOL createDirectoryStatus = CreateDirectory(dirPath.c_str(), NULL);

    if (createDirectoryStatus) {
        transaction.addResource<InstalledDirectory>(dirPath);
        return {};
    }

    std::wstring errorReason;
    switch (GetLastError()) {
        case ERROR_ALREADY_EXISTS:
            errorReason = std::format(
                L"Failed to create the directory at: {}, as the directory already exists.",
                dirPath);
            break;
        case ERROR_PATH_NOT_FOUND:
            errorReason = std::format(L"Failed to create the directory at: {}, as one or more "
                                      L"intermediate directories do not exist.",
                                      dirPath);
            break;
        default:
            errorReason = std::format(
                L"Failed to create the directory at: {}, due to the following last error code: {}",
                dirPath, GetLastError());
            break;
    }

    return std::unexpected(FileError(errorReason, FileErrorType::CreateDirectoryError));
}
