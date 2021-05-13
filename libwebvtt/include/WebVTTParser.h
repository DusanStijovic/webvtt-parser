#include <string>
#include <array>


namespace WebVTT{

class WebVTTParser {
   

private:
   static constexpr uint8_t NUM_BYTES = 3;
   
   void decodeToUTF8(std::string& input);
   std::array<uint8_t,NUM_BYTES > peekInputStream(std::string input);



void readUtf8UnicodeFile(const char* filename)
{
    std::ifstream wif(filename);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    wif.imbue(loc);
    string sLine;
    int nCount =1;
 
    do
    {
        getline(wif, sLine);
        cout << "\nLine line-"<<nCount<<" is:" << sLine;
        nCount++;
    }while(!wif.eof());
 
    wif.close();
}

};

}