INCLUDEFLAGS = -I /opt/vc/include -I /usr/include/libusb-1.0/
LIBFLAGS     = -lshapes -lm -lusb-1.0 -lwiringPi -lpthread
GCC          = gcc -Wall $(INCLUDEFLAGS) $(LIBFLAGS)
COMPILE      = $(GCC) -c
LINK         = $(GCC) -o
SOURCES      = hydro_pi.c QEI.c Joy.c
OBJECTS      = $(patsubst %.c, %.o, $(SOURCES))
HEADERS      = 
EXEC         = hydro_pi


all: $(EXEC)

$(EXEC): $(OBJECTS) 
	$(LINK) $(EXEC) $(OBJECTS)
	
%.o: %.c $(HEADERS)
	$(COMPILE) $<

run:	all
	sudo ./$(EXEC)
		
todo:
	grep -n TODO $(SOURCES)
	
opt:
	grep -n OPT $(SOURCES)

# Remove objects
clean:
	rm -f *.o

# Remove the exectuable
hella_clean: clean
	rm -f $(EXEC)
	
# Try to avoid filename conflicts?
.PHONY: run todo opt clean hella_clean
