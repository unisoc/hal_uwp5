# hal_uwp5
HAL libraries for UNISOC uwp5 series SOC.

The SDKs provides device header files and driver libraries, include register
definitions and helper functions.

In order to use UWP SDKs, drivers and applications need to

1. Set CONFIG_HAS_UWP566x=y in Kconfig
2. Include driver/include/uwp566x_hal.h

After above operations, all of the peripheral driver library functions will
be accessible.

This repository is maintained by Unisoc, if you have any questions, please
create issue in https://github.com/unisoc/hal_uwp5/issues.
