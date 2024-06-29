#pragma once

#include <string>
#include <vector>

struct InstallationArguments {
    const std::wstring srcDir;
    const std::wstring destDir;

    const std::vector<std::wstring> fileNames;

    InstallationArguments(std::wstring srcDir, std::wstring destDir,
                          std::vector<std::wstring> fileNames)
        : srcDir(srcDir),
          destDir(destDir),
          fileNames(std::move(fileNames)) {}
};
