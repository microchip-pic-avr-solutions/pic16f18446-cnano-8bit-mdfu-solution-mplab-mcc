#!/bin/sh
# - File: build_image.sh
# - Description: Shell script that can be executed in the MPLAB X post build
# -               step or ran as a standalone script to build the
# -               application binary image.
# - 
# - Requirements: pyfwimagebuilder, python
# - Arguments:
# -     $1 - the IS_DEBUG argument is passed by the MPLAB post build step to identify if the application is being built to a hex file (for production) or an elf file (for debugging).
# -     $2 - the INPUT_IMAGE_PATH argument is passed by the MPLAB post build step and it holds the output image path. (.hex or .elf normally)
# ----------------------------------------------------------------------------
# - if the script was not called with arguments; setup the arguments manually

if [ "$1" = "" ]; then
    IS_DEBUG=false
else 
    IS_DEBUG="$1"
fi
if [ "$2" = "" ]; then
    INPUT_IMAGE_PATH="./dist/Standalone/production/PIC16F18446_Application.X.production.hex"
else
    INPUT_IMAGE_PATH="$2"
fi
# - relative path to client config file
CONFIG_FILE_PATH="../PIC16F18446_Client.X/mcc_generated_files/bootloader/configurations/bootloader_configuration.toml"
# For creating new images, update the image file name below and uncomment the line
OUTPUT_IMAGE_PATH="./Application_Binary_v1.img"

# - Ensure pyfwimagebuilder is installed
if ! python -c "import pyfwimagebuilder" &> /dev/null; then
    echo "pyfwimagebuilder not found, installing..."
    pip install pyfwimagebuilder
fi

# - Build the application binary
if [ "$IS_DEBUG" = false ]; then
    pyfwimagebuilder build -i $INPUT_IMAGE_PATH -c $CONFIG_FILE_PATH -o $OUTPUT_IMAGE_PATH
fi
