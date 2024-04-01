#ifndef UBUNTU_IMAGE_INFO_UBUNTU_IMAGE_INFO_H
#define UBUNTU_IMAGE_INFO_UBUNTU_IMAGE_INFO_H

#include <string>
#include <vector>

//Define the abstract base class UbuntuImageInfo
class UbuntuImageInfo {
public:
    //Declare a virtual destructor to ensure proper cleanup of derived objects
    virtual ~UbuntuImageInfo() = default;

    //Declare pure virtual methods
    virtual std::vector<std::string> getSupportedReleases() = 0;
    virtual std::string getCurrentLTSVersion() = 0;
    virtual std::string getSHA256(const std::string& release) = 0;

};

#endif //UBUNTU_IMAGE_INFO_UBUNTU_IMAGE_INFO_H