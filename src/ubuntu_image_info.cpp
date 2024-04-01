#include "ubuntu_image_info.h"

#include <curl/curl.h>
#include <sstream>
#include <stdexcept>

//Derived class implementation of UbuntuImageInfo
class UbuntuImageInfoImpl : public UbuntuImageInfo {
public:
    UbuntuImageInfoImpl() {
        std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
        jsonData = UbuntuImageInfoImpl::downloadJson(url);

        //TODO: Parse the JSON data and store it in a member variable for later use
    }

    std::string getJsonData() const {
        return jsonData;
    }

    // Implementation of pure virtual methods
    std::vector<std::string> getSupportedReleases() override {
        //TODO: Implement extracting supported releases from parsed JSON data
        std::vector<std::string> releases {};
        return releases;
    }

    std::string getCurrentLTSVersion() override {
        //TODO: Implement determining current LTS version from the parsed JSON data
        return "23.10";
    }

    std::string getSHA256(const std::string& release) override {
        //TODO: Implement finding the SHA256 has of the disk1.img for the given release
        return release;
    }

private:
    static std::string downloadJson(const std::string& url) {
        CURL* curl = curl_easy_init();

        if (!curl) {
            throw std::runtime_error("Failed to initialize libcurl");
        }

        std::stringstream buffer; // Buffer to store the downloaded JSON data
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        CURLcode result = curl_easy_perform(curl);

        if (result != CURLE_OK) {
            throw std::runtime_error("Failed to download JSON data: "+
            std::string(curl_easy_strerror(result)));
        }

        curl_easy_cleanup(curl);

        return buffer.str();

    }

    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
        auto* buffer = static_cast<std::stringstream*>(userdata);
        buffer->write(ptr, static_cast<std::streamsize>(size * nmemb));
        return size * nmemb;
    }

    std::string jsonData {"No data"};

};