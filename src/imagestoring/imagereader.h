#ifndef IMAGESTORING_IMAGEREADER_H
#define IMAGESTORING_IMAGEREADER_H

#include <string>
#include <memory>
#include "xrayimage.h"

// File reader for the X-ray images. Different bit depth images are
// recognized and read as either 8-bit or 16-bit images.
class ImageReader {
public:
    ImageReader();

    std::unique_ptr<XrayImageAbstract> read(std::string url);
};

#endif // IMAGESTORING_IMAGEREADER_H
