#include "ubuntu_image_info.h"

#include <curl/curl.h>
#include <sstream>
#include <stdexcept>

#include "../external/json/json.hpp"

//Derived class implementation of UbuntuImageInfo
class UbuntuImageInfoImpl : public UbuntuImageInfo {
public:
    UbuntuImageInfoImpl() {
        std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
        jsonData = nlohmann::json::parse(UbuntuImageInfoImpl::downloadJson(url));
    }

    // Implementation of pure virtual methods
    std::vector<std::string> getSupportedReleases() override {
        std::vector<std::string> releases{};

        try {
            //Get all the products
            const auto &products = jsonData["products"];

            for (const auto &product: products.items()) {
                const std::string &release = product.key();
                // Check if the release name ends with "amd64"
                if (release.size() >= 5 && release.substr(release.size() - 5) == "amd64") {

                    //Check if the releases supported value is true
                    if (products[product.key()]["supported"].get<bool>()) {
                        releases.push_back(release);
                    }

                }
            }

        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to parse JSON data: " + std::string(e.what()));

        }

        return releases;
    }

    std::string getCurrentLTSVersion() override {
        std::vector<std::string> releases = getSupportedReleases();

        // Iterate backwards over the releases vector
        for (auto it = releases.rbegin(); it != releases.rend(); ++it) {
            const auto &release = *it;

            std::istringstream iss(release);
            std::string token;

            // Skip the first two tokens (com.ubuntu.cloud:server)
            std::getline(iss, token, ':');
            std::getline(iss, token, ':');

            // Get the version number token
            std::getline(iss, token, ':');

            // Check if the version number ends with ".04"
            if (token.size() >= 3 && token.substr(token.size() - 3) == ".04") {
                return token;
            }
        }

        // No LTS version found
        return "";

    }

    std::string getSHA256(const std::string &release) override {
        try {
            const auto &products = jsonData["products"];

            std::string releaseKey;

            if (release == "latest") {
                //Set the release key to the latest release
                if (!products.empty()) {
                    releaseKey = products.rbegin().key();
                } else {
                    throw std::runtime_error("No releases found in the JSON data");
                }

            } else {
                //Construct the release key from the version number
                //in the format "com.ubuntu.cloud:server:version:amd64"
                releaseKey = "com.ubuntu.cloud:server:" + release + ":amd64";
            }

            if (products.contains(releaseKey)) {
                const auto &versions = products[releaseKey]["versions"];

                if (!versions.empty()) {
                    const auto &lastVersion = versions.back();
                    const auto &items = lastVersion["items"];
                    if (items.contains("disk1.img")) {
                        return items["disk1.img"]["sha256"].get<std::string>();
                    }
                }

            }


        }
        catch (const std::exception &e) {
            throw std::runtime_error("Failed to retrieve SHA256: " + std::string(e.what()));
        }

        //No SHA found for release
        return "";

    }

private:
    static std::string downloadJson(const std::string &url) {
        CURL *curl = curl_easy_init();

        if (!curl) {
            throw std::runtime_error("Failed to initialize libcurl");
        }

        std::stringstream buffer; // Buffer to store the downloaded JSON data
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        CURLcode result = curl_easy_perform(curl);

        if (result != CURLE_OK) {
            throw std::runtime_error("Failed to download JSON data: " +
                                     std::string(curl_easy_strerror(result)));
        }

        curl_easy_cleanup(curl);

        return buffer.str();

    }

    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        auto *buffer = static_cast<std::stringstream *>(userdata);
        buffer->write(ptr, static_cast<std::streamsize>(size * nmemb));
        return size * nmemb;
    }

    nlohmann::json jsonData;

};