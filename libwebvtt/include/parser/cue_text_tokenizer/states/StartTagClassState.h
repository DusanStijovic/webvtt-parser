#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{

    class StartTagClassState : public CueTextTokenizerState
    {
    public:
        StartTagClassState() = default;
        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) override;
    };

}