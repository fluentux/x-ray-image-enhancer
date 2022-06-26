#ifndef IMAGEPROCESSING_IMAGEENHANCEMENT_H
#define IMAGEPROCESSING_IMAGEENHANCEMENT_H

#include <memory>
#include "xrayimage.h"

class ImageEnhancement {
public:
    virtual std::unique_ptr<XrayImageAbstract> execute(XrayImageAbstract& sourceImage) = 0;
};

#endif // IMAGEPROCESSING_ENHANCEMENT_H
