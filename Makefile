CC = gcc
CFLAGS = -Wall -Werror -g
BUILD_PATH=./

make_program: $(PROGRAM_NAME).c
	$(CC) $(CFLAGS) $(PROGRAM_NAME).c -o $(BUILD_PATH)$(PROGRAM_NAME)

# make hellgrind_default_check PROGRAM_NAME=<program_name>
helgrind_default_check: 
	$(MAKE) make_program PROGRAM_NAME=$(PROGRAM_NAME) 
	valgrind --tool=helgrind $(BUILD_PATH)$(PROGRAM_NAME) 
	rm -f $(BUILD_PATH)$(PROGRAM_NAME)

# Для отладки с помощью gdb

# 1 консоль:
# make make_program PROGRAM_NAME=<executable>
# valgrind --tool=helgrind --vgdb=yes --vgdb-error=0 <executable>

# 2 консоль:
# gdb ./<executable>
# target remote | blah blah blah