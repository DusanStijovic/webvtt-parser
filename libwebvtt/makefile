SHARED_LIB_NAME = libwebvtt
BUILD_DIR = build
EXTENSION = so
OUTPUT_DIR = output_dir
EXEC = webvtt

MAIN_CPP = source/main.cpp

SOURCE_CPP_LIST = \
source/logger/Logger.cpp\
source/decoder/UTF8ToUTF32StreamDecoder.cpp\

# WEBVTT OBJECTS
SOURCE_CPP_LIST += \
source/elements/webvtt_objects/Cue.cpp\
source/elements/webvtt_objects/Region.cpp\
source/elements/webvtt_objects/StyleSheet.cpp\
source/elements/webvtt_objects/CueStyleSheet.cpp\
source/elements/webvtt_objects/RegionStyleSheet.cpp\


# PARSERS
SOURCE_CPP_LIST += \
source/parser/Parser.cpp\
source/parser/object_parser/CueParser.cpp\
source/parser/object_parser/StyleSheetParser.cpp\
source/parser/object_parser/RegionParser.cpp\
source/parser/object_parser/ParserUtil.cpp\


# [STYLE PARSING] GENERAL STATES
SOURCE_CPP_LIST += \
source/parser/cue_style_parser/states/StyleState.cpp\
source/parser/cue_style_parser/states/StyleStartState.cpp\
source/parser/cue_style_parser/states/EndStyleState.cpp\
source/parser/cue_style_parser/states/ErrorStyleState.cpp\

# [Style Parsing] COMMENT STATES
SOURCE_CPP_LIST += \
source/parser/cue_style_parser/comment_states/StyleStartCommentState.cpp\
source/parser/cue_style_parser/comment_states/StyleCommentState.cpp\
source/parser/cue_style_parser/comment_states/StyleEndCommentState.cpp\



# [STYLE PARSING] SELECTOR STATES
SOURCE_CPP_LIST += \
source/parser/cue_style_parser/selectorStates/StyleIdSelectorState.cpp\
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
source/parser/cue_style_parser/states/StyleEscapedSequenceState.cpp\


# [STYLE PARSING] RULE STATES
SOURCE_CPP_LIST += \
source/parser/cue_style_parser/ruleStates/BeforeRuleStartState.cpp\
source/parser/cue_style_parser/ruleStates/StyleRulesState.cpp\


# [STYLE PARSING] START STYLE SELECTOR STATE
SOURCE_CPP_LIST += \
source/parser/cue_style_parser/cue_states/StyleStartSelectorState.cpp\


# [PARSING CUE TEXT] STATES
SOURCE_CPP_LIST += \
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


# [CUE TREE] GENERAL NODES
SOURCE_CPP_LIST += \
source/elements/cue_nodes/NodeObject.cpp\
source/elements/cue_nodes/InternalNodeObject.cpp\
source/elements/cue_nodes/LeafNodeObject.cpp\


# [CUE TREE] INTERNAL NODES
SOURCE_CPP_LIST += \
source/elements/cue_nodes/internal_node_objects/RootObject.cpp\
source/elements/cue_nodes/internal_node_objects/VoiceObject.cpp\
source/elements/cue_nodes/internal_node_objects/BoldObject.cpp\
source/elements/cue_nodes/internal_node_objects/ClassObject.cpp\
source/elements/cue_nodes/internal_node_objects/ItalicObject.cpp\
source/elements/cue_nodes/internal_node_objects/LanguageObject.cpp\
source/elements/cue_nodes/internal_node_objects/UnderlineObject.cpp\
source/elements/cue_nodes/internal_node_objects/RubyObject.cpp\
source/elements/cue_nodes/internal_node_objects/RubyTextObject.cpp\


# [CUE TREE] LEAF NODE
SOURCE_CPP_LIST += \
source/elements/cue_nodes/leaf_node_objects/TextObject.cpp\
source/elements/cue_nodes/leaf_node_Objects/TimeStampObject.cpp\


# STYLE SELECTORS
SOURCE_CPP_LIST += \
source/elements/style_selectors/StyleSelector.cpp\
source/elements/style_selectors/ClassSelector.cpp\
source/elements/style_selectors/IdSelector.cpp\
source/elements/style_selectors/MatchAllSelector.cpp\
source/elements/style_selectors/CompoundSelector.cpp\
source/elements/style_selectors/CombinatorSelector.cpp\


