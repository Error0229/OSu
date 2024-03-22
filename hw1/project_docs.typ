#set text(
  font: "New Computer Modern"
) 
#align(center, text(20pt)[
  *OS HW1 Programming projects*
])
#align(right, [
資工三 110590001 黃政 \
資工三 110590004 林奕廷 \
資工三 110590016 劉硯皓])
= Environment
- OS: Ubuntu 22.04
- Kernel: 6.5.0-26-generic
- Compiler: gcc 12.3.9
= Ch2 project 1
Commands
```bash
cd 2.P1
make
make install # for install module
cat /proc/jiffies
cat /proc/seconds
make remove # for remove module
make clean
```
Result image
#figure(
  image("2.P1/result.png"),
  caption:[
    The result for `cat /proc/jiffies` and `cat /proc/jiffies`
  ]
)

= Ch3 project 1
Commands
```bash
gcc 3.P1/osh.c -o osh
./osh
ls -l > out.txt
sort < out.txt
cat in.txt | sort -h --parallel=4
!!
rm out.txt
```

Result image
#figure(
  image("3.P1/result.png"),
  caption:[
    The result for `ls -l > out.txt`, `sort < out.txt`, `cat in.txt | sort -h --parallel=4`, `!!`, `rm out.txt`
  ]
)
