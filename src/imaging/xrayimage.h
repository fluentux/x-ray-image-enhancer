#ifndef IMAGING_XRAYIMAGE_H
#define IMAGING_XRAYIMAGE_H

#include <vector>
#include <cstdint>

// Types for different bit depth X-ray images.
enum class XrayImageType {
    Gray8,
    Gray16
};

// Abstract class for X-ray images.
// Implementations can have different bit depth for the images.
class XrayImageAbstract {
public:
    virtual const XrayImageType getType() = 0;
    virtual void* getPixelData() = 0;
    virtual const unsigned int width() = 0;
    virtual const unsigned int height() = 0;
    virtual ~XrayImageAbstract() {};
};

// Template class for 8-bit or 16-bit X-ray images.
template <typename GrayPixel>
class XrayImage : public XrayImageAbstract {
public:
    XrayImage<GrayPixel>(std::vector<GrayPixel> pixels, int width, int height)
        : pixels_(pixels), w_(width), h_(height)
    {
    }

    XrayImage<GrayPixel>(unsigned char* pixelData, int width, int height)
        : pixels_(width * height), w_(width), h_(height)
    {
        pixels_.assign(pixelData, pixelData + width * height);
    }

    const XrayImageType getType() {
        return sizeof(GrayPixel) == sizeof(std::uint8_t) ?
                    XrayImageType::Gray8 : XrayImageType::Gray16;
    }

    void* getPixelData() {
        return (GrayPixel*) pixels_.data();
    }

    std::vector<GrayPixel> pixels() { return pixels_; }
    const unsigned int width() { return w_; }
    const unsigned int height() { return h_; }

private:
    std::vector<GrayPixel> pixels_;
    unsigned int w_;
    unsigned int h_;
};

#endif // IMAGING_XRAYIMAGE_H
