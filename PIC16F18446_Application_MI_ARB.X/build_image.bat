REM - @file: build_image.bat
REM - @description: Batch script that can be executed in the MPLAB X post build
REM -               step or ran as a standalone script to build the
REM -               application binary image.
REM - 
REM - @requirements: pyfwimagebuilder, python
REM - @arguments:
REM -     %1 - the IS_DEBUG argument is passed by the MPLAB post build step to identify if the application is being built to a hex file (for production) or an elf file (for debugging).
REM -     %2 - the INPUT_IMAGE_PATH argument is passed by the MPLAB post build step and it holds the output image path. (.hex or .elf normally)
REM ----------------------------------------------------------------------------
REM - if the script was not called with arguments; setup the arguments manually
if "%1"=="" (set IS_DEBUG=false) else (set IS_DEBUG=%1)
if "%2"=="" (set INPUT_IMAGE_PATH=".\dist\Standalone\production\PIC16F18446_Application.X.production.hex") else (set INPUT_IMAGE_PATH=%2)
REM - relative path to client config file
set CONFIG_FILE_PATH="..\PIC16F18446_Client.X\mcc_generated_files\bootloader\configurations\bootloader_configuration.toml"
REM For creating new images, update the image file name below and uncomment the line
set OUTPUT_IMAGE_PATH=".\Application_Binary_v1.img" 

REM - Ensure pyfwimagebuilder is installed
WHERE pyfwimagebuilder >nul 2>nul

if %ERRORLEVEL% NEQ 0 (
    ECHO "pyfwimagebuilder not found, installing..."
    pip install pyfwimagebuilder
)

if %IS_DEBUG% == false (
    REM - Build the application binary
    pyfwimagebuilder build -i %INPUT_IMAGE_PATH% -c %CONFIG_FILE_PATH% -o %OUTPUT_IMAGE_PATH%
)