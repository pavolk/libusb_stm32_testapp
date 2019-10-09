# libusb_stm32_testapp
This is a simple libusb-application to benchmark the USB-connection to the STM32f4-Discovery board with this [firmware](https://github.com/pavolk/stm32_usb_test_wcid.git).

# Prepare the workspace

This was developed and tested on a host with Windows 10, but should work with any Linux distribution as well.

## Get the sources

`
git clone https://github.com/pavolk/libusb_stm32_testapp.git
cd libusb_stm32_testapp
`

## Install dependencies with `vcpck`

See (here)[https://github.com/microsoft/vcpkg/blob/master/README.md] for the documentation on installation and getting started with `vcpckg` C++ package manager.

Then just run following to install `libusb` to the host:

`
bootstrap.bat
`

# Build

`
mkdir build
cd build
cmake ..
cmake --build . --config Debug
`

# Open in Visual Studio

`
start libusb_stm32_testapp.sln
`

