//
// Created by Dušan on 6/15/2021.
//

#ifndef LIBWEBVTT_OBJECT_PARSER_H
#define LIBWEBVTT_OBJECT_PARSER_H

#include <memory>

template<typename Object>
class ObjectParser {
protected:
    std::shared_ptr<Object> currentObject;

public:
    virtual bool setNewObjectForParsing(std::shared_ptr<Object> newObject) {
        if (currentObject != nullptr) return false;
        currentObject = newObject;
        return true;
    };


    virtual std::shared_ptr<Object> collectCurrentObject() {
        std::shared_ptr<Object> temp = currentObject;
        currentObject = nullptr;
        return temp;
    };

    virtual ~ObjectParser() = 0;


};

template<typename Object>
ObjectParser<Object>::~ObjectParser<Object>() {}


#endif //LIBWEBVTT_OBJECT_PARSER_H
