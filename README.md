# libusb_stm32_testapp
This is a simple libusb-application to benchmark the USB-connection to the STM32F4-Discovery board with this [firmware](https://github.com/pavolk/stm32_usb_test_wcid.git).

# Prepare the workspace

This was developed and tested on a host with Windows 10 and Visual Studio 2017. Since [CMake](https://cmake.org/) is used for building the application and [vcpck](https://github.com/microsoft/vcpkg) for dependency management, the application should build on hosts with Linux and recent gcc (supporting at least C++11) as well. For Linux hosts, test and updates to this description follows soon...

## Get the sources

```
git clone https://github.com/pavolk/libusb_stm32_testapp.git
cd libusb_stm32_testapp
```

## Install dependencies

See [here](https://github.com/microsoft/vcpkg/blob/master/README.md) for the documentation on installation and getting started with `vcpkg` C++ package manager.

The root `CMakeLists.txt` will use the environment variable `VCPKG_DIR` to look for the `vcpkg.cmake` file. Set the variable `VCPKG_DIR` to point to the root directory of the `vcpkg` installation. E.g. on Windows like this

```
setx VCPKG_DIR=c:\Users\<usename>\vcpkg
```

Then just run following to install `libusb` to the host:

```
bootstrap.bat
```

> **Note**: The script expects the `vcpkg` to be callable from the shell, e.g. the `PATH` variable should point to the root directory of the `vcpkg` installation.

# Configure and build

```
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```

# Open in Visual Studio

```
start libusb_stm32_testapp.sln
```

# Run benchmark

```
bin\Debug\stm32_bench.exe
```

Example output

```
Starting send_test...
 ep_addr=0x1
 buffer_size=4096
 transfer_count=2000
Sending 8192000 bytes took 11563millis.
Output transfer-rate was 708467 bytes/sec.
Starting receive_test...
 ep_addr=0x81
 buffer_size=8192
 transfer_count=2000
Received 1022000 bytes took 1628millis.
Input transfer-rate was 627764 bytes/sec.
```
