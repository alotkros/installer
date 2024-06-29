#include "InstallTransaction.h"
#include <iostream>
#include <windows.h>

InstallTransaction::InstallTransaction() : isSuccessful(false) {}

InstallTransaction::~InstallTransaction() {
    if (!isSuccessful) {
        cleanResources();
    }
}

void InstallTransaction::cleanResources() {
    for (auto it = m_installedResources.rbegin(); it != m_installedResources.rend(); ++it) {
        auto& installedResource = *it;

        std::expected<void, FileError> cleanResourceStatus = installedResource->clean();

        if (!cleanResourceStatus) {
            std::wcout << "Failed to clean a resource due to: {}"
                       << cleanResourceStatus.error().message << std::endl;
        }
    }
}
