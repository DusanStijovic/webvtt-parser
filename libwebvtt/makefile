PROGRAM = program
BUILD_DIR = build

SOURCE_CPP_LIST = \
source/WebVTTParser.cpp \
source/main.cpp

INCLUDE_C_LIST = \
-Iinclude

OBJECTS_LIST = 
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_CPP_LIST:.cpp=.o)))

vpath %.cpp $(sort $(dir $(SOURCE_CPP_LIST)))

CC = g++ -c
LD = g++

FLAGS_CC = -MD -MP  $(INCLUDE_C_LIST)

FLAGS_LD= 

.phony: all
all : $(BUILD_DIR)/$(PROGRAM).o

$(BUILD_DIR)/$(PROGRAM).o : $(OBJECTS_LIST) makefile
	$(LD) $(FLAGS_LD) -o $(@) $(OBJECTS_LIST)


$(BUILD_DIR)/%.o : %.cpp makefile | $(BUILD_DIR)
	$(CC) $(FLAGS_CC) -o $(@) $(<)

$(BUILD_DIR) :
	mkdir $(@)

.phony: clean
clean :
	rm -rf $(BUILD_DIR)


-include $(wildcard $(BUILD_DIR)/*.d)
