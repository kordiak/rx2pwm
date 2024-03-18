CC=gcc
CFLAGS=-Wall -Wextra -Werror
BUILD_DIR =./build

all: ./build/test_rx2pwm

./build/rx2pwm.o: VehicleMovement.c VehicleMovement.h
	$(CC) $(CFLAGS) -c -o ./build/rx2pwm.o VehicleMovement.c

./build/test_rx2pwm.o: test_rx2pwm.c
	$(CC) $(CFLAGS) -c -o ./build/test_rx2pwm.o test_rx2pwm.c 

./build/test_rx2pwm: ./build/rx2pwm.o ./build/test_rx2pwm.o
	$(CC) $(CFLAGS) -o ./build/test_rx2pwm $(BUILD_DIR)/rx2pwm.o $(BUILD_DIR)/test_rx2pwm.o


run: all
	./build/test_rx2pwm
