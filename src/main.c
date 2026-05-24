#include "../MY_MACRO.h"
#include "stdio.h"
#include <time.h>

#ifdef TIMER_ON
CREATE_TIMER(tof, 50000)
CREATE_TIMER(cnot, 50000)
CREATE_TIMER(sig, 50000)
#endif

#ifdef RECORD_ON
CREATE_SAVE(tof, 300);
CREATE_SAVE(cnot, 300);
CREATE_SAVE(sig, 300);
#endif

extern int mainf(int argc, char **argv);

int main(int argc, char **argv) {
  #ifdef RECORD_ON
  SET_SAVE_FROM_FILE(tof, "./data/tof_cl.txt");
  SET_SAVE_FROM_FILE(cnot, "./data/cnot_cl.txt");
  SET_SAVE_FROM_FILE(sig, "./data/sig_cl.txt");
  #endif

  #ifdef FULL_TIME
  struct timespec start, stop;
  clock_gettime(CLOCK_MONOTONIC, &start);
  #endif

  int res = mainf(argc, argv);

  #ifdef FULL_TIME
  clock_gettime(CLOCK_MONOTONIC, &stop);
  unsigned long long fullt = (stop.tv_sec - start.tv_sec) * 1000000000LL
    + (stop.tv_nsec - start.tv_nsec);
  printf("REAL: %lf\n", fullt/1e9);
  #endif

  #ifdef TIMER_ON
  printf("tof_t: %llu\n", GET_FULLTIME(tof));
  printf("cnot_t: %llu\n", GET_FULLTIME(cnot));
  printf("sig_t: %llu\n", GET_FULLTIME(sig));
  #endif

  #ifdef TIMER_ON
  WRITE_LIST_TO_FILE("./data/tof.txt",
                     GET_TIME_LIST(tof),
                     GET_TIME_COUNT(tof),
                     "%lld\n");
  WRITE_LIST_TO_FILE("./data/cnot.txt",
                     GET_TIME_LIST(cnot),
                     GET_TIME_COUNT(cnot),
                     "%lld\n");
  WRITE_LIST_TO_FILE("./data/sig.txt",
                     GET_TIME_LIST(sig),
                     GET_TIME_COUNT(sig),
                     "%lld\n");
  #endif

  return res;
}
