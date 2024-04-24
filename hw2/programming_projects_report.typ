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
- Compiler: gcc 11.4.0
= Ch4 project 1
Commands ```bash
cd 4.P1
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("4.P1/result.png"), caption: [
The result for `./main` in `4.P1`
])

= Ch4 project 2
Commands ```bash
cd 4.P2
gcc main.c -pthread -o main
./main
``` Result image
#figure(image("4.P2/result.png"), caption: [
The result for `./main` in `4.P2`
])

= Ch5 project 1
Commands ```bash
cd 5.P1
make fcfs
./fcfs schedule.txt
make sjf
./sjf schedule.txt
make priority
./priority schedule.txt
make round_robin
./round_robin schedule.txt
make priority_rr
./priority_rr schedule.txt
```

Result images
#grid(rows: 2, columns: 2, grid.cell(
  colspan: 1,
  align: horizon,
  figure(image("5.P1/result_fcfs.png", width: 95%), caption: [
  The result for `./fcfs schedule.txt` in `5.P1`
  ]),
), grid.cell(
  colspan: 1,
  align: horizon,
  figure(image("5.P1/result_sjf.png", width: 95%), caption: [
  The result for `./sjf schedule.txt` in `5.P1`
  ]),
), grid.cell(
  colspan: 1,
  align: horizon,
  figure(image("5.P1/result_priority.png", width: 95%), caption: [
  The result for `./priority schedule.txt` in `5.P1`
  ]),
), grid.cell(
  colspan: 1,
  align: horizon,
  figure(image("5.P1/result_round_robin.png", width: 95%), caption: [
  The result for `./round_robin schedule.txt` in `5.P1`
  ]),
), grid.cell(
  colspan: 1,
  align: horizon,
  figure(image("5.P1/result_priority_rr.png", width: 95%), caption: [
  The result for `./priority_rr schedule.txt` in `5.P1`
  ]),
))
// #import "@preview/timeliney:0.0.1"

// #timeliney.timeline(
//   show-grid: true,
//   {
//     import timeliney: *

//     headerline(group(([*Time line*], 19)))

//     taskgroup({
//       task($P_1$, (0, 3), style: (stroke: 3pt + black))
//       task($P_2$, (3, 4), (16, 19), style: (stroke: 3pt + black))
//       task($P_3$, (4, 6), (8, 9), (14, 15), style: (stroke: 3pt + black))
//       task($P_4$, (6, 8), (10, 11), (15, 16), style: (stroke: 3pt + black))
//       task($P_5$, (9, 10), style: (stroke: 3pt + black))
//       task($P_6$, (11, 14), style: (stroke: 3pt + black))
//     })
//     for i in range(0, 20) {
//       milestone(align(center, str(i * 5)), at: i, style: (stroke: 1pt + gray))
//     }
//   },
// )
