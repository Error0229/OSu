#include <stdio.h>

int main(int argc, char *argv[]) {
  // 4 KB => 2^12 bytes
  // 32 bits, 32 - 12 = 20 bits for page number
  if (argc != 2) {
    printf("Usage: %s address\n", argv[0]);
    return 1;
  }
  unsigned int address = 0;
  if (sscanf(argv[1], "%d", &address) != 1) {
    printf("Invalid address\n");
    return 1;
  }
  int page = address >> 12;
  int offset = address & ((1 << 13) - 1);
  printf("The address %d contains:\npage number=%d\noffset=%d\n", address, page,
         offset);
}
