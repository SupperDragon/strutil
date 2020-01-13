# Make Target
TARGET := test.exe

# Custom Command
CC := g++
RM := rm -f

# Custom Options and Flags
OUTPUT_OPTION = -o $@
CFLAGS        += -ansi -Wall -DMACOS -D_DARWIN_C_SOURCE
CPPFLAGS      +=
LDFLAGS       += -L ../

# Depended Library that Already Existed
LDLIBS := -lgmock -lstrutil

# File lists
sources := $(wildcard *.c *.cpp)
objects := $(subst .c,.o,$(subst .cpp,.o,$(sources)))
depends = $(wildcard $(subst .o,.d,$(objects)))

# Makefile targets
.PHONY: all
all: $(TARGET) libstrutil.so

$(TARGET): $(objects)
	$(CC) $(OUTPUT_OPTION) $(TARGET_ARCH) $^ $(LDFLAGS) $(LDLIBS) $(LOADLIBES)

libstrutil.so: ../libstrutil.so
	 ln -s $< $@


.PHONY: clean
clean:
	$(RM) $(objects) $(depends)

.PHONY: distclean
distclean: clean
	$(RM) $(TARGET)
	$(RM) libstrutil.so

make_debug:
	# TARGET : $(TARGET)
	# CC: $(CC)
	# OUTPUT_OPTION: $(OUTPUT_OPTION)
	# LDFLAGS: $(LDFLAGS)
	# LDLIBS: $(LDLIBS)

$(eval $(if $(filter $(MAKECMDGOALS),clean distclean),,include $(depends)))

# Makefile rules
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP -MT $@ -MF $(subst .o,.d,$@) $<
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c $<

%.o: %.c
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP -MT $@ -MF $(subst .o,.d,$@) $<
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c $<
