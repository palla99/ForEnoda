#include"headers.h"
#include"sharedmem.h"


/* Filename: cpu1.c
 * Author  : Palla
 * Date    : 12-7-2024
 *
 * Description: This is the CPU1 thread function writes to the shared memory,and interrupts the CPU2.
 * After processing the data CPU1 will  wait for ack from CPU2.
 *
 */

/* Name of the Function:- cpu1_write_data
 * params                pointer to the memory                    array of characters    length 
 * void cpu1_write_data(volatile shared_memory_t* shared_mem_cpu1,const char* data, size_t data_len)
*/

void cpu1_write_data(volatile shared_memory_t* shared_mem_cpu1,const char* data, size_t data_len)
{
  size_t bytes_sent = 0;
  //printf(" data is %d\n",data_len);
  //data_len = 0;// for cpu2 wait simulate
  /* Implement Buffer Overflow */

  while (bytes_sent < data_len)
  {
   // size_t chunk_size = (data_len - bytes_sent > (BUFFER_SIZE - 2)) ? (BUFFER_SIZE - 2) : (data_len - bytes_sent);
    size_t chunk_size;
    if (data_len - bytes_sent > (BUFFER_SIZE - 2)) // 30 
    {
      chunk_size = BUFFER_SIZE - 2;
      printf("Buffer Overflow detected \n");
      exit(EXIT_FAILURE);
    }
    else
    {
      chunk_size = data_len - bytes_sent;// 30
      //printf("chunk_size if data_len  %ld  - bytes_sent %ld  > BUFFER_SIZE %ld =  %ld chunk_size \n",data_len,bytes_sent,BUFFER_SIZE,chunk_size);
    }
    //printf("chunk_size is %ld\n",chunk_size);
    // Wait for CPU2 to process previous data, cpu1 wait as long as ack is 0 and 
    while (shared_mem_cpu1->status_ready != 0 || shared_mem_cpu1->status_ack == 0) printf("CPU 1 waiting \n");
    // Copy data to shared memory
    memcpy((void*)&shared_mem_cpu1->buffer, data + bytes_sent, chunk_size);//
    shared_mem_cpu1->status_ready = 1;// make it one if data is ready 
    // Set status flag to indicate data is available
    shared_mem_cpu1->status_ack = 0;
    // Update bytes sent
    bytes_sent += chunk_size;

  }
  while (shared_mem_cpu1->status_ready != 0 || shared_mem_cpu1->status_ack == 0); //printf("CPU 1 waiting \n");
  
  printf("CPU1: Ack received from CPU2 \n");// this message wakes up after ack signal from cpu2
}
/* CPU1 Thread */
int CPU1_thread(void* arg)
{
  thread_param_t* params = (thread_param_t*) arg;
  #if FOR_X86 == 1
    volatile shared_memory_t* shared_mem_cpu1 = params->shared_mem;
  #else // port to the embedded board with dedicated address.
    volatile shared_memory_t* shared_mem_cpu1 = (volatile shared_memory_t*)SHARED_MEMORY_START_CPU1
  #endif
  const char* data = params->data;
  size_t n = 0;
  n = strlen(data);
  printf("CPU1: Sent %d bytes\n", n);
  cpu1_write_data(shared_mem_cpu1,data,n);
  return 0;
}

