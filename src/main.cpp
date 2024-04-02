#include "ubuntu_image_info.cpp"
#include <iostream>

int main() {
    try {
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
                case 1: {
                    std::vector<std::string> releases = imageInfo.getSupportedReleases();
                    std::cout << "Currently supported releases:" << std::endl;
                    for (const auto &release: releases) {
                        std::cout << release << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::string ltsVersion = imageInfo.getCurrentLTSVersion();
                    if (!ltsVersion.empty()) {
                        std::cout << "Current LTS version: " << ltsVersion << std::endl;
                    } else {
                        std::cout << "Unable to find the current LTS version." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::string release;
                    std::cout << "Enter the release (or 'latest'): ";
                    std::cin >> release;
                    std::string sha256 = imageInfo.getSHA256(release);
                    if (!sha256.empty()) {
                        std::cout << "SHA256 for release " << release << ": " << sha256 << std::endl;
                    } else {
                        std::cout << "Couldn't find the specified version: " << release << std::endl;
                        std::cout << "Please check the version number and try again." << std::endl;
                        std::cout << "Example of a correct input: 22.04" << std::endl;
                    }
                    break;
                }
                case 4: {
                    std::cout << "Exiting..." << std::endl;
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
            }

            std::cout << std::endl;
        }


    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
