PROGRAM = program
BUILD_DIR = build

SOURCE_CPP_LIST = \
source/main.cpp\
source/logger/Logger.cpp\
source/decoder/UTF8ToUTF32StreamDecoder.cpp\
source/elements/Cue.cpp\
source/elements/Region.cpp\
source/elements/StyleSheet.cpp\
source/parser/Parser.cpp\
source/parser/CueParser.cpp\
source/parser/StyleSheetParser.cpp\
source/parser/RegionParser.cpp\
source/parser/ParserUtil.cpp\
source/parser/cue_text_tokenizer/CueTextTokenizer.cpp\
source/parser/cue_text_tokenizer/CueTextTokenizerState.cpp\
source/parser/cue_text_tokenizer/DataState.cpp\



INCLUDE_CPP_LIST =\
 -Iinclude\
 -Ilib/utfcpp/source\



LIB_CPP_LIST = \
-lpthread

OBJECTS_LIST = 
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_CPP_LIST:.cpp=.o)))

SOURCE_CPP_PATH =  $(sort $(dir $(SOURCE_CPP_LIST)))


vpath %.cpp  $(SOURCE_CPP_PATH)


$(info start)
$(info $(SOURCE_CPP_PATH)) 


CC = g++ -c --std=c++17
LD = g++

FLAGS_CC = -MD -MP -g $(INCLUDE_CPP_LIST)

FLAGS_LD= 

.phony: all
all : $(BUILD_DIR)/$(PROGRAM).o

$(BUILD_DIR)/$(PROGRAM).o : $(OBJECTS_LIST) makefile
	$(LD) $(FLAGS_LD) -o $(@) $(OBJECTS_LIST) $(LIB_CPP_LIST)


$(BUILD_DIR)/%.o : %.cpp makefile | $(BUILD_DIR)
	$(CC) $(FLAGS_CC) -o $(@) $(<) 

$(BUILD_DIR) :
	mkdir $(@)

.phony: clean
clean :
	rm -rf $(BUILD_DIR)


-include $(wildcard $(BUILD_DIR)/*.d)
