gcc src/*.c -o bin/f1 -DSPEC_CPU -DSPEC_CPU_LINUX -lm -O0 -DTIMER_ON
gcc src/*.c -o bin/f2 -DSPEC_CPU -DSPEC_CPU_LINUX -lm -O0 -DRECORD_ON
gcc src_synt/*.c -o bin/f3 -DSPEC_CPU -DSPEC_CPU_LINUX -lm -O0 -DTIMER_ON
