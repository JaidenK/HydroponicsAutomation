INCLUDEFLAGS = 
LIBFLAGS     = 
GCC          = gcc -Wall $(INCLUDEFLAGS) $(LIBFLAGS)
COMPILE      = $(GCC) -c
LINK         = $(GCC) -o
SOURCES      = sample_generator.c http.c sensor_data.c
OBJECTS      = $(patsubst %.c, %.o, $(SOURCES))
HEADERS      = http.h sensor_data.h
EXEC         = sample_generator


all: sample_generator

sample_generator:	$(OBJECTS) $(HEADERS)
	$(LINK) $(EXEC) $(OBJECTS)
	
%.o: %.c $(HEADERS)
	$(COMPILE) $<

todo:
	grep -n TODO $(SOURCES)

# Remove objects
clean:
	rm -f *.o
