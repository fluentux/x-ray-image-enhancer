#ifndef IMAGEPROCESSING_BINNING_H
#define IMAGEPROCESSING_BINNING_H

#include <cstdint>
#include "xrayimage.h"

class Binning {
public:
    Binning(unsigned int blockWidth, unsigned int blockHeight);

    XrayImage<uint16_t> calculate(XrayImage<uint8_t> sourceImage);

private:
    unsigned int blockWidth_;
    unsigned int blockHeight_;
};

#endif // IMAGEPROCESSING_BINNING_H
