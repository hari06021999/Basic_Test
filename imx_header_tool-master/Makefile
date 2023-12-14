ROSS_COMPILE := aarch64-elf-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

CFLAGS := -I./common -I./imx8mm -DIMX8_MM -g
OBJS := $(wildcard *.c ./common/*.c ./imx8mm/*.c)

all:$(OBJS)
	gcc $(CFLAGS) -o imx_tool $^
