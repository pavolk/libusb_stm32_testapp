# libusb_stm32_testapp
This is a simple libusb-application to benchmark the USB-connection to the STM32f4-Discovery board with this [firmware](https://github.com/pavolk/stm32_usb_test_wcid.git).

# Prepare the workspace

This was developed and tested on a host with Windows 10 and Visual Studio 2017. Since `CMake` is used for building and `vcpck` for dependency management, the application should build on hosts with Linux and recent gcc (supporting at least C++11) as well. For Linux hosts, test and updates to this description follows soon...

## Get the sources

```
git clone https://github.com/pavolk/libusb_stm32_testapp.git
cd libusb_stm32_testapp
```

## Install dependencies

See [here](https://github.com/microsoft/vcpkg/blob/master/README.md) for the documentation on installation and getting started with `vcpckg` C++ package manager.

Then just run following to install `libusb` to the host:

```
bootstrap.bat
```

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
