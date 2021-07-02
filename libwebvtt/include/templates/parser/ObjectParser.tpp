
#include "parser/ObjectParser.h"

namespace WebVTT {

    template<typename Object>
    std::shared_ptr <Object> ObjectParser<Object>::collectCurrentObject() {
        std::shared_ptr <Object> temp = currentObject;
        currentObject = nullptr;
        return temp;
    };

    template<typename Object>
    bool ObjectParser<Object>::setNewObjectForParsing(std::shared_ptr <Object> newObject) {
        if (currentObject != nullptr) return false;
        currentObject = newObject;
        return true;
    };

}