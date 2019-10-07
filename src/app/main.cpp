// @author: Pavol Kurina, pavol dot kurina at google dot com

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

#include "usb.h"

static uint16_t USB_VID = 0x0483; // STMicroelectronics
static uint16_t USB_PID = 0x0010;
static uint8_t OUT_EP_ADDR = 0x01;
static uint8_t IN_EP_ADDR = 0x81;

static size_t OUT_BUFFER_SIZE = 4 * 1024;
static unsigned OUT_TRANSFER_COUNT = 2000;

static size_t IN_BUFFER_SIZE = 8 * 1024;
static size_t IN_TRANSFER_COUNT = 2000;

using duration = std::chrono::high_resolution_clock::duration;

struct test_result {
	duration duration;
	size_t transfered_bytes;
};

static test_result bulk_test(usb::Handle handle, uint8_t ep_addr, size_t buffer_size, unsigned transfer_count)
{
	std::stringstream ss;
	ss << " ep_addr=0x" << std::hex << static_cast<unsigned>(ep_addr) << std::endl;
	ss << " buffer_size=" << std::dec << buffer_size << std::endl;
	ss << " transfer_count=" << std::dec << transfer_count << std::endl;
	std::cout << ss.str();

	std::vector<uint8_t> buffer(buffer_size, 0);
	size_t transfered_bytes = 0;

	auto start = std::chrono::high_resolution_clock::now();
	for (auto i = 0U; i < transfer_count; ++i) {
		transfered_bytes += usb::bulk_transfer(handle, ep_addr, &*std::begin(buffer), buffer.size(), 1000);
	}
	auto end = std::chrono::high_resolution_clock::now();
	return { end - start, transfered_bytes };
}

static void send_test(usb::Handle handle, uint8_t ep_addr, size_t buffer_size, unsigned transfer_count)
{
	std::cout << "Starting " << __func__ << "..." << std::endl;

	auto result = bulk_test(handle, ep_addr, buffer_size, transfer_count);

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(result.duration).count();
	std::cout << "Sending " << result.transfered_bytes << " bytes took " << milliseconds << "millis." << std::endl;
	std::cout << "Output transfer-rate was " << 1000.0 * (static_cast<double>(result.transfered_bytes) / milliseconds)
			  << " bytes/sec." << std::endl;
}

static void receive_test(usb::Handle handle, uint8_t ep_addr, size_t buffer_size, unsigned transfer_count)
{
	std::cout << "Starting " << __func__ << "..." << std::endl;

	auto result = bulk_test(handle, ep_addr, buffer_size, transfer_count);

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(result.duration).count();
	std::cout << "Received " << result.transfered_bytes << " bytes took " << milliseconds << "millis." << std::endl;
	std::cout << "Input transfer-rate was " << 1000.0 * (static_cast<double>(result.transfered_bytes) / milliseconds)
			  << " bytes/sec." << std::endl;
}

static usb::Device find_device(usb::Context ctx, uint16_t vid, uint16_t pid)
{
	auto devices = usb::get_devices(ctx);

	auto it = std::find_if(std::begin(devices), std::end(devices), 
		[vid, pid](const usb::Device& d) {
			return vid == usb::vendor_id(d) && pid == usb::product_id(d);
		});

	if (std::end(devices) == it) {
		throw usb::system_error("No such device found!", LIBUSB_ERROR_NOT_FOUND);
	}

	return *it;
}

int main()
{
	auto ctx = usb::init();

	try {
		auto device = find_device(ctx, USB_VID, USB_PID);
		auto handle = usb::open(device);
		usb::claim_interface(handle, 0);
		send_test(handle, OUT_EP_ADDR, OUT_BUFFER_SIZE, OUT_TRANSFER_COUNT);
		receive_test(handle, IN_EP_ADDR, IN_BUFFER_SIZE, IN_TRANSFER_COUNT);
	} catch (const usb::system_error& err) {
		std::cerr << "error: msg=\"" << err.what() << "\", code=" << err.code() << std::endl;
	}

	return 0;
}