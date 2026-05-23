#ifndef MY_MACRO_H

#define MY_MACRO_H

#include <stdio.h>
#include <time.h>

#define CREATE_COUNT(name) unsigned long long name##_COUNT = 0;

#define INIT_COUNT(name) extern unsigned long long name##_COUNT;

#define ADD_COUNT(name) name##_COUNT++;

#define GET_COUNT(name) name##_COUNT

#define CREATE_TIMER(name, maxcount)                                           \
  long long name##_TIME_LIST[maxcount];                                        \
  unsigned long long name##_TIME_COUNT = 0;                                    \
  long long name##_FULL_TIME = 0;

#define INIT_TIMER(name)                                                       \
  extern long long name##_TIME_LIST[];                                         \
  extern unsigned long long name##_TIME_COUNT;                                 \
  extern long long name##_FULL_TIME;

#define START_TIMER(name)                                                      \
  struct timespec name##_TIME_START, name##_TIME_STOP;                         \
  clock_gettime(CLOCK_MONOTONIC_RAW, &name##_TIME_START);

#define STOP_TIMER(name)                                                       \
  clock_gettime(CLOCK_MONOTONIC_RAW, &name##_TIME_STOP);                       \
  long long name##_TIME_DIFF =                                                 \
      (name##_TIME_STOP.tv_sec - name##_TIME_START.tv_sec) * 1000000000 +      \
      (name##_TIME_STOP.tv_nsec - name##_TIME_START.tv_nsec);                  \
  name##_TIME_LIST[name##_TIME_COUNT++] = name##_TIME_DIFF;                    \
  name##_FULL_TIME += name##_TIME_DIFF;

#define GET_FULLTIME(name) name##_FULL_TIME
#define GET_TIME_COUNT(name) name##_TIME_COUNT
#define GET_TIME_LIST(name) name##_TIME_LIST

#define WRITE_LIST_TO_FILE(file, list, size, format)                           \
  {                                                                            \
    FILE *f = fopen(file, "w");                                                \
    if (f) {                                                                   \
      for (int i = 0; i < size; i++)                                           \
        fprintf(f, format, list[i]);                                           \
      fclose(f);                                                               \
    }                                                                          \
  }

#define CREATE_SAVE(name, size)                                                \
  int name##_LOOK_LIST_SIZE = size;                                            \
  int name##_LOOK_LIST[size];                                                  \
  int name##_LOOK_COUNT = 0;

#define INIT_SAVE(name)                                                        \
  extern int name##_LOOK_LIST_SIZE;                                            \
  extern int name##_LOOK_LIST[];                                               \
  extern int name##_LOOK_COUNT;

#define SET_SAVE_FROM_FILE(name, file)                                         \
  {                                                                            \
    FILE *f = fopen(file, "r");                                                \
    fscanf(f, "%d", &(name##_LOOK_LIST_SIZE));                                 \
    name##_LOOK_LIST_SIZE *= 10;                                               \
    for (int i = 0; i < name##_LOOK_LIST_SIZE; i++)                            \
      fscanf(f, "%d", name##_LOOK_LIST + i);                                   \
    fclose(f);                                                                 \
  }

#define GET_SAVE_LIST(name) name##_LOOK_LIST
#define GET_SAVE_SIZE(name) name##_LOOK_LIST_SIZE

#define SET_VALUE_TO_CURR(name, value)                                         \
  int name##_CURR = 0;                                                         \
  for (; name##_CURR < name##_LOOK_LIST_SIZE; name##_CURR++)                   \
    if (name##_LOOK_COUNT == name##_LOOK_LIST[name##_CURR])                    \
      break;                                                                   \
  value = name##_CURR >= name##_LOOK_LIST_SIZE ? -1 : name##_CURR;             \
  name##_LOOK_COUNT++;

#endif
