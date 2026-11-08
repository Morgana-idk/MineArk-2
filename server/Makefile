CC = gcc
CFLAGS = -Wall -Wextra -O2 -lraylib
TARGET = server
OBJECTS = server.c ../sharedLibs/World/world.c

all:$(TARGET)

$(TARGET) : $(OBJECTS)
	 clear && make clean && $(CC) $(OBJECTS) -o $(TARGET) && ./$(TARGET) && rm -f $(TARGET)

clean:
	rm -f $(TARGET)