#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "argc not correct.\n");
    return 1;
  }

  char *p = argv[1];

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");
  printf("  mov rax, %ld\n", strtol(p, &p, 10));

  while (*p) {
    if (*p == '+' || *p == '-') {
      bool isAdd = (*p == '+');
      p++;
      printf("  %s rax, %ld\n", isAdd ? "add" : "sub", strtol(p, &p, 10));
      continue;
    }

    fprintf(stderr, "unexoected chars: '%c'\n", *p);
    return 1;
  }

  printf("  ret\n");
  return 0;
}
