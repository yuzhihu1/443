#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>

/**
 * populate a random array (which is already
 * allocated with enough memory to hold n bytes.
 */
void random_array(char *array, long bytes){
  for (int i=0; i<bytes; i++){
    char c = 'A' + (rand() % 26);
    array[i] = c;
  }
  array[bytes] = '\0';
}



int main(int argc, char const *argv[]) {
  const char *file = argv[1];
  int block_size = atoi(argv[3]);
  int total_bytes = atoi(argv[2]);
  struct timeb t_start, t_end;
  char buffer[block_size+1];
  int remain = total_bytes % block_size;
  int n = total_bytes / block_size;
  FILE *fp = fopen(file, "w");
  ftime(&t_start);
  long t_start_in_ms = t_start.time * 1000 + t_start.millitm;
  for (int i=0; i<n; i++){
    random_array(buffer, block_size);
    fwrite(buffer, 1, block_size, fp);
    fflush(fp);
  }

  if(remain != 0){
    memset(buffer, 0, block_size+1);
    random_array(buffer, remain);
    fwrite(buffer, 1, block_size, fp);
    fflush(fp);
  }
  ftime(&t_end);
  fclose(fp);
  long t_end_in_ms = t_end.time * 1000 + t_end.millitm;
  long total_time = t_end_in_ms - t_start_in_ms;
  printf("%ld\n", total_time);
  return total_time;
}
