DEVKITPRO ?= /opt/devkitpro
DEVKITA64  ?= $(DEVKITPRO)/devkitA64

CC      = $(DEVKITA64)/bin/aarch64-none-elf-gcc
CXX     = $(DEVKITA64)/bin/aarch64-none-elf-g++
LD      = $(DEVKITA64)/bin/aarch64-none-elf-ld

# Network libraries
LIBS     = -lnx -lnn_socket -lsocket

CFLAGS   = -march=armv8-a+crc+crypto -mtune=cortex-a57 -fPIE \
           -I$(DEVKITPRO)/libnx/include \
           -I$(DEVKITPRO)/portlibs/switch/include \
           -O2 -Wall
CXXFLAGS = $(CFLAGS) -std=c++17
LDFLAGS  = -specs=$(DEVKITPRO)/libnx/switch.specs

TARGET   = main_nx
SOURCES  = main.cpp
OBJECTS  = $(SOURCES:.cpp=.o)

all: $(TARGET).nro

$(TARGET).elf: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET).nro: $(TARGET).elf
	$(DEVKITPRO)/tools/bin/elf2nro $< $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).nro
