#pragma once
#include <string>
#include <filesystem>
#include <stddef.h>

const unsigned int frameRateLimit = 15;

const unsigned int sideLength = 10;

const unsigned int colSize = 200;

const unsigned int rowSize = 100;

const unsigned int windowWidth = sideLength * (colSize + 2);

const unsigned int windowHeight = sideLength * (rowSize + 2);

const std::string entryFolderName = "cs6010_FinalProject";

std::string
getWorkingDirectory()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string workingDirectory{currentPath.u8string()};
    return workingDirectory;
}

// e.g. /Users/XXX/cs6010_FinalProject/build
const std::string workingDirectory = getWorkingDirectory();

std::string getFilePrefixPath()
{
    std::size_t startIndex = workingDirectory.find(entryFolderName);
    // e.g. /Users/XXX/cs6010_FinalProject/
    std::string prefix = workingDirectory.substr(0, startIndex + entryFolderName.length() + 1);
    return prefix;
}

const std::string filePrefixPath = getFilePrefixPath();

std::string getClickSoundPath()
{
    // the sound is a free sound sample called "water click" from: https://freesound.org/people/Mafon2/sounds/371274/
    const std::string relativeClickSoundPath = "src/utils/ClickSound.wav";
    // e.g. /Users/XXX/cs6010_FinalProject/src/utils/ClickSound.wav
    return filePrefixPath + relativeClickSoundPath;
}

const std::string clickSoundPath = getClickSoundPath();