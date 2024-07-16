#include"headers.h"
#include"sharedmem.h"

/* Filename: readmem.c
 * Author  : Palla
 * Date    : 12-7-2024
 *
 * Description: This function reads a specific byte from a shared memory region that is addressed in 16-bit words. 
 * It calculates the correct 16-bit word address and determines whether to return the lower or upper byte of the word based on the provided byte offset
 *
 */

/* Name of the Function:- read_shared_mem_cpu2
    params                         OFFSET             pointer to memory 
   uint8_t read_shared_mem_cpu2(uint16_t offset,volatile uint16_t *shared_mem_cpu2) 
*/


uint8_t read_shared_mem_cpu2(uint16_t offset,volatile uint16_t *shared_mem_cpu2) 
{
  uint16_t word_addr = offset / 2; // Convert byte offset to 16-bit word address
  uint8_t byte_offset = offset % 2; // Determine if we need the lower or upper byte

  uint16_t word = shared_mem_cpu2[word_addr];
  //printf(" word is is %d\n",word);
  if (byte_offset == 0) {
    // printf(" word1 is %d\n",byte_offset);
    return word & 0x00FF;
  } else {
    //printf(" word2 is %d\n",byte_offset);
    return word >> 8;
  }
}

