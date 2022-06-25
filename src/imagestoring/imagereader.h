#ifndef IMAGESTORING_IMAGEREADER_H
#define IMAGESTORING_IMAGEREADER_H

#include <string>
#include <memory>
#include "xrayimage.h"

class ImageReader {
public:
    ImageReader();

    std::unique_ptr<XrayImageAbstract> read(std::string url);
};

#endif // IMAGESTORING_IMAGEREADER_H
