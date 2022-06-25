#ifndef IMAGEPROCESSING_BINNING_H
#define IMAGEPROCESSING_BINNING_H

#include <cstdint>
#include <memory>
#include "xrayimage.h"

class Binning {
public:
    Binning(unsigned int blockWidth, unsigned int blockHeight);

    std::unique_ptr<XrayImage<uint16_t>> calculate(XrayImageAbstract& sourceImage);

private:
    unsigned int blockWidth_;
    unsigned int blockHeight_;
};

#endif // IMAGEPROCESSING_BINNING_H
