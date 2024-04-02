# Ubuntu Cloud Image Info

This project provides a command line tool/interface for fetching the latest Ubuntu Cloud image information in Simplestreams format from https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json and provides methods to retrieve information about the supported Ubuntu releases, current LTS version, and SHA256 of the disk1.img item for a given release.

## Requirements

- C++17
- libcurl (for HTTP downloads)
- nlohmann/json (for JSON parsing)
- CMake (for building the project)

## Build Instructions (Linux & Mac)

1. Clone the repository:
   ```
   git clone <repository-url>
   ```

2. Generate the build files using CMake:
   ```
   cmake .
   ```

4. Build the project:
   ```
   make
   ```

5. Run the executable:
   ```
   ./ubuntu_image_info
   ```

### Windows

Building works on Visual Studio 2022 with `cmake --build .`

You will need to put libcurl.dll (renamed to libcurl-d.dll if it is a Debug build) and zlib1.dll from your vcpkg_installed folder in the same folder as the generated .exe to run it. (see ubuntu_image_info_win64.zip in Releases)

## Usage

The project provides a command-line interface (CLI) that allows you to retrieve information about Ubuntu Cloud images based on different options:

1. Get a list of all currently supported Ubuntu releases:
   ```
   ./ubuntu_image_info --supported-releases
   ```

2. Get the current Ubuntu LTS version:
   ```
   ./ubuntu_image_info --current-lts
   ```

3. Get the SHA256 of the disk1.img item for a given Ubuntu release:
   ```
   ./ubuntu_image_info --sha256 <release>
   ```
   Replace `<release>` with the desired Ubuntu release version (e.g. 20.04).

If no command line options are provided, an interactive interface will launch.

## Project Structure

- `include/ubuntu_image_info.h`: Header file containing the interface definition for the `UbuntuImageInfo` class.
- `src/ubuntu_image_info.cpp`: Source file containing the implementation of the `UbuntuImageInfoImpl` class derived from `UbuntuImageInfo`.
- `src/main.cpp`: Source file containing the main function and CLI implementation.
- `CMakeLists.txt`: CMake configuration file for building the project.

## Dependencies

- libcurl: Used for downloading the JSON data from the specified URL.
- nlohmann/json: Used for parsing the downloaded JSON data. (included)

## Supported Platforms

The project is designed to be built and run on Linux, macOS, and Windows.

## Design Decisions

- The project utilizes libcurl for downloading the JSON data from the specified URL. libcurl is a widely used library for making HTTP requests and provides cross-platform support.
- The project uses the nlohmann/json library for parsing the downloaded JSON data (the single header version is included in external/json). This library provides a simple and intuitive API for working with JSON data in C++.

## Development Steps

The development of this project followed these main steps:

1. Define the interface for the `UbuntuImageInfo` class in the header file.
2. Implement the derived class `UbuntuImageInfoImpl` in the source file, providing the functionality for each method.
3. Implement the CLI in the `main.cpp` file, parsing command-line arguments and calling the appropriate methods based on the provided options.
4. Configure the CMake build system to include the necessary dependencies and generate the build files.
5. Test the project on the different platforms to ensure its functionality.

## Notes

- The project assumes that the JSON data from the specified URL follows the Simplestreams format as defined in the provided documentation.
- The project focuses on the amd64 architecture for the Ubuntu Cloud images, as per the requirements.