# TYPE SELECTORS
SOURCE_CPP_LIST += \
source/elements/style_selectors/type_selectors/TypeSelector.cpp\
source/elements/style_selectors/type_selectors/BoldTypeSelector.cpp\
source/elements/style_selectors/type_selectors/ClassTypeSelector.cpp\
source/elements/style_selectors/type_selectors/ItalicTypeSelector.cpp\
source/elements/style_selectors/type_selectors/LanguageTypeSelector.cpp\
source/elements/style_selectors/type_selectors/RubyTypeSelector.cpp\
source/elements/style_selectors/type_selectors/RubyTextTypeSelector.cpp\
source/elements/style_selectors/type_selectors/UnderlineTypeSelector.cpp\
source/elements/style_selectors/type_selectors/VoiceTypeSelector.cpp\



# ATTRIBUTE SELECTORS
SOURCE_CPP_LIST += \
source/elements/style_selectors/attribute_selectors/AttributeSelector.cpp\
source/elements/style_selectors/attribute_selectors/LanguageSelector.cpp\
source/elements/style_selectors/attribute_selectors/VoiceSelector.cpp\


# PSEUDO SELECTORS
SOURCE_CPP_LIST += \
source/elements/style_selectors/pseudo_class_selectors/PseudoClassWithArgument.cpp\
source/elements/style_selectors/pseudo_class_selectors/PseudoClassSelector.cpp\
source/elements/style_selectors/pseudo_element_selectors/PseudoElementSelector.cpp\
source/elements/style_selectors/pseudo_element_selectors/PseudoElementWithArgument.cpp\



# HELPERS FOR HTML NAMED AND NUMBER REFERENCE
SOURCE_CPP_LIST += \
source/parser/html_references_constants/NumberReferenceMapDefinition.cpp\
source/parser/html_references_constants/NamedReferenceMapDefinition.cpp\
source/parser/html_references_constants/UnallowedHTMLCharacterReferences.cpp\


# FILTERS FOR CSS RULES
SOURCE_CPP_LIST += \
source/elements/rules_filters/RuleFilter.cpp\
source/elements/rules_filters/ArgumentRuleFilter.cpp\
source/elements/rules_filters/NoArgumentRuleFilter.cpp\
source/elements/rules_filters/TimeStampRuleFilter.cpp\


# VISITOR INTERFACE FOR VISITING CUE TEXT TREE
SOURCE_CPP_LIST += \
source/elements/visitors/ICueTreeVisitor.cpp


INCLUDE_CPP_LIST =\
 -Iinclude\
 -Ilib/utfcpp/source\


LIB_CPP_LIST = \
-pthread


OBJECTS_LIST_FOR_SHARED = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_CPP_LIST:.cpp=.o)))

MAIN_OBJECT = $(addprefix $(BUILD_DIR)/, $(notdir $(MAIN_CPP:.cpp=.o)))



SOURCE_CPP_PATH =  $(sort $(dir $(SOURCE_CPP_LIST)))
SOURCE_CPP_PATH += $(dir $(MAIN_CPP))

vpath %.cpp  $(SOURCE_CPP_PATH)


$(info start)
$(info $(SOURCE_CPP_PATH))


CXX = g++ -c
LD = g++


CXXFLAGS = -MD -MP
CXXFLAGS += -g -std=c++20
CXXFLAGS += -Wall -Wextra
CXXFLAGS += $(INCLUDE_CPP_LIST)
CXXFLAGS += -fPIC

SHARED_LD_FLASGS += -shared -fPIC


.phony: all
all :  $(OUTPUT_DIR)/$(SHARED_LIB_NAME).$(EXTENSION)  $(OUTPUT_DIR)/$(EXEC) $(OUTPUT_DIR)


$(OUTPUT_DIR)/$(SHARED_LIB_NAME).$(EXTENSION) : $(OBJECTS_LIST_FOR_SHARED) makefile |  $(OUTPUT_DIR)
	$(LD) $(SHARED_LD_FLASGS) -o $(@) $(OBJECTS_LIST_FOR_SHARED) $(LIB_CPP_LIST)


$(OUTPUT_DIR)/$(EXEC): $(OBJECTS_LIST_FOR_SHARED) $(MAIN_OBJECT) makefile |  $(OUTPUT_DIR)
	$(LD) -o $(@) $(OBJECTS_LIST_FOR_SHARED) $(MAIN_OBJECT)  $(LIB_CPP_LIST)


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
