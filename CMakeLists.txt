cmake_minimum_required(VERSION 3.21)

project(Installer LANGUAGES CXX)

set(CMAKE_GENERATOR Ninja)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

set(INSTALLER_SOURCE_FILES
    "src/main.cpp"
    "src/Installer.cpp"
    "src/FileCopier.cpp"
    "src/Parser/ArgumentsParser.cpp"
    "src/Validations/FileValidations.cpp"
    "src/Transaction/InstallTransaction.cpp"
    "src/Transaction/Resources/InstalledDirectory.cpp"
    "src/Transaction/Resources/InstalledFile.cpp"
)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(Installer ${INSTALLER_SOURCE_FILES})

target_include_directories(Installer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(
    Installer
    PRIVATE shlwapi
)
