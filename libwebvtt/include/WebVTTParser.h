#include "SyncBuffer.h"
#include <string>
#include <array>
#include <vector>
#include <memory.h>

namespace WebVTT
{

   class WebVTTParser
   {

   public:
      WebVTTParser(std::shared_ptr<SyncBuffer> syncBuffer) : inputBuffer(syncBuffer){};
      void parserRun();

   private:
      std::vector<uint32_t> decodeUTF8ToUTF32(std::string &input);
      std::shared_ptr<SyncBuffer> inputBuffer;
   };

}