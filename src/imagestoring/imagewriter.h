#ifndef IMAGESTORING_IMAGEWRITER_H
#define IMAGESTORING_IMAGEWRITER_H

#include <string>
#include <memory>
#include "xrayimage.h"

// File writer for the X-ray images.
// Image is written with bit depth of the given image.
class ImageWriter {
public:
    ImageWriter();

    void write(std::unique_ptr<XrayImageAbstract>& image, std::string url);
};

#endif // IMAGESTORING_IMAGEWRITER_H
