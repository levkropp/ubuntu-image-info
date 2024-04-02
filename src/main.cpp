#include "ubuntu_image_info.cpp"
#include <iostream>

int main() {
    //Try to download the json file with libcurl
    std::cout << "Trying to download JSON Data.." << std::endl;
    try {
        UbuntuImageInfoImpl imageInfo;

        //Print the releases

        auto releases = imageInfo.getSupportedReleases();

        std::cout << "Releases: " << std::endl;

        for (auto release : releases) {
            std::cout << release << std::endl;
        }

        std::cout << "Current LTS Version: " << imageInfo.getCurrentLTSVersion() << std::endl;


        std::cout << "10.04 sha256: " << imageInfo.getSHA256("10.04") << std::endl;
        std::cout << "latest sha256: " << imageInfo.getSHA256("latest") << std::endl;



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "JSON Data downloaded successfully!" << std::endl;
    return 0;
}
