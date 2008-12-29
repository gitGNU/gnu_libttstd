CC      = arm-linux-gcc

TOOLCHAINDIR = /usr/local/cross/gcc-3.3.4_glibc-2.3.2
INSTALLDIR = $(TOOLCHAINDIR)

INCS	= -I $(TOOLCHAINDIR)/include/ -I include/
CFLAGS  = -DLINUX_TARGET -DBARCELONA_TARGET $(INCS)
LDFLAGS = -lm

BIN = lib/libttstd.a 
MODULES = battery framebuffer gps touchscreen 
SMPLS = test draw
SMPLOBJ = $(SMPLS:%=examples/%.o)
 
OBJ = $(MODULES:%=src/%.o)

all: $(BIN) samples

$(BIN): $(OBJ)
	arm-linux-ar rsc $@ $^
	arm-linux-ranlib $@

src/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

samples: $(SMPLS)
	$(CC) examples/$<.o $(LDFLAGS) lib/libttstd.a -o bin/$<

$(SMPLS): $(SMPLOBJ)

examples/%.o: examples/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: doc
doc: 
	doxygen doc/ttstd.doxygen

clean:
	-rm src/*.o examples/*.o

install:
	-cp lib/* $(INSTALLDIR)/lib/
	-cp -r include/* $(INSTALLDIR)/include/
	
