CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC = CPU.c driver.c
EXEC = scheduler

.PHONY: all fcfs round_robin sjf priority priority_rr clean help
all: help

fcfs:
	$(CC) $(CFLAGS) -DFCFS $(SRC) -o $@

round_robin:
	$(CC) $(CFLAGS) -DROUND_ROBIN $(SRC) -o $@

sjf:
	$(CC) $(CFLAGS) -DSJF $(SRC) -o $@

priority:
	$(CC) $(CFLAGS) -DPRIORITY $(SRC) -o $@

priority_rr:
	$(CC) $(CFLAGS) -DPRIORITY_RR $(SRC) -o $@

clean:
	rm -f fcfs round_robin sjf priority priority_rr

help:
	@echo "Compile the scheduler with a specific algorithm by running one of the following commands:"
	@echo "make fcfs"
	@echo "make round_robin"
	@echo "make sjf"
	@echo "make priority"
	@echo "make priority_rr"
