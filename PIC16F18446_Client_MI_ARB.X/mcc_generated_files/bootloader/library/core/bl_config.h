/**
 * © 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip 
 * software and any derivatives exclusively with Microchip products. 
 * It is your responsibility to comply with third party license terms 
 * applicable to your use of third party software (including open 
 * source software) that may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, 
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, 
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE 
 * OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, 
 * EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE 
 * DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, 
 * MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
 * THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU 
 * HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 * 
 * @file        bl_config.h
 * @ingroup     mdfu_client_8bit
 *
 * @brief       This file contains macros and type definitions related to the
 *              bootloader client device configuration and bootloader settings.
 */

#ifndef BL_BOOT_CONFIG_H
/* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
#define BL_BOOT_CONFIG_H

#include <stdint.h>

/**
 * @ingroup mdfu_client_8bit
 * @def PIC_ARCH
 * Corresponds to the current device architecture.
 * This macro is used to conditionally compile parts of the code needed
 * for specific architectures inside the bootloader core firmware.
 */
#ifndef PIC_ARCH
#define PIC_ARCH /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
#endif
/**
 * @ingroup mdfu_client_8bit
 * @def BL_IMAGE_FORMAT_MAJOR_VERSION
 * Represents the major version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_MAJOR_VERSION (0x00) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_IMAGE_FORMAT_MINOR_VERSION
 * Represents the minor version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_MINOR_VERSION (0x03) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_IMAGE_FORMAT_PATCH_VERSION
 * Represents the patch version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_PATCH_VERSION (0x00) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_VECTORED_INTERRUPTS_ENABLED
 * Indicates that the bootloader supports vectored interrupts in the application.
 */
#define BL_VECTORED_INTERRUPTS_ENABLED (1) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_APPLICATION_START_ADDRESS
 * Start of the application memory space.
 */
#define BL_APPLICATION_START_ADDRESS (0x2000) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_APPLICATION_INTERRUPT_VECTOR_LOW
 * Start address of the low-priority interrupt vector.
 */
#define BL_APPLICATION_INTERRUPT_VECTOR_LOW (0x2004) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_DEVICE_ID_START_ADDRESS_U
 * Device ID address.
 */
#define BL_DEVICE_ID_START_ADDRESS_U (0x06U) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_APPLICATION_END_ADDRESS
 * End of the application memory space.
 */
#define BL_APPLICATION_END_ADDRESS (0x2FFF) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_IMAGE_PARTITION_SIZE
 * Defined size of the application memory space.
 */
#define BL_IMAGE_PARTITION_SIZE (0x1000U) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_STAGING_IMAGE_START
 * Start of the application download space.
 */
#define BL_STAGING_IMAGE_START (0x3000) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_STAGING_IMAGE_END
 * End of the application download space.
 */
#define BL_STAGING_IMAGE_END (0x3FFF)
/**
 * @ingroup mdfu_client_8bit
 * @def BL_STAGING_IMAGE_ID
 * Image area ID that identifies the download location of the transferred data.
 */
#define BL_STAGING_IMAGE_ID (1U) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
/**
 * @ingroup mdfu_client_8bit
 * @def BL_APPLICATION_IMAGE_COUNT
 * Number of application image spaces configured.
 */
#define BL_APPLICATION_IMAGE_COUNT (2U)

/**
* @ingroup mdfu_client_8bit
* @def PARTITION_ID_DATA_SIZE
* Size of the partition ID data in bytes.
*/
#define PARTITION_ID_DATA_SIZE (2U)

/**
* @ingroup mdfu_client_8bit
* @def VERSION_DATA_SIZE
* Size of the version data in bytes.
*/
#define VERSION_DATA_SIZE (4U)

/**
* @ingroup mdfu_client_8bit
* @def VERIFY_END_ADDRESS_SIZE
* Size of the verify end address data in bytes.
*/
#define VERIFY_END_ADDRESS_SIZE (4U)

/**
* @ingroup mdfu_client_8bit
* @def VERIFY_START_ADDRESS_SIZE
* Size of the verify start address data in bytes.
*/
#define VERIFY_START_ADDRESS_SIZE (4U)

/**
* @ingroup mdfu_client_8bit
* @def HASH_DATA_SIZE
* Size of the hash data in bytes.
*/
#define HASH_DATA_SIZE (4U)

/**
* @ingroup mdfu_client_8bit
* @def HASH_DATA_OFFSET
* Offset of the hash data in bytes, calculated as the sum of verify start address size, verify end address size, version data size, and partition ID data size.
*/
#define HASH_DATA_OFFSET (VERIFY_START_ADDRESS_SIZE + VERIFY_END_ADDRESS_SIZE + VERSION_DATA_SIZE + PARTITION_ID_DATA_SIZE)

/**
* @ingroup mdfu_client_8bit
* @def ANTI_ROLLBACK_ENABLED
* Defines whether the anti-rollback feature is enabled or not.
*/
#define BL_ANTI_ROLLBACK_ENABLED (1)

/**
* @ingroup mdfu_client_8bit
* @enum bl_image_id_t
* @brief Contains codes corresponding to the various image IDs
* used in the system.
* @var IMAGE_ID::IMAGE_0
* 0x00 - Image ID 0 will always be the execution space, due to hardware limitations. The image will be located from address 0x2000 to address 0x2FFF
* @var IMAGE_ID::IMAGE_1
* Image ID 1 is the image space that resides from address [0x2000 + (0x1000 �? 1)] to address [0x2FFF + (0x1000 �? 1)]
*/
typedef enum
{
    IMAGE_0 = 0x00,
    IMAGE_1
} bl_image_id_t;

/**
* @ingroup mdfu_client_8bit
* @struct bl_footer_data_t
* @brief Contains metadata for the bootloader footer.
* @var bl_footer_data_t::applicationId
* Contains the identifier for the application. The high byte identifies where the image can be executed from (0x00 in most cases). The low byte identifies the image space where it will be stored.
* @var bl_footer_data_t::applicationVersion
* Contains the version of the application.
* @var bl_footer_data_t::verificationEndAddress
* Contains the end address for verification.
* @var bl_footer_data_t::verificationStartAddress
* Contains the start address for verification.
* @var bl_footer_data_t::verificationData
* Contains the verification hash value for verification.
*/
typedef struct
{
    uint16_t applicationId;
    uint32_t applicationVersion;
    uint32_t verificationEndAddress;
    uint32_t verificationStartAddress;
    uint32_t verificationData;
} bl_footer_data_t;
#endif // BL_BOOT_CONFIG_H
