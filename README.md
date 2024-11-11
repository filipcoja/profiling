# KNN Profiling

This repository was used as a university project for TU Vienna. All the code can be found in the `knn` folder. This project tests custom instructions in order to improve performance. In this example we are covering the K-Nearest-Neighbour Algorithm. This project targets x86, RISCV and the bare metal FPGA CPU designed in the DDCA course at TU Vienna.

`compile` is the main script used for all three compilation methods. Here is a small piece of documentation also embedded in the script:
```
#!/bin/bash
# ./compile => rv32im isa without custom instruction
# ./compile custom => rv32im isa with and without custom instruction + compiled assembly
# ./compile callgrind => x86 isa with callgrind.out file to check for profiling
# ./compile miriv => rv32im isa with and without custom instruction for MiRiV CPU
```

`knn.c` is the base KNN implementation which can use both the regular abs() function as well as the custom absdsq() function.

`util.c` contains general utilk functions used for all implementations.

`libhelper.h` contains a wrapper containing the custom instruction in assembly.

`libc.c` is a C standard library used in the FPGA CPU.

`hex2mif.pl` converts the IHEX files to MIF files used to initialize FPGA memory.

`visualization/data.json` is the output of a `knn.c` run.

`visualization/knn.py` is a python script visualizing the classified points.


## Makefiles
The file `Makefile.x86` compiles to a regular x86 architecture and can be run by any x86 cpu.

The file `Makefile` compiles to RISCV using the [https://github.com/riscv-collab/riscv-gnu-toolchain](riscv-gnu-toolchain).

The file `Makefile.miriv` also compiles to RISCV which is able to run on our bare metal FPGA CPU.

