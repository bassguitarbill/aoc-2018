#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANVAS_WIDTH 1024

struct claim {
  int id;
  int x;
  int y;
  int width;
  int height;
};

typedef struct claim claim;

void print_claim(claim c) {
  printf("ID: %d - x=%d, y=%d, %dx%d\n", c.id, c.x, c.y, c.width, c.height);
}

void print_canvas(int* canvas) {
  for (int x = 0; x < CANVAS_WIDTH; x++) {
    for (int y = 0; y < CANVAS_WIDTH; y++) {
      printf("%d", canvas[x + (CANVAS_WIDTH * y)]);
    }
    printf("\n");
  }
}

int count_conflicts(int* canvas) {
  int sum = 0;
  for (int x = 0; x < CANVAS_WIDTH; x++) {
    for (int y = 0; y < CANVAS_WIDTH; y++) {
      if(canvas[x + (CANVAS_WIDTH * y)] > 1) {
        sum += 1;
      }
    }
  }
  return sum;
}

void stake_claim(int* canvas, claim c) {
  for (int x = c.x; x < c.x + c.width; x++) {
    for (int y = c.y; y < c.y + c.height; y++) {
      canvas[x + (CANVAS_WIDTH * y)] += 1;
    }
  }
}

int check_claim(int* canvas, claim c) {
  for (int x = c.x; x < c.x + c.width; x++) {
    for (int y = c.y; y < c.y + c.height; y++) {
      if(canvas[x + (CANVAS_WIDTH * y)] > 1) return 0;
    }
  }
  return c.id;
}

int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }

  int* canvas = calloc(CANVAS_WIDTH*CANVAS_WIDTH, sizeof(int));
  
  int eof;

  claim c;
  eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  while(eof != EOF) {
    //print_claim(c);
    stake_claim(canvas, c);
    eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  }
  //print_canvas(canvas);
  return count_conflicts(canvas);
}

int solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }

  int* canvas = calloc(CANVAS_WIDTH*CANVAS_WIDTH, sizeof(int));
  
  int eof;

  claim c;
  eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  while(eof != EOF) {
    //print_claim(c);
    stake_claim(canvas, c);
    eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  }

  rewind(in);
  eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  while(eof != EOF) {
    //print_claim(c);
    if (check_claim(canvas, c) > 0) return c.id;
    eof = fscanf(in, "#%d @ %d,%d: %dx%d\n", &c.id, &c.x, &c.y, &c.width, &c.height);
  }
  //print_canvas(canvas);
  return count_conflicts(canvas);
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
