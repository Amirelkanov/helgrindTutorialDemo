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

#  Address 0x10c014 is 0 bytes inside data symbol "var"
# Location 0x10c014 is 0 bytes inside global var "var" declared at simple_data_race.c:3
# valgrind --tool=helgrind --vgdb=yes --vgdb-error=0 $(BUILD_PATH)$(PROGRAM_NAME)