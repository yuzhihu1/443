#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <assert.h>

/**
 * file_ptr : the file pointer, ready to be read from.
 * hist: an array to hold 26 long integers.  hist[0] is the
 *       number of 'A', and hist[1] is the number of 'B', etc.
 * block_size: the buffer size to be used.
 * milliseconds: time it took to complete the file scan
 * total_bytes_read: the amount data in bytes read
 *
 * returns: -1 if there is an error.
 */
int get_histogram(
    FILE *file_ptr,
    long hist[],
    int block_size,
    long *milliseconds,
    long *total_bytes_read){

    for(int i=0; i<26; i++){
      hist[i]=0;
    }
    char buffer[block_size];
    struct timeb t_start, t_end;
    ftime(&t_start);
    long t_start_in_ms = t_start.time * 1000 + t_start.millitm;

    for(int i=0; !feof(file_ptr); i+=block_size){
       // empty the buffer
       memset(buffer, 0, block_size);
       // read file into buffer
       int n = fread(buffer, 1, block_size, file_ptr);
       // update the hist list
       for(int j = 0; j<block_size;j++){
         char c = buffer[j];
         int index;
         index = (int)c - 'A';
         hist[index] += 1;
       }
       *total_bytes_read += (long)n;
    }

    ftime(&t_end);
    long t_end_in_ms = t_end.time * 1000 + t_end.millitm;
    *milliseconds = t_end_in_ms - t_start_in_ms;

    fclose(file_ptr);
    return 0;
    }


int main(int argc, char const *argv[]) {
  const char *file = argv[1];
  int block_size = atoi(argv[2]);

  long hist[26];
  long milliseconds;
  long filelen;
  FILE *file_ptr;
  file_ptr = fopen(file, "r");

  int result = get_histogram(file_ptr, hist, block_size, &milliseconds, &filelen);

  assert(! (result < 0));

  printf("computed the histgram in %ld milliseconds \n", milliseconds);

  for(int i=0; i<26; i++){
    printf("%c : %ld\n", 'A' + i, hist[i]);
  }

  printf("total len = %ld\n", filelen);
  double rate;
  rate = (double)filelen/milliseconds * 1000;
  int final_rate = (int) rate;
  printf("Data rate: %d Bps\n", final_rate);


  return 0;
}
