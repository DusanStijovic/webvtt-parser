PROGRAM = webvtt
BUILD_DIR = build
EXTENSION = o
OUTPUT_DIR = output_dir

SOURCE_CPP_LIST = \
source/main.cpp\
source/logger/Logger.cpp\
source/decoder/UTF8ToUTF32StreamDecoder.cpp\
\
\
source/elements/webvtt_objects/Cue.cpp\
source/elements/webvtt_objects/Region.cpp\
source/elements/webvtt_objects/StyleSheet.cpp\
source/elements/webvtt_objects/CueStyleSheet.cpp\
source/elements/webvtt_objects/RegionStyleSheet.cpp\
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
source/parser/cue_style_parser/states/EndStyleState.cpp\
source/parser/cue_style_parser/states/ErrorStyleState.cpp\
\
\
source/parser/cue_style_parser/selectorStates/StyleIDSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StyleClassSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StyleAttributeSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StyleTypeSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StyleEndSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/FetchSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StyleStartPseudoState.cpp\
source/parser/cue_style_parser/selectorStates/StylePseudoElementSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StylePseudoClassSelectorState.cpp\
source/parser/cue_style_parser/selectorStates/StylePseudoElementWithArgumentEndState.cpp\
source/parser/cue_style_parser/selectorStates/StylePseudoClassWithArgumentEndState.cpp\
source/parser/cue_style_parser/selectorStates/StylePseudoWithArgumentEndState.cpp\
\
\
\
\
source/parser/cue_style_parser/ruleStates/BeforeRuleStartState.cpp\
source/parser/cue_style_parser/ruleStates/StyleRulesState.cpp\
\
\
source/parser/cue_style_parser/cue_states/CueStyleStartSelectorState.cpp\
\
\
source/parser/cue_style_parser/cue_region_states/CueRegionStyleStartSelectorState.cpp\
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
source/elements/cue_nodes/NodeObject.cpp\
source/elements/cue_nodes/InternalNodeObject.cpp\
source/elements/cue_nodes/LeafNodeObject.cpp\
\
\
source/elements/cue_nodes/internal_node_objects/RootObject.cpp\
source/elements/cue_nodes/internal_node_objects/VoiceObject.cpp\
source/elements/cue_nodes/internal_node_objects/BoldObject.cpp\
source/elements/cue_nodes/internal_node_objects/ClassObject.cpp\
source/elements/cue_nodes/internal_node_objects/ItalicObject.cpp\
source/elements/cue_nodes/internal_node_objects/LanguageObject.cpp\
source/elements/cue_nodes/internal_node_objects/UnderlineObject.cpp\
source/elements/cue_nodes/internal_node_objects/RubyObject.cpp\
source/elements/cue_nodes/internal_node_objects/RubyTextObject.cpp\
\
\
source/elements/cue_nodes/leaf_node_objects/TextObject.cpp\
source/elements/cue_nodes/leaf_node_Objects/TimeStampObject.cpp\
\
\
source/elements/style_selectors/StyleSelector.cpp\
source/elements/style_selectors/ClassSelector.cpp\
source/elements/style_selectors/IDSelector.cpp\
source/elements/style_selectors/TypeSelector.cpp\
source/elements/style_selectors/AttributeSelector.cpp\
source/elements/style_selectors/MatchAllSelector.cpp\
source/elements/style_selectors/PseudoClassSelector.cpp\
source/elements/style_selectors/PseudoElementSelector.cpp\
source/elements/style_selectors/CompoundSelector.cpp\
\
\
source/parser/html_references_constants/NumberReferenceMapDefinition.cpp\
source/parser/html_references_constants/NamedReferenceMapDefinition.cpp\
source/parser/html_references_constants/UnallowedHTMLCharacterReferences.cpp\
\
\
source/elements/rules_filters/RuleFilter.cpp\
source/elements/rules_filters/ArgumentRuleFilter.cpp\
source/elements/rules_filters/NoArgumentRuleFilter.cpp\
source/elements/rules_filters/TimeStampRuleFilter.cpp\
\
\
source/elements/visitors/ICueTreeVisitor.cpp


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


CXX = g++ -c
LD = g++ 

SHARED = 0

CXXFLAGS = -MD -MP
CXXFLAGS += -g --std=c++17
CXXFLAGS += -Wall -Wextra 
CXXFLAGS += $(INCLUDE_CPP_LIST)
ifeq ($(SHARED), 1)
	CXXFLAGS += -fPIC
endif

FLAGS_LD =

ifeq ($(SHARED), 1)
	FLAGS_LD += -shared -fPIC -pie
endif


ifeq ($(SHARED), 1)
	EXTENSION = so
	PROGRAM = libwebvtt
endif

.phony: all
all :  $(OUTPUT_DIR)/$(PROGRAM).$(EXTENSION) $(OUTPUT_DIR)


$(OUTPUT_DIR)/$(PROGRAM).$(EXTENSION) : $(OBJECTS_LIST) makefile |  $(OUTPUT_DIR)
	$(LD) $(FLAGS_LD) -o $(@) $(OBJECTS_LIST) $(LIB_CPP_LIST)


$(BUILD_DIR)/%.o : %.cpp makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(@) $(<) 

$(BUILD_DIR) :
	mkdir $(@)

$(OUTPUT_DIR) :
	mkdir $(@)

.phony: clean
clean :
	rm -rf $(BUILD_DIR)
	rm -rf $(OUTPUT_DIR)



-include $(wildcard $(BUILD_DIR)/*.d)
