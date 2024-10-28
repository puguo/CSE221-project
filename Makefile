
CC = gcc
CFLAGS = -Werror -O0
SRC_FILES = $(wildcard CPU/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
EXECUTABLES = $(SRC_FILES:.c=)
LOG_DIR = logs

all: $(EXECUTABLES)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

context_switch_overhead: context_switch_overhead.o
	$(CC) $(CFLAGS) $< -o $@

run: all
	@mkdir -p $(LOG_DIR)
	@echo "Running executables..."
	@./CPU/context_switch_overhead
	@for i in {1..99}; do ./CPU/context_switch_overhead; done
	@./CPU/measurement_overhead
	@./CPU/procedure_call_overhead
	@./CPU/syscall_overhead
	@./CPU/task_creation_overhead

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLES) $(LOG_DIR)/*.log

.PHONY: all run clean
