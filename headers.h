#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <threads.h>


#define SHARED_MEMORY_START_CPU1 ((volatile uint8_t*) 0x20000000)// 0x20000000 - 0x20000040 -> 8 bits addressable
#define SHARED_MEMORY_START_CPU2 ((volatile uint16_t*) 0x80010)  // 0x80010-0x80030  -> 16 bits addressable 

#ifndef FOR_X86
  #define FOR_X86                                             1  // Make it enable -> 1 if you want to test in X86
#endif


#define BUFFER_SIZE                                         64  // 512 bits = 64 bytes
#define STATUS_READY_OFFSET                                 0
#define STATUS_ACK_OFFSET                                   1
#define DATA_OFFSET                                         2

