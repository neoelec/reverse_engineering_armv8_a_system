TARGET			:= hello

CSRCS			:= $(TARGET).c

CFLAGS			:= -pg
CFLAGS			+= -fno-builtin-printf

include ../../prj_native.mk

uftrace: $(OUTPUT)
	@uftrace $<

uftrace_argument: $(OUTPUT)
	@uftrace -A printf@arg1/s $<
