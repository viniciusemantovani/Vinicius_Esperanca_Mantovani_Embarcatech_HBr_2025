#!/bin/bash

# This script automates the build process for a Raspberry Pi Pico project
# using CMake and Make. It then waits for a Pico to be connected in
# BOOTSEL mode and copies the compiled firmware to it.

# Exit immediately if a command exits with a non-zero status.
set -e

# --- 1. Setup Build Directory ---
BUILD_DIR="build"
echo "Creating and navigating to directory '$BUILD_DIR'..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# --- 2. Configure with CMake ---
echo "Configuring project with CMake..."
# Assumes the CMakeLists.txt is in the parent directory
cmake ..

# --- 3. Compile with Make ---
echo "Building project with make..."
make

# --- 4. Prepare for Deploy ---
FIRMWARE_FILE="smart_light.uf2"

# Check if the firmware file was actually created by the build process
if [ ! -f "$FIRMWARE_FILE" ]; then
    echo "-----------------------------------------------------"
    echo "Error: Build failed or produced no output file."
    echo "Expected to find '$FIRMWARE_FILE' in the build directory, but it's missing."
    exit 1
fi

echo "Build successful. Firmware file '$FIRMWARE_FILE' is ready."
echo "-----------------------------------------------------"

# --- 5. Find and Copy to Pico ---
echo "Please connect your Raspberry Pi Pico in BOOTSEL mode now."
echo "Waiting for Pico to mount as a USB drive..."

PICO_PATH=""
# We'll wait for up to 60 seconds
TIMEOUT=60
SECONDS_WAITED=0

# Loop until we find the Pico's mount point or we time out
while [ -z "$PICO_PATH" ]; do
    # This command is a robust way to find the mount point of a drive by its label
    # It avoids issues with different usernames or system configurations.
    # We use lsblk as a more portable alternative to "findmnt --label".
    PICO_PATH=$(lsblk -o LABEL,MOUNTPOINT | grep "RPI-RP2" | awk '{print $2}')

    if [ -n "$PICO_PATH" ]; then
        echo "" # Newline for cleaner output
        echo "Pico detected at mount point: $PICO_PATH"
        break
    fi

    if [ $SECONDS_WAITED -ge $TIMEOUT ]; then
        echo "" # Newline for cleaner output
        echo "Error: Timed out waiting for Pico."
        echo "Please ensure it's connected in BOOTSEL mode and shows up as 'RPI-RP2' drive."
        exit 1
    fi

    sleep 1
    SECONDS_WAITED=$((SECONDS_WAITED+1))
    echo -n "." # Progress indicator
done

echo "Copying '$FIRMWARE_FILE' to the Pico..."
cp "$FIRMWARE_FILE" "$PICO_PATH/"

# 'sync' ensures that the data is physically written to the device before we finish.
# This can help prevent file corruption.
sync

echo "Copy complete! Your Raspberry Pi Pico should now reboot with the new firmware."

