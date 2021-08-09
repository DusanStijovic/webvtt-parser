PROGRAM = program
BUILD_DIR = build

SOURCE_CPP_LIST = \
source/main.cpp\
source/logger/Logger.cpp\
source/decoder/UTF8ToUTF32StreamDecoder.cpp\
\
\
source/elements/Cue.cpp\
source/elements/Region.cpp\
source/elements/StyleSheet.cpp\
\
\
source/parser/Parser.cpp\
source/parser/CueParser.cpp\
source/parser/StyleSheetParser.cpp\
source/parser/RegionParser.cpp\
source/parser/ParserUtil.cpp\
\
\
source/parser/cue_style_parser/states/StyleState.cpp\
source/parser/cue_style_parser/states/StyleStartState.cpp\
source/parser/cue_style_parser/states/StyleIDSelectorState.cpp\
source/parser/cue_style_parser/states/StyleClassSelectorState.cpp\
source/parser/cue_style_parser/states/StyleTypeSelectorState.cpp\
source/parser/cue_style_parser/states/StylePseudoClassSelectorState.cpp\
source/parser/cue_style_parser/states/StyleEndSelectorState.cpp\
source/parser/cue_style_parser/states/StyleRulesState.cpp\
source/parser/cue_style_parser/states/ErrorStyleState.cpp\
\
\
source/parser/cue_style_parser/cue_states/CueStyleStartSelectorState.cpp\
source/parser/cue_style_parser/cue_states/CueStyleIDSelectorState.cpp\
\
\
source/parser/cue_style_parser/cue_region_states/CueRegionStyleStartSelectorState.cpp\
source/parser/cue_style_parser/cue_region_states/CueRegionStyleIDSelectorState.cpp\
\
\
source/parser/cue_text_tokenizer/CueTextTokenizer.cpp\
source/parser/cue_text_tokenizer/states/CueTextTokenizerState.cpp\
source/parser/cue_text_tokenizer/states/DataState.cpp\
source/parser/cue_text_tokenizer/states/StartTagState.cpp\
source/parser/cue_text_tokenizer/states/StartTagClassState.cpp\
source/parser/cue_text_tokenizer/states/StartTagAnnotationState.cpp\
source/parser/cue_text_tokenizer/states/EndTagState.cpp\
source/parser/cue_text_tokenizer/states/TagState.cpp\
source/parser/cue_text_tokenizer/states/TimeStampTagState.cpp\
source/parser/cue_text_tokenizer/tokens/Token.cpp\
source/parser/cue_text_tokenizer/tokens/BasicToken.cpp\
source/parser/cue_text_tokenizer/tokens/StartTagToken.cpp\
source/parser/cue_text_tokenizer/tokens/EndTagToken.cpp\
source/parser/cue_text_tokenizer/tokens/TimeStampTagToken.cpp\
\
\
source/elements/cue_node_objects/NodeObject.cpp\
source/elements/cue_node_objects/InternalNodeObject.cpp\
source/elements/cue_node_objects/LeafNodeObject.cpp\
\
\
source/elements/cue_node_objects/internal_node_objects/RootObject.cpp\
source/elements/cue_node_objects/internal_node_objects/VoiceObject.cpp\
source/elements/cue_node_objects/internal_node_objects/BoldObject.cpp\
source/elements/cue_node_objects/internal_node_objects/ClassObject.cpp\
source/elements/cue_node_objects/internal_node_objects/ItalicObject.cpp\
source/elements/cue_node_objects/internal_node_objects/LanguageObject.cpp\
source/elements/cue_node_objects/internal_node_objects/UnderlineObject.cpp\
source/elements/cue_node_objects/internal_node_objects/RubyObject.cpp\
source/elements/cue_node_objects/internal_node_objects/RubyTextObject.cpp\
\
\
source/elements/cue_node_objects/leaf_node_objects/TextObject.cpp\
source/elements/cue_node_objects/leaf_node_Objects/TimeStampObject.cpp\
\
\
source/elements/style_objects/StyleSelector.cpp\
source/elements/style_objects/StyleSelectorWithArgument.cpp\
source/elements/style_objects/ClassSelector.cpp\
source/elements/style_objects/IDSelector.cpp\
source/elements/style_objects/TypeSelector.cpp\
source/elements/style_objects/AttributeSelector.cpp\
source/elements/style_objects/MatchAllSelector.cpp\
source/elements/style_objects/TimeStampSelector.cpp\
\
\
source/parser/NumberReferenceMapDefinition.cpp\
source/parser/NamedReferenceMapDefinition.cpp\
source/parser/UnallowedHTMLCharacterReferences.cpp\

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
