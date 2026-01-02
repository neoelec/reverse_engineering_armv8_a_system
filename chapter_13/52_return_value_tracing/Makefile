TARGET			:= main

CSRCS			:= $(TARGET).c

CFLAGS			:= -pg
CFLAGS			+= -fno-builtin-printf

include ../../prj_native.mk

uftrace: $(OUTPUT)
	@uftrace $<

uftrace_return: $(OUTPUT)
	@uftrace -R add_func@retval $<
