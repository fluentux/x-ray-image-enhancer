#ifndef IMAGEPROCESSING_BINNING_H
#define IMAGEPROCESSING_BINNING_H

#include <cstdint>
#include <memory>
#include "imageenhancement.h"
#include "xrayimage.h"

// Binning image processing method.
// Calculates combined pixel values for specific size of image blocks.
class Binning : public ImageEnhancement {
public:
    Binning(unsigned int blockWidth, unsigned int blockHeight);

    std::unique_ptr<XrayImageAbstract> execute(XrayImageAbstract& sourceImage);

private:
    unsigned int blockWidth_;
    unsigned int blockHeight_;
};

#endif // IMAGEPROCESSING_BINNING_H
