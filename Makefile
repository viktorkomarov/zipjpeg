TARGET_EXEC := jpegzip
SRC_DIR := src

$(TARGET_EXEC): 
	cc -o $(TARGET_EXEC) *.c  -Wall -Wextra -Wpedantic -Werror -std=c11

.PHONY: clean
clean:
	-rm $(TARGET_EXEC)