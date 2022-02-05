
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define NUM_RULES 101

struct rule {
  char req;
  char res;
};

typedef struct rule rule;

typedef struct step {
  char name;
  int requiredFor;
  int dependsOn;
} step;


int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  rule* rules = calloc(NUM_RULES, sizeof(rule));
  int numRules = 0;
  char x, y;
  while(fscanf(in, "Step %c must be finished before step %c can begin.\n", &x, &y) != EOF) {
    rules[numRules].req = x;
    rules[numRules].res = y;
    numRules++;
  }

  rule* completedRules = calloc(NUM_RULES, sizeOf(rule));
  rule* availableRules = calloc(NUM_RULES, sizeOf(rule));
  rule* forbiddenRules = calloc(NUM_RULES, sizeOf(rule));


  return numRules;
}

int solveProblem2(char* filepath) {
  return 420;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
