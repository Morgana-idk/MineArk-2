CC = gcc
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
TARGET = server
OBJECTS = server.c ../sharedLibs/World/world.c ../sharedLibs/Memoria/memoria.c

all:$(TARGET)

$(TARGET) : $(OBJECTS)
	 clear && make clean && $(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDLIBS) && ./$(TARGET) && rm -f $(TARGET)

clean:
	rm -f $(TARGET)