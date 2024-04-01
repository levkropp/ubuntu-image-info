#include "ubuntu_image_info.cpp"
#include <iostream>

int main() {
    //Try to download the json file with libcurl
    std::cout << "Trying to download JSON Data.." << std::endl;
    try {
        UbuntuImageInfoImpl imageInfo;

        //Print the JSON data
        std::string jsonData = imageInfo.getJsonData();
        std::cout << "JSON data: " << std::endl;
        std::cout << jsonData << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "JSON Data downloaded successfully!" << std::endl;
    return 0;
}
