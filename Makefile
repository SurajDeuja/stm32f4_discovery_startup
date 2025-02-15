PROJ_NAME=main

STD_PERIPH=.

SRCS = main.c startup.c

CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb

OBJCOPY=arm-none-eabi-objcopy

OBJDIR = build

INCLUDES= -I . \
	  -I inc

CFLAGS  = -g3 -Wall -Wno-missing-braces -std=c99
CFLAGS += -mthumb -mcpu=cortex-m4 
CFLAGS += -mfloat-abi=soft -std=gnu99
LDFLAGS = -nostdlib -Wl,-Map,$(OBJDIR)/$(PROJ_NAME).map -g -T$(STD_PERIPH)/stm32f4.ld

CFLAGS += $(INCLUDES)

#SRCS += 

OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

all: $(OBJDIR)/$(PROJ_NAME).elf $(OBJDIR)/$(PROJ_NAME).hex $(OBJDIR)/$(PROJ_NAME).bin

$(OBJDIR)/%.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.hex: %.elf
	$(OBJCOPY) -O ihex $^ $@

%.bin: %.elf
	$(OBJCOPY) -O binary $^ $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf build
	rm -rf libraries
	#rm -f $(OBJDIR)/$(PROJ_NAME).elf
	#rm -f $(OBJDIR)/$(PROJ_NAME).hex
	#rm -f $(OBJDIR)/$(PROJ_NAME).bin
	#rm -f $(OBJDIR)/$(PROJ_NAME).map
	#find $(OBJDIR) -type f -name '*.o' -print0 | xargs -0 -r rm

# Dependdencies
$(OBJDIR)/$(PROJ_NAME).elf: $(OBJS) | $(OBJDIR)

