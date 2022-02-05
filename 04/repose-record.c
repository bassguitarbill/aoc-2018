#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct entry {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int id;
  bool wakesUp;
};

typedef struct entry entry;

struct guard {
  int id;
  int totalMinutesAsleep;
  int minutesAsleep[60];
};

typedef struct guard guard;

entry populateEntry(char* log) {
  entry e;
  e.year = atoi(strtok(log + 1, "-"));
  e.month = atoi(strtok(NULL, "-"));
  e.day = atoi(strtok(NULL, " "));
  e.hour = atoi(strtok(NULL, ":"));
  e.min = atoi(strtok(NULL, "]"));
  char* rest = strtok(NULL, "#");

  if (rest[1] == 'w') { // wakes up
    e.wakesUp = true;
  } else if (rest[1] == 'f') { // falls asleep
    e.wakesUp = false;
  } else {
    char* id = strtok(NULL, " "); // read up to the guard number
    e.id = atoi(id);
  }
  return e;
}

void printEntry(entry e) {
  printf("Y:%d M:%d D:%d H:%d M:%d", e.year, e.month, e.day, e.hour, e.min);
  if (e.id > 0) {
    printf(": Guard %d arrives\n", e.id);
  } else if (e.wakesUp) {
    printf(": wakes up\n");
  } else {
    printf(": falls asleep\n");
  }
}

int compareEntries(entry a, entry b) {
  if (a.year > b.year) return -1;
  if (a.year < b.year) return 1;
  if (a.month > b.month) return -1;
  if (a.month < b.month) return 1;
  if (a.day > b.day) return -1;
  if (a.day < b.day) return 1;
  if (a.hour > b.hour) return -1;
  if (a.hour < b.hour) return 1;
  if (a.min > b.min) return -1;
  if (a.min < b.min) return 1;
  return 0;
}

void sortEntries(entry* entries, int numEntries) {
  if (numEntries < 1) return;
  entry index = entries[0];
  entry* upper = calloc(numEntries, sizeof(entry));
  int ul = 0;
  entry* lower = calloc(numEntries, sizeof(entry));
  int ll = 0;

  for (int i = 1; i < numEntries; i++) {
    if (compareEntries(index, entries[i]) == 1) {
      upper[ul] = entries[i];
      ul ++;
    } else {
      lower[ll] = entries[i];
      ll++;
    }
  }

  sortEntries(upper, ul);
  sortEntries(lower, ll);

  entries[ll] = index;

  for (int i = 0; i < numEntries; i++) {
    if (i < ll) {
      entries[i] = lower[i];
    } else if (i > ll) {
      entries[i] = upper[i - ll - 1];
    }

  }
  free(lower);
  free(upper);
}

#define MAX_NUMBER_OF_GUARDS 25
int addGuardIdToList(guard* guards, int guardId) {
  int i = 0;
  while(guards[i].id != 0) {
    if (guards[i].id == guardId) return 0;
    i++;
  }
  assert(i < MAX_NUMBER_OF_GUARDS);
  guards[i].id = guardId;
  return i + 1; // Length of list of guards
}

guard findGuardById(guard* guards, int id) {
  for (int i = 0; i < MAX_NUMBER_OF_GUARDS; i++) {
    if (guards[i].id == id) return guards[i];
  }
}
int findGuardIndexById(guard* guards, int id) {
  for (int i = 0; i < MAX_NUMBER_OF_GUARDS; i++) {
    if (guards[i].id == id) return i;
  }
}

void addSleepToGuard(guard* g, int index, int sleepMin, int wakeMin) {
  for (int i = sleepMin; i < wakeMin; i++) {
    g[index].minutesAsleep[i] += 1;
    g[index].totalMinutesAsleep += 1;
  }
}

int solveProblem1(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  int eof;

  int numLogs = 0;
  int numGuards = 0;
  guard* guards = calloc(MAX_NUMBER_OF_GUARDS, sizeof(guard));
  //int* ids = calloc(MAX_NUMBER_OF_GUARDS, sizeof(int));
  entry* entries = calloc(1000, sizeof(entry));
  char* log = malloc(50);
  entry e;
  while(fgets(log, 50, in) != NULL) {
    e = populateEntry(log);
    if (e.id > 0) {
      int ng = addGuardIdToList(guards, e.id);
      if (ng > 0) numGuards = ng;
    }
    entries[numLogs] = e;
    numLogs++;
  }
  sortEntries(entries, numLogs);

  int gIndex;
  for (int i = 0; i < numLogs; i++) {
    entry e = entries[i];
    if (e.id > 0) {
      gIndex = findGuardIndexById(guards, e.id);
    } else if (!e.wakesUp) {
      addSleepToGuard(guards, gIndex, e.min, entries[i+1].min);
      i++;
    }
  }

  int minutesAsleep = -1;
  guard sleepiestGuard;
  for (int i = 0; i < numGuards; i++) {
    if (guards[i].totalMinutesAsleep > minutesAsleep) {
      sleepiestGuard = guards[i];
      minutesAsleep = guards[i].totalMinutesAsleep;
    }
  }

  int minutesAsleepAtSleepiestMinute = -1;
  int sleepiestMinute;

  for (int i = 0; i < 60; i++) {
    if (sleepiestGuard.minutesAsleep[i] > minutesAsleepAtSleepiestMinute) {
      sleepiestMinute = i;
      minutesAsleepAtSleepiestMinute = sleepiestGuard.minutesAsleep[i];
    }
  }

  return sleepiestGuard.id * sleepiestMinute;
}


int solveProblem2(char* filepath) {
  FILE *in = fopen(filepath, "r");
  if (in == NULL) {
    printf("Error opening file %s\n", filepath);
    exit(1);
  }
  int eof;

  int numLogs = 0;
  int numGuards = 0;
  guard* guards = calloc(MAX_NUMBER_OF_GUARDS, sizeof(guard));
  //int* ids = calloc(MAX_NUMBER_OF_GUARDS, sizeof(int));
  entry* entries = calloc(1000, sizeof(entry));
  char* log = malloc(50);
  entry e;
  while(fgets(log, 50, in) != NULL) {
    e = populateEntry(log);
    if (e.id > 0) {
      int ng = addGuardIdToList(guards, e.id);
      if (ng > 0) numGuards = ng;
    }
    entries[numLogs] = e;
    numLogs++;
  }
  sortEntries(entries, numLogs);

  int gIndex;
  for (int i = 0; i < numLogs; i++) {
    entry e = entries[i];
    if (e.id > 0) {
      gIndex = findGuardIndexById(guards, e.id);
    } else if (!e.wakesUp) {
      addSleepToGuard(guards, gIndex, e.min, entries[i+1].min);
      i++;
    }
  }

  int sleepiestMinute;
  int mostTimesAsleepAtSleepiestMinute = -1;
  int sleepiestGuardInThisContext;
  for (int i = 0; i < numGuards; i++) {
    for (int j = 0; j < 60; j++) {
      int m = guards[i].minutesAsleep[j];
      if (m > mostTimesAsleepAtSleepiestMinute) {
        sleepiestMinute = j;
        sleepiestGuardInThisContext = guards[i].id;
        mostTimesAsleepAtSleepiestMinute = m;
      }
    }
  }
  return sleepiestMinute * sleepiestGuardInThisContext;
}

int main() {
  char* filepath = "data.txt";
  printf("Problem 1: '%d'\n", solveProblem1(filepath));
  printf("Problem 2: '%d'\n", solveProblem2(filepath));
  return 0;
}
