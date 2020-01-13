TARGET    = libstrutil.so
CC        = gcc
CFLAGS    += -fPIC -ansi -Wall -DMACOS -D_DARWIN_C_SOURCE
CPPFLAGS  +=
LDFLAGS   +=
AR        = ar
ARFLAGS   = -rc
SOFLAGS   = -shared -nostartfiles
RM        = rm
RMFLAGS   = -f
TARGET_ARCH   =
OUTPUT_OPTION = -o $@

# file lists
sources	= $(wildcard *.c)
objects	= $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(sources)))
depends	= $(wildcard $(patsubst %.o,%.d,$(objects)))

# Makefile command goals
.PHONY: all clean distclean makedebug gtest

# default command goal
all: $(TARGET)

gtest: $(TARGET)
	make -C test && test/test.exe

# Makefile command goal: TARGET
$(TARGET): $(objects)
	$(CC) $(LDFLAGS) $(SOFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) $^ $(LDLIBS) $(LOADLIBES)

clean:
	$(if $(wildcard $(objects)),$(RM) $(RMFLAGS) $(objects),)
	$(if $(wildcard $(depends)),$(RM) $(RMFLAGS) $(depends),)
	make -C test $@

distclean: clean
	$(if $(wildcard $(TARGET)),$(RM) $(RMFLAGS) $(TARGET),)
	make -C test $@

# dependencies
$(eval $(if $(filter $(MAKECMDGOALS),clean distclean makedebug),,include $(depends)))

# compile rules
%.o: %.c
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP -MT $@ -MF $(subst .o,.d,$@) $<
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c $<

# debug this Makefile itself
makedebug:
	#sources	: $(sources)
	#objects	: $(objects)
	#depends	: $(depends)
