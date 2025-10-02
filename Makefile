#-----------------------------------------------------------------------------
# Author: Karla Mejia
# Simple Makefile for custom Shell Project

# This code is provided here solely for educational and portfolio purposes.  
# No permission is granted to copy, modify, or redistribute this code.  
#-----------------------------------------------------------------------------

# Compiler and flags
CC     = gcc
OPTS   = -O0    # No optimizations
DEBUG  = -g     # -g enables debugging with GDB
CFLAGS = $(OPTS) $(DEBUG)

# Target
TARGET = shell

all: $(TARGET)

shell: shell.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)