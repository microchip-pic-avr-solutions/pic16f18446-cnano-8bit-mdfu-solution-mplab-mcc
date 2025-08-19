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
 * @file    bl_memory.h
 * @ingroup bl_memory
 * @brief   This file contains implementation for the helper functions used with the NVM peripheral driver
 *
 */

#include "bl_memory.h"
#include <string.h>

/**@misradeviation{@advisory, 17.8} - The parameter is passed to this wrapper API to decrement and
 * write or erase bytes/words from consecutive memory locations until its value is zero. 
 * Assigning the value to a different local variable for each API will increase redundancy.
 */
/**@misradeviation{@advisory, 8.9} The static buffer will not be declared at local scope
 * due to portability concerns between various architectures.
 */

static uint16_t erasePageKey;
static uint16_t readKey;
static uint16_t byteWordWriteKey;
static uint16_t rowWriteKey;

// Static Buffer Declared to Assist in writing blocks of any length upto 1 page
/* cppcheck-suppress misra-c2012-8.9 */
static flash_data_t writeBuffer[PROGMEM_PAGE_SIZE];

void BL_MemoryUnlockKeysInit(key_structure_t keys)
{
    erasePageKey = keys.eraseUnlockKey;
    readKey = keys.readUnlockKey;
    rowWriteKey = keys.rowWriteUnlockKey;
    byteWordWriteKey = keys.byteWordWriteUnlockKey;
}

void BL_MemoryUnlockKeysClear(void)
{
    erasePageKey = 0;
    readKey = 0;
    rowWriteKey = 0;
    byteWordWriteKey = 0;
}

#if defined (BL_EEPROM_READ_ENABLED)

bl_mem_result_t BL_EEPROMRead(eeprom_address_t address, eeprom_data_t * buffer, size_t length)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    NVM_StatusClear();
    if (buffer == NULL) // Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((length <= (size_t) 0) || ((address + length) > (EEPROM_START_ADDRESS + EEPROM_SIZE))) // Check valid length
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((address < EEPROM_START_ADDRESS) || (address > (EEPROM_START_ADDRESS + EEPROM_SIZE)))// Check valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        for (uint16_t index = 0; index < length; index++)
        {
            buffer[index] = EEPROM_Read(address);

            /* cppcheck-suppress misra-c2012-17.8 */
            address++;
            while (NVM_IsBusy() == true)
            {

            }
            if (NVM_OK == NVM_StatusGet())
            {
                result = BL_MEM_PASS;
            }
            else
            {
                result = BL_MEM_FAIL;
                break;
            }
        }
    }
    return result;
}
#endif

#if defined (BL_EEPROM_WRITE_ENABLED)
bl_mem_result_t BL_EEPROMWrite(eeprom_address_t address, eeprom_data_t * buffer, size_t length)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    NVM_StatusClear();
    if (buffer == NULL)// Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((length <= (size_t) 0) || ((address + length) > (EEPROM_START_ADDRESS + EEPROM_SIZE)))// Check valid length
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((address < EEPROM_START_ADDRESS) || (address > (EEPROM_START_ADDRESS + EEPROM_SIZE)))// Check valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        for (uint16_t index = 0; index < length; index++)
        {
#if defined (_18FXXQ10_FAMILY_)
            NVM_UnlockKeySet(byteWordWriteKey);
#else
            NVM_UnlockKeySet(byteWordWriteKey);
#endif
            EEPROM_Write(address, buffer[index]);
            NVM_UnlockKeyClear();
            /* cppcheck-suppress misra-c2012-17.8 */
            address++;
            while (NVM_IsBusy() == true)
            {

            } // Wait while NVM is busy
            if (NVM_OK == NVM_StatusGet())
            {
                result = BL_MEM_PASS;
            } // If NVM_ERROR break
            else
            {
                result = BL_MEM_FAIL;
                break;
            }
        }
    }
    return result;
}
#endif

bl_mem_result_t BL_FlashRead(flash_address_t address, flash_data_t * buffer, size_t length)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    NVM_StatusClear();
    if (buffer == NULL)// Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if (address > PROGMEM_SIZE) // Check the valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((length <= (size_t) 0) || (length > (size_t) PROGMEM_PAGE_SIZE) || ((address + length) > (PROGMEM_SIZE + (uint24_t) 1)))// Check valid length
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        for (uint16_t index = 0; index <= length; index++)
        {
            NVM_UnlockKeySet(readKey);
            buffer[index] = FLASH_Read(address);
            NVM_UnlockKeyClear();
            /* cppcheck-suppress misra-c2012-17.8 */
            address++;
            while (NVM_IsBusy() == true)
            {

            }
            if (NVM_OK == NVM_StatusGet())
            {
                result = BL_MEM_PASS;
            }
            else
            {
                result = BL_MEM_FAIL;
                break;
            }
        }
    }
    return result;
}

