#ifndef HEX_CONVERTER_H
#define HEX_CONVERTER_H

#include<string>

struct RGB
{
    int r;
    int g;
    int b;
};

class hexConverter
{
    public:
        static RGB HexToRgb(const std::string &hex);
};



#endif