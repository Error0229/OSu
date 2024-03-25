#set text(
  font: "New Computer Modern"
) 
#align(center, text(20pt)[
  *OS HW1 Programming projects*
])
#align(right, [
資工三 110590001 黃政 \
資工三 110590004 林奕廷 \
資工三 110590016 劉硯皓 ])
分工: $1/3$ for each
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
exit
```

Result image
#figure(
  image("3.P1/result.png"),
  caption:[
    The result for `ls -l > out.txt`, `sort < out.txt`, `cat in.txt | sort -h --parallel=4`, `!!`, `rm out.txt`, `exit`
  ]
)

= Ch3 project 2
Commands
```bash
cd 3.P2
make
make install # install module
echo 1 > /proc/pid
cat /proc/pid
make remove # remove module
```
Result image
#figure(
  image("3.P2/result.png"),
  caption:[
    The result for `echo 1 > /proc/pid` and `cat /proc/pid`
  ]
)

= Ch3 project 3
Commands
```bash
cd 3.P3/macro
make
make install
sudo dmesg | tail
make remove
cd ../dfs
make
make install
sudo dmesg | tail
make remove
```
Result image
#grid(
  columns: 2,
  grid.cell(
    colspan: 1,    
    align: horizon,
    figure(
      image("3.P3/macro/result.png", width:90%),
      caption: [
        The result for `sudo dmesg | tail` after `make install` in `3.P3/macro`
      ]
    )
  ),
  grid.cell(
    colspan: 1,
    align: horizon,
    figure(
      image("./3.P3/dfs/result.png", width:90%),
      caption: [
        The result for `sudo dmesg | tail` after `make install` in `3.P3/dfs`
      ]
    )
  ) 
)

= Ch3 project 4
Commands
```bash
cd 3.P4/1
make 
make install
sudo dmesg | tail
make remove
cd ../2
make
sudo insmod ./collatz.ko start=40
sudo dmesg | tail
sudo rmmod collatz
```

Result image
#grid(
  columns: 2,
  grid.cell(
    colspan: 1,    
    align: horizon,
    figure(
      image("3.P4/1/result.png", width:90%),
      caption: [
        The result for `sudo dmesg | tail` after `make install` in `3.P4/1`
      ]
    )
  ),
  grid.cell(
    colspan: 1,
    align: horizon,
    figure(
      image("./3.P4/2/result.png", width:90%),
      caption: [
        The result for `sudo dmesg | tail` after `sudo insmod ./collatz.ko start=40` in `3.P4/2`
      ]
    )
  ) 
)
