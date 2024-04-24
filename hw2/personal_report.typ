#set text(font: "New Computer Modern")
#align(center, text(20pt)[
  *OS HW2 Programming exercises*
])
#align(right, [資工三 110590004 林奕廷])

= Environment
- OS: Ubuntu 22.04
- Kernel: Linux 5.15.153.1-microsoft-standard-WSL2
- Compiler: gcc 11.4.0

= 4.24
Commands```bash
cd 4.24
gcc main.c -pthread -o main
./main
3000000
```
#figure(image("4.24/result.png"), caption: [
The result for `./main` in `4.24`
])

= 4.27
Commands```bash
cd 4.27
gcc main.c -pthread -o main
./main
20
```
#figure(image("4.27/result.png"), caption: [
The result for `./main` in `4.27`
])

= 6.33
#show raw.line: it => {
  text(fill: gray)[#it.number]
  h(1em)
  it.body
}
```c
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
int decrease_count(int count) {
  if (available_resources < count) {
    return -1;
  } else {
    available_resources -= count;
    return 0;
  }
}
int increase_count(int count) {
  available_resources += count;
  return 0;
}

```
#show raw.line: it => { it.body }
\(a\) The data involved race condition is `available_resources`.\
\(b\) The race condition occurs at line 4, 7, 12.\
\(c\) The revised version using mutex is as follows:\
```c
#include <pthread.h>
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;
int decrease_count(int count) {
  pthread_mutex_lock(&mutex);
  if (available_resources < count) {
    pthread_mutex_unlock(&mutex);
    return -1;
  } else {
    available_resources -= count;
    pthread_mutex_unlock(&mutex);
    return 0;
  }
}
int increase_count(int count) {
  pthread_mutex_lock(&mutex);
  available_resources += count;
  pthread_mutex_unlock(&mutex);
  return 0;
}
```
