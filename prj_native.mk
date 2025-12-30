PRJ_NATIVE_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
PRJ_NATIVE_MK_DIR	:= $(shell dirname $(PRJ_NATIVE_MK_FILE))

I_HDD00			:= $(HOME)/iHDD00
MK_RACCOON_DIR		:= $(I_HDD00)/08.PROJECT/mk-raccoon

VPATH			+= $(PRJ_NATIVE_MK_DIR)/src_c
EXTRAINCDIRS		+= $(PRJ_NATIVE_MK_DIR)/inc

CFLAGS			+= -Wextra
CFLAGS			+= -Wno-unused-parameter
CFLAGS			+= -Wno-unused-result

OPT			:= s

include $(MK_RACCOON_DIR)/gcc_native.mk
# include $(MK_RACCOON_DIR)/llvm_native.mk
