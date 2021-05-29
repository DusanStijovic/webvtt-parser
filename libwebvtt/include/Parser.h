#ifndef WEB_VTT_PARSER_H
#define WEB_VTT_PARSER_H

#include "SyncBuffer.h"
#include <Logger.h>
#include <string>
#include <array>
#include <list>
#include <memory.h>
#include <thread>

namespace WebVTT
{
   using namespace CPlusPlusLogging;

   class Parser
   {

   public:
      Parser(std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> inputStream);
      bool startParsing();
      ~Parser();
      
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
      bool parsingStarted = false;

      std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> inputStream;
      std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> preprocessedStream;

      std::unique_ptr<std::thread> preProcsessingThread;
      std::unique_ptr<std::thread> parsingThread;

      Logger parserLogger{"parserLog.txt"};

      //Preprocessing
      void cleanDecodedData(std::u32string &input);
      void preProcessDecodedStreamLoop();

      //Parsing
      void parsingLoop();
      std::u32string collectWebVTTBlock(bool inHeader);
      bool checkIfStringContainsArrow(std::u32string input);
   };
}

#endif