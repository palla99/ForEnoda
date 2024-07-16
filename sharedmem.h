
/* Shared Memory Structure */

typedef struct 
{
  uint8_t status_ready;        // 1 byte status flag to indicate data is ready
  uint8_t status_ack;          // 1 byte status flag to indicate data has been processed
  uint8_t buffer[BUFFER_SIZE - 2]; // 62 bytes data buffer
} shared_memory_t;


typedef struct 
{
    volatile shared_memory_t* shared_mem;
    const char* data;
} thread_param_t;

/* Function Prototypes */
int CPU1_thread(void* arg);
void cpu1_write_data(volatile shared_memory_t* shared_mem_cpu1,const char* data, size_t data_len);
int CPU2_thread(void* arg);
void cpu2_read_data(volatile shared_memory_t* shared_memory, volatile uint16_t *shared_mem_cpu2, char* buffer);
uint8_t read_shared_mem_cpu2(uint16_t offset,volatile uint16_t *shared_mem_cpu2);
