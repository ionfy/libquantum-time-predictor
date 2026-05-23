#include "gates.h"
#include "../MY_MACRO.h"
#include "stdio.h"
#include <stdlib.h>


CREATE_TIMER(tof, 1000)
CREATE_TIMER(cnot, 1000)
CREATE_TIMER(sig, 1000)

long long tof_c[100];
long long sig_c[100];
long long cnot_c[100];

int main(int argc, char **argv) {
  int tof_s;
  int cnot_s;
  int sig_s;
  {
    FILE *f = fopen("./data/tof_s.txt", "r");
    fscanf(f, "%d", &tof_s);
    for (int i = 0; i < tof_s; i++)
      fscanf(f, "%lld", tof_c + i);
    fclose(f);
  }
  {
    FILE *f = fopen("./data/sig_s.txt", "r");
    fscanf(f, "%d", &sig_s);
    for (int i = 0; i < sig_s; i++)
      fscanf(f, "%lld", sig_c + i);
    fclose(f);
  }
  {
    FILE *f = fopen("./data/cnot_s.txt", "r");
    fscanf(f, "%d", &cnot_s);
    for (int i = 0; i < cnot_s; i++)
      fscanf(f, "%lld", cnot_c + i);
    fclose(f);
  }
  long long tof_predicted = 0;
  for (int i = 0; i < tof_s; i++) {
    GET_FULLTIME(tof) = 0;
    for (int j = 0; j < 10; j++) {
      quantum_reg* reg = (quantum_reg*)malloc(sizeof(quantum_reg));
      int control1;
      int control2;
      int target;
      char filename[100];
      sprintf(filename, "./bdata/tof_%d.dat", i*10+j);
      FILE* f = fopen(filename, "rb");
      if (f == NULL) {
        printf("ERROR: Cannot open file: %s\n", filename);
        GET_FULLTIME(cnot) = 0;
        break;
      }
      fread(&control1, sizeof(int), 1, f);
      fread(&control2, sizeof(int), 1, f);
      fread(&target, sizeof(int), 1, f);
      fread(reg, sizeof(quantum_reg), 1, f);
      reg->hash = (int*)malloc(sizeof(int)*reg->hashw);
      reg->node = (quantum_reg_node*)malloc(sizeof(quantum_reg_node)*reg->size);
      fread(reg->node, sizeof(quantum_reg_node), reg->size, f);
      fread(reg->hash, sizeof(int), reg->hashw, f);
      fclose(f);
      quantum_toffoli(control1, control2, target, reg);
      free(reg->hash);
      free(reg->node);
      free(reg);
    }
    tof_predicted += (GET_FULLTIME(tof)/10 * tof_c[i]); 
  }

  long long sig_predicted = 0;
  for (int i = 0; i < sig_s; i++) {
    GET_FULLTIME(sig) = 0;
    for (int j = 0; j < 10; j++) {
      quantum_reg* reg = (quantum_reg*)malloc(sizeof(quantum_reg));
      int target;
      char filename[100];
      sprintf(filename, "./bdata/sig_%d.dat", i*10+j);
      FILE* f = fopen(filename, "rb");
      if (f == NULL) {
        printf("ERROR: Cannot open file: %s\n", filename);
        GET_FULLTIME(cnot) = 0;
        break;
      }
      fread(&target, sizeof(int), 1, f);
      fread(reg, sizeof(quantum_reg), 1, f);
      reg->hash = (int*)malloc(sizeof(int)*reg->hashw);
      reg->node = (quantum_reg_node*)malloc(sizeof(quantum_reg_node)*reg->size);
      fread(reg->node, sizeof(quantum_reg_node), reg->size, f);
      fread(reg->hash, sizeof(int), reg->hashw, f);
      fclose(f);
      quantum_sigma_x(target, reg);
      free(reg->hash);
      free(reg->node);
      free(reg);
    }
    sig_predicted += GET_FULLTIME(sig)/10 * sig_c[i]; 
  }

  long long cnot_predicted = 0;
  for (int i = 0; i < cnot_s; i++) {
    GET_FULLTIME(cnot) = 0;
    for (int j = 0; j < 10; j++) {
      quantum_reg* reg = (quantum_reg*)malloc(sizeof(quantum_reg));
      int control;
      int target;
      char filename[100];
      sprintf(filename, "./bdata/cnot_%d.dat", i*10+j);
      FILE* f = fopen(filename, "rb");
      if (f == NULL) {
        printf("ERROR: Cannot open file: %s\n", filename);
        GET_FULLTIME(cnot) = 0;
        break;
      }

      fread(&control, sizeof(int), 1, f);
      fread(&target, sizeof(int), 1, f);
      fread(reg, sizeof(quantum_reg), 1, f);
      reg->hash = (int*)malloc(sizeof(int)*reg->hashw);
      reg->node = (quantum_reg_node*)malloc(sizeof(quantum_reg_node)*reg->size);
      fread(reg->node, sizeof(quantum_reg_node), reg->size, f);
      fread(reg->hash, sizeof(int), reg->hashw, f);
      fclose(f);
      quantum_cnot(control, target, reg);
      free(reg->hash);
      free(reg->node);
      free(reg);
    }
    cnot_predicted += GET_FULLTIME(cnot)/10 * cnot_c[i]; 
  }

  printf("tof_t: %llu\n", tof_predicted);
  printf("cnot_t: %llu\n", cnot_predicted);
  printf("sig_t: %llu\n", sig_predicted);

  WRITE_LIST_TO_FILE("./data/tof_synt.txt",
                     GET_TIME_LIST(tof),
                     GET_TIME_COUNT(tof),
                     "%lld\n");
  WRITE_LIST_TO_FILE("./data/cnot_synt.txt",
                     GET_TIME_LIST(cnot),
                     GET_TIME_COUNT(cnot),
                     "%lld\n");
  WRITE_LIST_TO_FILE("./data/sig_synt.txt",
                     GET_TIME_LIST(sig),
                     GET_TIME_COUNT(sig),
                     "%lld\n");

  return 0;
}

