#include"headers.h"
#include"sharedmem.h"

/* Filename: cpu2.c
 * Author  : Palla
 * Date    : 12-7-2024
 *
 * Description: This is the CPU2 Thread, which consumes data when recieves interrupt signal from CPU1, once the data
 * is consumed,it sends the ack to CPU1. 
 *
 */

/* Name of the Function:- cpu2_read_data
 * params                pointer to the memory                    array of characters    length 
   void cpu2_read_data(volatile shared_memory_t *shared_memory, volatile uint16_t *shared_mem_cpu2, char* buffer)
*/




void cpu2_read_data(volatile shared_memory_t *shared_memory, volatile uint16_t *shared_mem_cpu2, char* buffer)
{
  size_t bytes_received = 0;
  size_t received_data_size = 0;

  //check if data is available
  //if this is invalid and zero is return, keep waiting!!!
  while(read_shared_mem_cpu2(STATUS_READY_OFFSET,shared_mem_cpu2) != 1) printf("CPU 2 waiting \n");

  // Read data from shared memory
  for (size_t i = 0; i < (BUFFER_SIZE - 1) / 2; ++i)
  {
    //uint16_t word = SHARED_MEMORY_CPU2[DATA_OFFSET / 2 + i];
    uint16_t word = shared_mem_cpu2[DATA_OFFSET / 2 + i];
    buffer[received_data_size++] = word & 0xFF;
    buffer[received_data_size++] = (word >> 8) & 0xFF;
    // Clear status flag to indicate data has been processed
    shared_memory->status_ready = 0;
    shared_memory->status_ack = 1;
  }
}

/* CPU2 Thread */
int CPU2_thread(void* arg)
{
  (void)arg;

  // Receive data from CPU1
  // CPU2 reads data
  char received_message[BUFFER_SIZE] = {0};

  thread_param_t* params = (thread_param_t*) arg;

  #if FOR_X86 == 1
    volatile shared_memory_t* shared_memory = params->shared_mem;
    volatile uint16_t* shared_mem_cpu2 = (volatile uint16_t *)params->shared_mem;
  #else //port to the embedded board with dedicated address.
    volatile shared_memory_t* shared_memory = (volatile shared_memory_t *)SHARED_MEMORY_START_CPU2;
    volatile uint16_t* shared_mem_cpu2 = (volatile uint16_t *)SHARED_MEMORY_START_CPU2;
  #endif

  cpu2_read_data(shared_memory,shared_mem_cpu2,received_message);
  printf("CPU2: Received message: %s\n", received_message);
  printf("CPU2: Received message of %d bytes\n", strlen(received_message));
  return 0;
}

