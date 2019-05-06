SRC = ./src/USBCom.c ./src/http.c ./src/sensor_data.c ./src/QEI.c ./src/vg_keyboard.c ./src/Joy.c ./src/Protocol.c
INCLUDES = -I /usr/include/libusb-1.0/ -I ./include/ -I /opt/vc/include 
LIBFLAGS = -lusb-1.0 -lwiringPi -lm -lshapes -lpthread

All:
	gcc -o hydro main.c ${SRC} ${INCLUDES} ${LIBFLAGS}

