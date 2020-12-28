DEVICE = atmega32u4
CLOCK = 16000000UL

PORT=/dev/ttyACM0

PROJECT_INCDIR = include
INCDIR = ../../wrapper/include $(PROJECT_INCDIR)
SRCDIR = src
OUTDIR = build

INCFLAGS = $(patsubst %,-I%,$(INCDIR))
OBJDIR = $(OUTDIR)/obj

COMPILE_FLAGS = $(INCFLAGS) -mmcu=$(DEVICE) -Wall -DF_CPU=$(CLOCK)
MODE = DEBUG
ifeq ($(MODE),DEBUG)
	COMPILE_FLAGS += -O0 -g
else
	COMPILE_FLAGS += -Os
endif

CC = avr-gcc
CCFLAGS = $(COMPILE_FLAGS)

XX = avr-g++
XXFLAGS = $(COMPILE_FLAGS)

AS = avr-as
ASFLAGS = 

LK = avr-ld
LKFLAGS = 

OBJCOPY = avr-objcopy
OBJCOPYFLAGS = 

DRIVER = avrdude
DRIVER_OPTIONS = -p$(DEVICE) -cavr109 -P$(PORT) -D -v

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(shell find src -name \*.c))
OBJS += $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(shell find src -name \*.cpp))
OBJS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%.o, $(shell find src -name \*.S))

EXE = lcd_blink
FIRMWARE = $(OUTDIR)/$(EXE).hex

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(PROJECT_INCDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $(OBJDIR)/$*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PROJECT_INCDIR)/%.h
	$(XX) $(XXFLAGS) -c $< -o $(OBJDIR)/$*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(AS) $(XXFLAGS) $< -o $(OBJDIR)/$*.o

$(OUTDIR)/$(EXE).elf: $(OBJS)
	$(LK) $(LKFLAGS) $^ -o $@

$(FIRMWARE): $(OUTDIR)/$(EXE).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) -O ihex $^ $@

.PHONY: clean deploy

deploy: $(FIRMWARE)
	$(DRIVER) $(DRIVER_OPTIONS) -Uflash:w:$(FIRMWARE):i

clean:
	find $(OUTDIR) ! -type d -exec rm -f '{}' \;