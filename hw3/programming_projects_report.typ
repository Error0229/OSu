#set text(font: "New Computer Modern")
#align(center, text(20pt)[
  *OS HW2 Programming projects*
])
#align(right, [
  資工三 110590001 黃政 \
  資工三 110590004 林奕廷 \
  資工三 110590016 劉硯皓
])
分工: $1/3$ for each

= Environment
- OS: Ubuntu 22.04
- Kernel: Linux 5.15.153.1-microsoft-standard-WSL2
- Compiler: gcc 13.1.0
= Ch7 project 1
Commands ```bash
cd 7.P1
make
./pool
``` Result image
#figure(image("7.P1/result.png"), caption: [
The result for `./main` in `4.P1`
])
#pagebreak()
= Ch7 project 2
Commands ```bash
cd 7.P2
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("7.P2/result.png", width: 50%), caption: [
The result for `./main` in `7.P2`
])

= Ch7 project 3
Commands ```bash
cd 7.P3
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("7.P3/result.png"), caption: [
The result for `./main` in `7.P3`
])
#pagebreak()

= Ch7 project 4
Commands ```bash
cd 7.P4
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("7.P4/result.png"), caption: [
The result for `./main` in `7.P4`
])

= Ch8 project 1
Commands ```bash
cd 8.P1
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("8.P1/result.png"), caption: [
Part of the result for `./main` in `8.P1`
])

= Ch9 project 1
Commands ```bash
cd 9.P1
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("9.P1/result.png"), caption: [
The result for `./main` in `9.P1`
])
