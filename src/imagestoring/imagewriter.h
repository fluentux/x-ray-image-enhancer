#ifndef IMAGESTORING_IMAGEWRITER_H
#define IMAGESTORING_IMAGEWRITER_H

#include <string>
#include <memory>
#include "xrayimage.h"

class ImageWriter {
public:
    ImageWriter();

    bool write(std::string url, std::unique_ptr<XrayImageAbstract>& image);
};

#endif // IMAGESTORING_IMAGEWRITER_H
