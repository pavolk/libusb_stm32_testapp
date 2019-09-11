
#include <iostream>
#include "usb.h"

int main()
{
	auto ctx = usb::init(7);

	auto devices = usb::get_devices(ctx);

	for (auto& d : devices) {
		std::cout << usb::get_device_descriptor(d) << std::endl;
	}

	return 0;
}