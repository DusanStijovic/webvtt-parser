#include "WebVTTParser.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream t("sample.vtt", std::ios_base::in);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    std::cout << str;
}