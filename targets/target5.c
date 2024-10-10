#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_INPUT "/tmp/sploit5_output"

char* get_shell() {
  return "/bin/sh";
}

int bar(char *arg, char *out, size_t n) {
  memcpy(out, arg, n);
  return 0;
}

void foo(char input[], size_t n) {
  char buf[300];
  bar(input, buf, n);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "target5: argc != 2\n");
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("target5: open error");
    exit(EXIT_FAILURE);
  }

  char input[4096];
  ssize_t len = read(fd, input, sizeof(input));
  if (len < 0) {
    perror("target5: read failed");
    exit(EXIT_FAILURE);
  }

  setuid(0);
  foo(input, len);
  return 0;
}

// position: 0x472dff. insts: pop %rax; ret. bytes: 58c3

/*
position: 0x49ed02. insts: pop %rax; ret. bytes: 58c3
position: 0x49ee0b. insts: pop %rax; ret. bytes: 58c3
position: 0x49efa6. insts: pop %rax; ret. bytes: 58c3
*/

// position: 0x485d4b. insts: pop %rdx; ret. bytes: 5ac3

/*
position: 0x48709c. insts: syscall; ret. bytes: 0f05c3
position: 0x4874ea. insts: syscall; ret. bytes: 0f05c3
*/

// position: 0x48709c. insts: syscall; ret. bytes: 0f05c3


// position: 0x4218b0. insts: pop %rsi; ret. bytes: 5ec3
/*
position: 0x482922. insts: pop %rsi; ret. bytes: 5ec3
position: 0x485bb1. insts: pop %rsi; ret. bytes: 5ec3
position: 0x4865a0. insts: pop %rsi; ret. bytes: 5ec3
position: 0x486f63. insts: pop %rsi; ret. bytes: 5ec3
position: 0x4883a9. insts: pop %rsi; ret. bytes: 5ec3
position: 0x488400. insts: pop %rsi; ret. bytes: 5ec3
position: 0x48fb46. insts: pop %rsi; ret. bytes: 5ec3
*/


// position: 0x4042d6. insts: pop %rdi; ret. bytes: 5fc3
/*
position: 0x48098b. insts: pop %rdi; ret. bytes: 5fc3
position: 0x481bd3. insts: pop %rdi; ret. bytes: 5fc3
position: 0x481d75. insts: pop %rdi; ret. bytes: 5fc3
position: 0x4826ba. insts: pop %rdi; ret. bytes: 5fc3
position: 0x482747. insts: pop %rdi; ret. bytes: 5fc3
position: 0x4838b6. insts: pop %rdi; ret. bytes: 5fc3
position: 0x4842ee. insts: pop %rdi; ret. bytes: 5fc3
position: 0x484c18. insts: pop %rdi; ret. bytes: 5fc3
position: 0x484d83. insts: pop %rdi; ret. bytes: 5fc3
position: 0x4852e5. insts: pop %rdi; ret. bytes: 5fc3
position: 0x487cf7. insts: pop %rdi; ret. bytes: 5fc3
position: 0x487f90. insts: pop %rdi; ret. bytes: 5fc3
position: 0x488dea. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48c709. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48cac6. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48ce77. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48d204. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48d541. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48d5b8. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48d676. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48e44d. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48f056. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48f2f2. insts: pop %rdi; ret. bytes: 5fc3
position: 0x48f67b. insts: pop %rdi; ret. bytes: 5fc3
*/