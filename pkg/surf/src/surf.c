#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int (*add)(int, int);
  char *error;
  void *math;

  math = dlopen("./libsurf.so", RTLD_LAZY);

  if (!math) {
    fprintf(stderr, "%s\n", dlerror());
    return 1;
  }

  dlerror();

  add = dlsym(math, "add");

  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return 1;
  }

  printf("%d\n", (*add)(2, 2));
  dlclose(math);
  return 0;
}