include $(DEFINES_MAKEFILE)

ifeq ("$(strip $(ELF_PREFIX))","")
TARGET_ELF = $(patsubst %.c,$(OUT_BIN)/%,$(notdir $(APP_SOURCE)))
else
TARGET_ELF = $(patsubst %.c,$(OUT_BIN)/$(ELF_PREFIX)-%,$(notdir $(APP_SOURCE)))
endif

all: $(TARGET_ELF)

include $(ELF_DEPEND)
include $(APP_DEPEND)
