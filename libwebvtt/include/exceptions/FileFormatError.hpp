#ifndef FILE_FORMAT_ERROR_H
#define FILE_FORMAT_ERROR_H

#include <exception>

namespace webvtt
{
    class FileFormatError : public std::exception
    {
    public:
        FileFormatError() = default;
        virtual const char *what() const noexcept
        {
            return "File format error";
        }
    };

} // namespace webvtt

#endif //FILE_FORMAT_ERROR_H
