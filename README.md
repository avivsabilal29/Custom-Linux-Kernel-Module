# Sabilal Device Driver

This project demonstrates a basic implementation of a Linux character device driver. The driver, named **Sabilal Device**, allows user-space applications to read and write data to a virtual device.

## Features

- Provides a character device named `sabilal_device`.
- Implements basic `read` and `write` operations.
- Includes a buffer to store and manage messages.
- Demonstrates essential Linux kernel development concepts, such as:
  - Registering a character device.
  - Handling user-space and kernel-space communication.

## Prerequisites

- A Linux system with kernel development tools installed.
- Root privileges to load and unload the module.
- Basic knowledge of Linux kernel programming.

## Files

- **sabilal_device.c**: The main source file containing the driver implementation.

## How It Works

1. **Read Operation**:
   - User-space applications can read the device's default message: `Hello from Sabilal Device!`.

2. **Write Operation**:
   - User-space applications can write a message to the device. The message is stored in a buffer and can be read back.

3. **Device Initialization**:
   - During initialization, the driver registers the character device and assigns a major number dynamically.

4. **Device Removal**:
   - The driver unregisters the character device during module cleanup.

## Usage Instructions

### 1. Build the Driver

Compile the driver using `make`. Make sure you have a `Makefile` in the same directory. Example `Makefile`:

```makefile
obj-m += sabilal_device.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

Run:
```bash
make
```

### 2. Load the Driver
```bash
sudo insmod ldd.ko
```

### 3. Create the Device Node
Find the assigned major number from the kernel logs:
```bash
dmesg | grep "Sabilal Device registered"
```
Create the device node:
```bash
sudo mknod /dev/sabilal_device c <major_number> 0
```

### 4. Interact with the Device
Read from the device:
```bash
cat /dev/sabilal_device
```
Write to the device:
```bash
echo "Hello, Kernel!" > /dev/sabilal_device
```

### 5. Unload the Driver
Remove the module from the kernel:
```bash
sudo rmmod sabilal_device
```
Clean up the device node:
```bash
sudo rm /dev/sabilal_device
```