/* Filename: main.c
 * Author  : Palla
 * Date    : 12-7-2024
 *
 * Description: This is the main file which initiates the threads and passes the array,and shared memory structure 
 * to both of the threads. The Threads Spawned are CPU1 and CPU2, the array data can be given through command line
 * args.
 *
 */



#include"headers.h"
#include"sharedmem.h"

int main(int argc, char *argv[]) 
{
  
  int total_length = 0;

  volatile shared_memory_t shared_memory; // Simulating shared memory
  
  
  //********** remember this is only simulaton *************
  // Simulating memory mapping for CPU1 and CPU2,
  //volatile shared_memory_t* shared_mem_cpu1 = &shared_memory;
  //volatile uint16_t* shared_mem_cpu2 = (volatile uint16_t*) &shared_memory;

  for (int i = 1; i < argc; i++) 
  {
        total_length += strlen(argv[i]);
  }
  // Allocate memory for the concatenated string, plus one for the null terminator
  char *concatenated_string = malloc(total_length + 1); 
  if (concatenated_string == NULL) 
  {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
  }
    // Concatenate the strings into the allocated memory
  concatenated_string[0] = '\0'; // Initialize the concatenated string
  for (int i = 1; i < argc; i++) 
  {
        strcat(concatenated_string, argv[i]);
        strcat(concatenated_string, " ");
  }
  //printf("concated string is %s",concatenated_string);

  // Initialize the shared memory flags to make sure CPU1 to get ready
  shared_memory.status_ready = 0;
  shared_memory.status_ack = 1;

  thrd_t thread1, thread2;
  thread_param_t params;
  params.shared_mem = &shared_memory;
  params.data = concatenated_string;

  // Create thread for CPU1
  if (thrd_create(&thread1, CPU1_thread, &params) != thrd_success) 
  {
    fprintf(stderr, "Failed to create CPU1 thread\n");
    return 1;
  }

  // Create thread for CPU2
  if (thrd_create(&thread2, CPU2_thread, &params) != thrd_success) 
  {
    fprintf(stderr, "Failed to create CPU2 thread\n");
    return 1;
  }

  // Wait for threads to finish
  thrd_join(thread1, NULL);
  thrd_join(thread2, NULL);
  return 0;
}

