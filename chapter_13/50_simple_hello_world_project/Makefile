TARGET			:= hello

CSRCS			:= $(TARGET).c

CFLAGS			:= -pg

include ../../prj_native.mk

uftrace: $(OUTPUT)
	@uftrace $<

uftrace_argument: $(OUTPUT)
	@uftrace -A puts@arg1/s $<
