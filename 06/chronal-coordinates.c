#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define NUM_COORDS 50
struct coord {
  int x;
  int y;
  bool isInfinite;
  int area;
};

typedef struct coord coord;

int taxicabDistance(coord a, coord b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

int getClosestCoord(coord* coords, coord c) {
  int minDistance = INT_MAX;
  bool dupe = false;
  int closestCoordIndex;
  for (int i = 0; i < NUM_COORDS; i++) {
    int td = taxicabDistance(coords[i], c);
    if (td < minDistance) {
      dupe = false;
      minDistance = td;
      closestCoordIndex = i;
    } else if(td == minDistance) {
      dupe = true;
    }
  }

  return dupe ? -1 : closestCoordIndex;
}

int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int x, y;
  int i = 0;
  coord* coords = calloc(NUM_COORDS, sizeof(coord));

  int xMax = -1;
  int yMax = -1;
  int xMin = INT_MAX;
  int yMin = INT_MAX;

  while(fscanf(in, "%d, %d\n", &x, &y) != EOF){
    coords[i].x = x;
    coords[i].y = y;
    coords[i].isInfinite = false;

    if (x > xMax) xMax = x;
    if (x < xMin) xMin = x;
    if (y > yMax) yMax = y;
    if (y < yMin) yMin = y;

    i++;
  }

  // printf("xMax:%d, xMin:%d, yMax:%d, yMin:%d\n", xMax, xMin, yMax, yMin);

  int width = (xMax - xMin + 1); 
  int* grid = calloc(width * (yMax - yMin + 1), sizeof(int));
  coord c;
  for (int x = xMin; x <= xMax; x++) {
    for (int y = yMin; y <= yMax; y++) {
      c.x = x;
      c.y = y;
      int cci = getClosestCoord(coords, c);
      grid[(x - xMin) + ((y - yMin) * width)] = cci;
      coords[cci].area += 1;
    }
  }

  for (int x = xMin - 1; x <= xMax + 1; x++) {
    c.x = x;
    c.y = yMin - 1;
    int cci = getClosestCoord(coords, c);
    coords[cci].isInfinite = true;
    c.y = yMax + 1;
    cci = getClosestCoord(coords, c);
    coords[cci].isInfinite = true;
  }

  for (int y = yMin - 1; y <= yMax + 1; y++) {
    c.y = y;
    c.x = xMin - 1;
    int cci = getClosestCoord(coords, c);
    coords[cci].isInfinite = true;
    c.x = xMax + 1;
    cci = getClosestCoord(coords, c);
    coords[cci].isInfinite = true;
  }

  int largestArea = 0;
  for (int i = 0; i < NUM_COORDS; i++) {
    coord c = coords[i];
    if (!c.isInfinite && c.area > largestArea) {
      largestArea = c.area;
    }
  }

  return largestArea;
}

int totalDistanceFromAllCoords(coord* coords, coord c) {
  int totalDistance = 0;
  for (int i = 0; i < NUM_COORDS; i++) {
    totalDistance += taxicabDistance(coords[i], c);
  }

  return totalDistance;
}

#define MINIMUM_DISTANCE 10000
int solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  
  int x, y;
  int i = 0;
  coord* coords = calloc(NUM_COORDS, sizeof(coord));

  int xMax = -1;
  int yMax = -1;
  int xMin = INT_MAX;
  int yMin = INT_MAX;

  while(fscanf(in, "%d, %d\n", &x, &y) != EOF){
    coords[i].x = x;
    coords[i].y = y;
    coords[i].isInfinite = false;

    if (x > xMax) xMax = x;
    if (x < xMin) xMin = x;
    if (y > yMax) yMax = y;
    if (y < yMin) yMin = y;

    i++;
  }

  int width = (xMax - xMin + 1); 
  int* grid = calloc(width * (yMax - yMin + 1), sizeof(int));
  coord c;
  int numWithinDistance = 0;
  for (int x = xMin; x <= xMax; x++) {
    for (int y = yMin; y <= yMax; y++) {
      c.x = x - xMin;
      c.y = y - yMin;
      int td = totalDistanceFromAllCoords(coords, c);
      if (td < MINIMUM_DISTANCE) numWithinDistance += 1;
    }
  }

  return numWithinDistance;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
