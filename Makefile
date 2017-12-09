CXXFLAGS=-Wall -O3 -g -I./CImg
OBJECTS=animation.o colortest.o led-animations.o screen.o snowflake.o xmastree.o
BINARIES=led-animations

RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a

LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -lpng -lX11


all: led-animations

led-animations: $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

%.o: %.cpp
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)
	$(MAKE) -C $(RGB_LIBDIR) clean
