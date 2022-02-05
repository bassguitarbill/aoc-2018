#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define UC_LC 'a' - 'A'
bool unitsMatch (char a, char b) {
  assert(a != 0 && b != 0);
  return (a - b == UC_LC || b - a == UC_LC);
}

#define POLYMER_SIZE 50000
int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int eof;
  char polymer[POLYMER_SIZE];
  fscanf(in, "%s", &polymer);
  bool noChange = false;
  while (noChange == false) {
    noChange = true;
    for (int i = 0; i < POLYMER_SIZE - 1; i++) {
      if (polymer[i] == 0) continue;
      int j = i + 1;
      while(polymer[j] == 0) {
        j++;
      }

      if (unitsMatch(polymer[i], polymer[j])) {
        polymer[i] = 0;
        polymer[j] = 0;
        noChange = false;
      }
      i = j - 1;
    }
  }

  int count = 0;
  for (int i = 0; i < POLYMER_SIZE; i++) {
    if (polymer[i] > 0) {
      count++;
      //printf("%c", polymer[i]);
    }
  }
  return count;
}

void printPolymer(char* polymer) {
  for (int i = 0; i < POLYMER_SIZE; i++) {
    if (polymer[i] > 0) {
      printf("%c", polymer[i]);
    }
  }
  puts("");
}

int solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int eof;
  char* originalPolymer = malloc(POLYMER_SIZE * sizeof(char));
  fscanf(in, "%s", originalPolymer);

  char* polymer = malloc(POLYMER_SIZE * sizeof(char));
  char shortestPolymer;
  int shortestPolymerLength = POLYMER_SIZE + 1;
  for (char c = 'a'; c <= 'z'; c++) {
    strcpy(polymer, originalPolymer);

    for (int i = 0; i < POLYMER_SIZE; i++) {
      if (polymer[i] == c || (polymer[i] + UC_LC) == c) {
        polymer[i] = 0;
      }
    }

    bool noChange = false;
    while (noChange == false) {
      noChange = true;
      for (int i = 0; i < POLYMER_SIZE - 1; i++) {
        if (polymer[i] == 0) continue;
        int j = i + 1;
        while(polymer[j] == 0) {
          j++;
        }

        if (unitsMatch(polymer[i], polymer[j])) {
          polymer[i] = 0;
          polymer[j] = 0;
          noChange = false;
        }
        i = j - 1;
      }
    }

    int count = 0;
    for (int i = 0; i < POLYMER_SIZE; i++) {
      if (polymer[i] > 0) {
        count++;
        //printf("%c", polymer[i]);
      }
    }

    if (count < shortestPolymerLength) {
      shortestPolymerLength = count;
      shortestPolymer = c;
    }
  }
  return shortestPolymerLength;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
