#include "ubuntu_image_info.cpp"
#include <iostream>

void printSupportedReleases(UbuntuImageInfoImpl &imageInfo) {
    std::vector<std::string> releases = imageInfo.getSupportedReleases();
    std::cout << "Currently supported releases:" << std::endl;
    for (const auto &release: releases) {
        std::cout << release << std::endl;
    }
}

void printCurrentLTSVersion(UbuntuImageInfoImpl &imageInfo) {
    std::string ltsVersion = imageInfo.getCurrentLTSVersion();
    if (!ltsVersion.empty()) {
        std::cout << "Current LTS version: " << ltsVersion << std::endl;
    } else {
        std::cout << "Unable to find the current LTS version." << std::endl;
    }
}

void printSHA256(UbuntuImageInfoImpl &imageInfo, const std::string &release) {
    std::string sha256 = imageInfo.getSHA256(release);
    if (!sha256.empty()) {
        std::cout << "SHA256 for release " << release << ": " << sha256 << std::endl;
    } else {
        std::cout << "Couldn't find the specified version: " << release << std::endl;
        std::cout << "Please check the version number and try again." << std::endl;
        std::cout << "Example of a correct input: 22.04" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    try {

        if (argc == 1) {
            // Interactive mode
            std::cout << "Loading Ubuntu Cloud Image JSON.." << std::endl;
            UbuntuImageInfoImpl imageInfo;
            std::cout << "Ubuntu Cloud Image Data Loaded!" << std::endl;

            while (true) {
                std::cout << "Select an option:" << std::endl;
                std::cout << "1. Get currently supported releases" << std::endl;
                std::cout << "2. Get current LTS version" << std::endl;
                std::cout << "3. Get SHA256 for a release" << std::endl;
                std::cout << "4. Exit" << std::endl;
                std::cout << "Enter your choice (1-4): ";

                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        printSupportedReleases(imageInfo);
                        break;
                    case 2:
                        printCurrentLTSVersion(imageInfo);
                        break;
                    case 3: {
                        std::string release;
                        std::cout << "Enter the release (or 'latest'): ";
                        std::cin >> release;
                        printSHA256(imageInfo, release);
                        break;
                    }
                    case 4:
                        std::cout << "Exiting..." << std::endl;
                        return 0;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                }

                std::cout << std::endl;
            }
        } else if (argc == 2) {
            std::string arg = argv[1];

            if (arg == "--supported-releases") {
                UbuntuImageInfoImpl imageInfo;
                printSupportedReleases(imageInfo);
            } else if (arg == "--current-lts") {
                UbuntuImageInfoImpl imageInfo;
                printCurrentLTSVersion(imageInfo);
            } else {
                std::cerr << "Invalid argument: " << arg << std::endl;
                return 1;
            }
        } else if (argc == 3) {
            std::string arg1 = argv[1];
            std::string arg2 = argv[2];

            if (arg1 == "--sha256") {
                UbuntuImageInfoImpl imageInfo;
                printSHA256(imageInfo, arg2);
            } else {
                std::cerr << "Invalid arguments: " << arg1 << " " << arg2 << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Invalid number of arguments." << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}