bl_mem_result_t BL_FlashWrite(flash_address_t address, flash_data_t * buffer, size_t length) // using precompiled directives for differences in PIC18 and PIC16 implementation
{
    bl_mem_result_t result = BL_MEM_FAIL;
    // Get the number of bytes before the target update location
    uint16_t offsetByteCount = FLASH_PageOffsetGet(address);
    // Get the address of the page start
    flash_address_t pageStartAddress = FLASH_PageAddressGet(address);

    if (buffer == NULL)// Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if (address > PROGMEM_SIZE)// Check valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if ((length <= (size_t) 0) || (length > (size_t) PROGMEM_PAGE_SIZE) || ((address + length) > (PROGMEM_SIZE + (uint24_t) 1)))// Check valid length
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        // Arguments appear to be valid. Begin writing
        NVM_StatusClear();

        // Read the offset bytes into the work buffer starting at pageStartAddress
        if (offsetByteCount > 0U)
        {
            result = BL_FlashRead(pageStartAddress, &writeBuffer[0], offsetByteCount);
        }

        // Copy the data to write from the argument buffer into the write buffer
#ifndef _PIC18
        // Copying data words
        (void) memcpy(& writeBuffer[offsetByteCount], & buffer[0], length * 2U);
#else
        // Copying data bytes
        (void) memcpy(&writeBuffer[offsetByteCount], &buffer[0], length);
#endif

        // Save the total amount of bytes stored so far
        uint16_t loadedCount = (uint16_t) (offsetByteCount + length);

        // Get the number of bytes that will need to be read after the target location.
        uint16_t postReadByteCount = (uint16_t) (PROGMEM_PAGE_SIZE - loadedCount);

        // If postReadByteCount is non-zero then read the rest of the page starting from the target address range
        if (postReadByteCount > 0U)
        {
            result = BL_FlashRead((pageStartAddress + loadedCount), &writeBuffer[loadedCount], postReadByteCount);
        }
        else
        {
            // No pre-read is required
            result = NVM_OK;
        }

        if (BL_MEM_PASS == result)
        {
            // Perform the NVM erase and write sequence exactly how we did before.
            NVM_UnlockKeySet(erasePageKey);
            result = (bl_mem_result_t) FLASH_PageErase(pageStartAddress); // Erase page in flash
            while(NVM_IsBusy() == true)
            {
                
            }
            NVM_UnlockKeyClear();
        }

        if (BL_MEM_PASS == result)
        {
            // Write data to Flash row
            NVM_UnlockKeySet(rowWriteKey);
            result = (bl_mem_result_t) FLASH_RowWrite(pageStartAddress, writeBuffer);
            NVM_UnlockKeyClear();
        }
        else
        {
            result = BL_MEM_FAIL;
        }

        if (BL_MEM_PASS == result)
        {
            result = BL_MEM_PASS;
        }
        else
        {
            result = BL_MEM_FAIL;
        }
    }
    return result;
}

bl_mem_result_t BL_FlashCopy(flash_address_t srcAddress, flash_address_t destAddress, size_t length)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    flash_address_t destEndAddress = destAddress + length;
    flash_address_t srcEndAddress = srcAddress + length;
    uint32_t flashEndAddress = PROGMEM_SIZE + (uint32_t) 1;

    // Check if the given source and destination addresses are outside Flash memory range
    if (
            (srcAddress > PROGMEM_SIZE) ||
            (destAddress > PROGMEM_SIZE)
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
        // Check if the given source and destination regions are overlapping
    else if (
            (srcAddress == destAddress) ||
            ((srcEndAddress > destAddress) && (srcEndAddress < destEndAddress)) ||
            ((destEndAddress > srcAddress) && (destEndAddress < srcEndAddress))
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
        // Check if the length is invalid
    else if (
            (length <= (size_t) 0) ||
            (srcEndAddress > flashEndAddress) ||
            (destEndAddress > flashEndAddress)
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        // Read the data into the static buffer using the BL_FlashRead.
        result = BL_FlashRead(srcAddress, (flash_data_t *) & writeBuffer[0], length);
        while (NVM_IsBusy() == true)
        {

        }

        if (result == BL_MEM_PASS)
        {
            result = BL_FlashWrite(destAddress, (flash_data_t *) & writeBuffer[0], length);
        }
    }

    return result;
}

#if defined(PIC_ARCH) && !defined(_PIC18)
bl_mem_result_t BL_FlashReadUint16(flash_address_t address, uint16_t * data)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    NVM_StatusClear();
    if (data == NULL)// Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if (address > PROGMEM_SIZE) // Check the valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        NVM_UnlockKeySet(readKey);
        *data = (uint16_t) (
                ((uint16_t) (FLASH_Read(address + 1U) & 0x00FFU) << 8U)
                | (uint16_t) (FLASH_Read(address) & 0x00FFU)
                );
        NVM_UnlockKeyClear();

        while (NVM_IsBusy() == true)
        {

        }
        if (NVM_OK == NVM_StatusGet())
        {
            result = BL_MEM_PASS;
        }
        else
        {
            result = BL_MEM_FAIL;
        }
    }

    return result;
}

bl_mem_result_t BL_FlashReadUint32(flash_address_t address, uint32_t * data)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    NVM_StatusClear();
    if (data == NULL)// Check the valid buffer
    {
        result = BL_MEM_INVALID_ARG;
    }
    else if (address > PROGMEM_SIZE) // Check the valid address
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        NVM_UnlockKeySet(readKey);
        *data = (uint32_t) (
                (((uint32_t) FLASH_Read(address) & 0x00FFU)) |
                (((uint32_t) FLASH_Read(address + 1U) & 0x00FFU) << 8U) |
                (((uint32_t) FLASH_Read(address + 2U) & 0x00FFU) << 16U) |
                (((uint32_t) FLASH_Read(address + 3U) & 0x00FFU) << 24U)
                );
        NVM_UnlockKeyClear();

        while (NVM_IsBusy() == true)
        {

        }
        if (NVM_OK == NVM_StatusGet())
        {
            result = BL_MEM_PASS;
        }
        else
        {
            result = BL_MEM_FAIL;
        }
    }

    return result;
}
#endif
