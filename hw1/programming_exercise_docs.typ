#set text(
  font: "New Computer Modern"
) 
#align(center, text(20pt)[
  *OS HW1 Programming exercises*
])
#align(right, [資工三 110590004 林奕廷])
= 2.24 
Command
```bash
gcc ./2.24/main.c -o FileCopy
./FileCopy cat.gif copycat.gif
strace ./FileCopy cat.gif copycat.gif
```
The `copycat.gif` file produced in the same directory. 
#grid(
  columns: 2,
  grid.cell(
    colspan: 1,    
    align: horizon,
    figure(
      image("cat.gif", width:90%),
      caption: [
        copycat.gif
      ]
    )
  ),
  grid.cell(
    colspan: 1,
    align: horizon,
    figure(
      image("./2.24/result.png", width:90%),
      caption: [
        The last few line result of `strace ./FileCopy cat.gif copycat.gif` command
      ]
    )
  ) 
 )

= 3.19
#text(1.3em)[Version 1]

Commands
```bash
gcc ./3.19/v1.c -o time_v1
./time_v1 ls -l 
```
Result image
#figure(
  image("3.19/v1.png", width: 50%),
  caption: [
    The result of `./time_v1 ls -l` command
  ]
)
#pagebreak()
#text(1.3em)[Version 2]

Commands
```bash
gcc ./3.19/v2.c -o time_v2
./time_v2 ls -l 
```
Result image
#figure(
  image("3.19/v2.png", width: 80%),
  caption: [
    The result of `./time_v2 ls -l` command
  ]
)

= 3.21
Commands
```bash
gcc ./3.21/main.c -o collatz
./collatz 7
```

Result image
#figure(
  image("3.21/result.png", width: 50%),
  caption: [
    The result of `./collatz 7` command
  ]
)

#pagebreak()
= 3.27
Commands
```bash
gcc ./3.27/main.c -o filecopy
./filecopy in.txt out.txt
strace ./filecopy in.txt out.txt
```
Result image
#figure(
  image("3.27/result.png", width: 50%),
  caption: [
    The result of `strace ./filecopy in.txt out.txt` command
  ]
)
