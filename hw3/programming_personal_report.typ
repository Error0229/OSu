#set text(font: "New Computer Modern")
#align(center, text(20pt)[
  *OS HW3 Programming exercises*
])
#align(right, [資工三 110590004 林奕廷])

= Environment
- OS: Ubuntu 22.04
- Kernel: Linux 5.15.153.1-microsoft-standard-WSL2
- Compiler: gcc 11.4.0

= 7.15
Commands```bash
cd 7.15
gcc main.c -pthread -o main
./main
20
```
#figure(image("7.15/result.png"), caption: [
The result for `./main` in `7.15`
])

= 7.17
Commands```bash
cd 7.17
gcc main.c -pthread -o main
./main
200000000
```
#figure(image("7.17/result.png"), caption: [
The result for `./main` in `7.17`
])

= 8.32
Commands```bash
cd 8.32
gcc main.c -pthread -o main
./main
10
```
#figure(image("8.32/result.png"), caption: [
The result for `./main` in `8.32`
])

= 9.28
Commands```bash
cd 9.28
gcc main.c -pthread -o main
./main
19986
```
#figure(image("9.28/result.png"), caption: [
The result for `./main` in `9.28`
])
