#pragma once

#include "InstalledResource.h"
#include <memory>
#include <vector>

class InstallTransaction {
public:
    InstallTransaction();
    ~InstallTransaction();

private:
    std::vector<std::unique_ptr<InstalledResource>> m_installedResources;

    void cleanResources();

public:
    bool isSuccessful;

public:
    template <class T, class... Targs>
    void addResource(Targs... args) {
        std::unique_ptr<T> resource = std::make_unique<T>(args...);
        m_installedResources.push_back(std::move(resource));
    }
};
