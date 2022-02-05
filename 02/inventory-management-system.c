#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addChecksums(int* hasTwo, int* hasThree, char* line) {
  int* letterCount = calloc(26, sizeof(int));

  int i = 0;
  while(line[i] > 0) {
    letterCount[line[i] - 'a'] += 1;
    i++;
  }

  for (int j = 0; j < 26; j++) {
    if (letterCount[j] == 2) {
      *hasTwo += 1;
      break;
    }
  }

  for (int j = 0; j < 26; j++) {
    if (letterCount[j] == 3) {
      *hasThree += 1;
      break;
    }
  }

}

int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int hasTwo = 0;
  int hasThree = 0;
  int* p_hasTwo = &hasTwo;
  int* p_hasThree = &hasThree;

  int eof;
  char line[50];
  eof = fscanf(in, "%s", &line);
  while(eof != EOF) {
    addChecksums(p_hasTwo, p_hasThree, line);
    eof = fscanf(in, "%s", &line);
  }
  return hasTwo * hasThree;
}

char* compareLines(char* a, char* b) {
  int differenceOffset = -1;
  for (int offset = 0; a[offset] > 0 && b[offset] > 0; offset++) {
    if (a[offset] != b[offset]) {
      if (differenceOffset != -1) return NULL; // Second difference, return immediately
      differenceOffset = offset;
    }
  }
  if (differenceOffset == -1) return NULL; // No differences
  // printf("%s, %s\n", a, b); // Lol
  a[differenceOffset] = 0;
  char* outString = calloc(50, sizeof(char));
  strcpy(outString, a);
  strcpy(outString + differenceOffset, a + differenceOffset + 1);
  return outString;
}


char* checkForOffByOne(char** lines, int numLines) {
  if (numLines < 2) return NULL;

  for (int i = 0; i < numLines - 1; i++) {
    char* solution = compareLines(lines[numLines - 1], lines[i]);
    if (solution > 0) return solution;
  }
  return NULL;
}

char* solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int eof;
  char line[50];

  char** lines = calloc(1, sizeof(char*));
  int numLines = 0;

  eof = fscanf(in, "%s", &line);
  while(eof != EOF) {
    lines = realloc(lines, sizeof(char*) * (numLines + 1));
    lines[numLines] = malloc(50);
    strcpy(lines[numLines], line);
    numLines += 1;
    char* success = checkForOffByOne(lines, numLines);
    if (success) return success;
    eof = fscanf(in, "%s", &line);
  }
  printf("%d lines\n", numLines);
  return NULL;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%s'\n", solveProblem2(filepath));
  return 0;
}
