#ifndef WEB_VTT_PARSER_H
#define WEB_VTT_PARSER_H

#include "SyncBuffer.h"
#include <string>
#include <array>
#include <list>
#include <memory.h>
#include <Logger.h>

namespace WebVTT
{
   using namespace CPlusPlusLogging;

   class WebVTTParser
   {

   public:
      WebVTTParser(std::shared_ptr<SyncBuffer<std::string, u_int8_t>> inputBuffer);
      void parserRun();
      enum SPECIAL_CHARACTER
      {
         NULL_C = 0x0000,
         REPLACEMENT_C = 0xFFFD,
         CR_C = 0x000D,
         LF_C = 0x000A,
         SPACE_C = 0x0020,
         TAB_C = 0x0009,
         HYPEN_MINUS = 0x002D,
         HYPEN_GREATHER = 0x003E
      };

   private:
      constexpr static int DEFAULT_READ_NUMBER = 1;
      bool lastReadCR = false;
      std::shared_ptr<SyncBuffer<std::string, uint8_t>> inputBuffer;
      std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> decodedBuffer;

      Logger parserLogger{"parserLog.txt"};

      std::u32string decodeReadBytes(std::string &readBytes);
      void cleanDecodedBytes(std::u32string &input);

      void decodeInputStream();

      std::u32string collectWebVTTBlock(bool inHeader);

      bool checkIfStringContainsArrow(std::u32string input);
   };
}

#endif