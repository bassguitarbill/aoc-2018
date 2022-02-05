#include <stdio.h>
#include <stdlib.h>

int adjustFrequency(int freq, char* adj) {
  int sign = *adj == '+' ? 1 : -1;
  char* magnitude = adj + 1;
  return freq + (atoi(magnitude) * sign);
  //printf("'%s'\n", adj);
}

int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int sum = 0;

  int eof;
  char line[10];
  eof = fscanf(in, "%s", &line);
  while(eof != EOF) {
    sum = adjustFrequency(sum, line);
    eof = fscanf(in, "%s", &line);
  }
  return sum;
}

int solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int sum = 0;

  int* seen = calloc(1024 * 1024, sizeof(int));
  int offset = 512 * 1024;

  int eof;
  char line[10];
  while(1) {
    eof = fscanf(in, "%s", &line);
    while(eof != EOF) {
      sum = adjustFrequency(sum, line);
      int seenBefore = seen[sum + offset];
      if (seenBefore > 0) return sum;
      seen[sum + offset] = 1;
      eof = fscanf(in, "%s", &line);
    }
    rewind(in);
  }
  return -69;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
