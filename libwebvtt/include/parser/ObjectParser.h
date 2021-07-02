#ifndef LIBWEBVTT_OBJECT_PARSER_H
#define LIBWEBVTT_OBJECT_PARSER_H

#include <memory>

namespace WebVTT {
    /**
     * Helper class for creating parser for specific WebVTT object
     * Object parser has one internal object in which will be set all parsed info
     *
     * @tparam Object some subtype of Block.
     */
    template<typename Object>
    class ObjectParser {
    protected:
        std::shared_ptr<Object> currentObject;

    public:
        /**
         * Set new object as parsing object
         *
         * @param newObject  new object to be set as parsing object
         * @return true if object set, otherwise false
         */
        virtual bool setNewObjectForParsing(std::shared_ptr<Object> newObject);


        /**
         * @return return parser internal object and set internal object to nullptr
         */
        virtual std::shared_ptr<Object> collectCurrentObject();

        virtual ~ObjectParser() = 0;


    };

    /**
     * This is needed because we want that every class ObjectParser<Object> be abstract
     * @tparam Object
     */
    template<typename Object>
    ObjectParser<Object>::~ObjectParser<Object>() {}

} //End of namespace

#include "templates/parser/ObjectParser.tpp"

#endif
