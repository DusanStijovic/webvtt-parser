#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{

    class StartTagClassState : public CueTextTokenizerState
    {
    public:
        StartTagClassState(CueTextTokenizer &tokenizer)
            : CueTextTokenizerState(tokenizer){};
        virtual std::shared_ptr<Token> process() override;
    };

}