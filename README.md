
# C++ Template for the Nucleo 144 (STM32L4R5ZI)

A minimal C++ project template for STM32L4R5ZI microcontroller with CMake build system and integrated debugging support.

## Features

- **C++17** support with proper ARM cross-compilation
- **CMake** build system with Makefile convenience wrapper
- **Integrated debugging** with OpenOCD and GDB
- **tmux-aware** debug sessions for optimal workflow
- **LED blink example** demonstrating GPIO control

## Prerequisites

- **ARM GCC toolchain**: `arm-none-eabi-gcc` and `arm-none-eabi-g++`
- **OpenOCD**: For debugging and flashing
- **st-flash**: For direct flashing (optional)
- **tmux**: For enhanced debugging experience (optional)

### Installation on macOS

```bash
# Install ARM toolchain
brew install arm-none-eabi-gcc

# Install OpenOCD
brew install openocd

# Install st-flash (optional)
pip install stm32loader

# Install tmux (optional)
brew install tmux
```

## Project Structure

```
stm_demo_cpp/
├── main.cpp                 # Main C++ application
├── system_stm32l4xx.c       # STM32 system configuration
├── startup_stm32l4r5xx.s    # ARM startup assembly
├── stm32l4r5zi.ld           # Linker script
├── CMakeLists.txt           # CMake build configuration
├── arm-none-eabi-toolchain.cmake  # ARM cross-compilation setup
├── Makefile                 # Convenience wrapper
└── README.md                # This file
```

## Building

### Quick Start

```bash
# Build the project
make

# Clean build files
make clean

# Show available targets
make help
```

### Build Process

The project uses CMake for the build system with a Makefile wrapper for convenience:

1. **CMake** handles cross-compilation and linking
2. **Makefile** provides simple commands for common tasks
3. **ARM tool-chain** compiles C++, C, and Assembly files
4. **Output**: `build/stm32_led_blink.elf` and `build/stm32_led_blink.bin`

## Flashing

### Using st-flash (Recommended)

```bash
# Flash to STM32
make flash
```

### Using OpenOCD

```bash
# Start OpenOCD server
make openocd

# In another terminal, flash using GDB
make gdb
```

## Debugging

### Quick Debug Session

```bash
# Start full debug session (tmux-aware)
make debug
```

This will:
- **In tmux**: Create a new window with OpenOCD and GDB
- **Outside tmux**: Run OpenOCD in background, then GDB

### Manual Debugging

```bash
# Terminal 1: Start OpenOCD
make openocd

# Terminal 2: Start GDB
make gdb
```

### Debug Features

- **Automatic breakpoint** at `main()` function
- **TUI mode** enabled for better debugging experience
- **Program loading** and reset handling
- **Remote debugging** via OpenOCD

## Hardware Setup

### STM32L4R5ZI Nucleo-144

- **LED2**: Connected to GPIO Port B, Pin 7
- **Debug interface**: ST-Link V2-1
- **UART**: Available via ST-Link (LPUART1, requires correct SB setup)

### Pin Configuration

The example blinks LED2 (PB7) with a simple delay loop.

## Available Make Targets

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build the project |
| `make clean` | Clean build files |
| `make flash` | Flash to STM32 using st-flash |
| `make debug` | Start debug session (tmux-aware) |
| `make openocd` | Start OpenOCD server |
| `make gdb` | Start GDB client |
| `make help` | Show available targets |

## Troubleshooting

### Common Issues

1. **"cannot find entry symbol Reset_Handler"**
   - Ensure all source files are properly included in CMakeLists.txt
   - Check that startup file is compiled as Assembly

2. **OpenOCD connection issues**
   - Verify ST-Link is connected and recognized
   - Check USB permissions on Linux

3. **Build errors**
   - Ensure ARM toolchain is properly installed
   - Verify CMake version >= 3.16

## License

This template is provided as-is for educational and development purposes.

Linkerscript, startup & system files are taken from ST repositories:

- [stm32l4r5zi.ld](https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/NUCLEO-L4R5ZI/Templates/STM32CubeIDE/STM32L4R5ZITX_FLASH.ld)
- [startup_stm32l4r5xx.s](https://github.com/STMicroelectronics/cmsis-device-l4/blob/a2530753e86dd326a75467d28feb92e2ba7d0df2/Source/Templates/gcc/startup_stm32l4r5xx.s)
- [system_stm32l4xx.c](https://github.com/STMicroelectronics/cmsis-device-l4/blob/a2530753e86dd326a75467d28feb92e2ba7d0df2/Source/Templates/system_stm32l4xx.c)

## References

- [STM32L4R5ZI Reference Manual](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4x5xx-and-stm32l4x6xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Nucleo 144 User Manual](https://www.st.com/resource/en/user_manual/um2179-stm32-nucleo144-boards-mb1312-stmicroelectronics.pdf)
- [ARM GCC Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain)
- [OpenOCD Documentation](http://openocd.org/doc/html/index.html)
