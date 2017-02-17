# include <stdio.h>
# include <stdlib.h>

char *fgets_or_exit(char *buffer, int size, FILE *stream)
{
  if (fgets(buffer, size, stream) == NULL) {
    exit(1);
  }
  return buffer;
}
