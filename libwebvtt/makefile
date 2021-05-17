PROGRAM = program
BUILD_DIR = build

SOURCE_CPP_LIST = \
source/WebVTTParser.cpp \
source/main.cpp \
source/bufferImpl/Semaphore.cpp \
source/bufferImpl/SyncBuffer.cpp


INCLUDE_CPP_LIST = \
-Iinclude -Iinclude/bufferImpl

OBJECTS_LIST = 
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_CPP_LIST:.cpp=.o)))


vpath %.cpp  source source/bufferImpl 



$(info $(sort $(dir $(SOURCE_CPP_LIST))) ) 


CC = g++ -c --std=c++17
LD = g++

FLAGS_CC = -MD -MP  $(INCLUDE_CPP_LIST)

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
