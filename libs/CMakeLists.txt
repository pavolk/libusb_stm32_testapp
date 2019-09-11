
add_library(usb++ usb/usb.cpp)

target_include_directories(usb++
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/usb
)
