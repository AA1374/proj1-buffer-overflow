#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#if __SIZEOF_LONG__ != 8
#error Build this as a 64-bit binary: use gcc -m64 ...
#endif

int main (int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s shellcode.bin\n", argv[0]);
		exit(-1);
	}

	void *buf;
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror("open");

	struct stat st;
	if (fstat(fd, &st) < 0)
		perror("fstat");

	buf = memalign(4096, st.st_size);
	if (!buf)
		perror("malloc");

	ssize_t cc = read(fd, buf, st.st_size);
	if (cc < 0)
		perror("read");
	if (cc != st.st_size)
		printf("incomplete read: got %ld, expected %ld\n", cc, st.st_size);

	close(fd);

	if (mprotect(buf, st.st_size, PROT_READ|PROT_WRITE|PROT_EXEC) < 0)
		perror("mprotect");

	void (*f)(void) __attribute__((noreturn)) = buf;
	f();
}
