#ifndef IMAGING_XRAYIMAGE_H
#define IMAGING_XRAYIMAGE_H

#include <vector>
#include <cstdint>

enum class XrayImageFormat {
    Gray8,
    Gray16
};

class XrayImageAbstract {
public:
    virtual XrayImageFormat getFormat() = 0;
    virtual void* getPixelData() = 0;
    virtual int width() = 0;
    virtual int height() = 0;
    virtual ~XrayImageAbstract() {};
};

template <typename GrayPixel>
class XrayImage : public XrayImageAbstract {
public:
    XrayImage<GrayPixel>(std::vector<GrayPixel> pixels, int width, int height)
        : pixels_(pixels), w_(width), h_(height)
    {
    }

    XrayImageFormat getFormat() {
        return sizeof(GrayPixel) == sizeof(std::uint8_t) ?
                    XrayImageFormat::Gray8 : XrayImageFormat::Gray16;
    }

    void* getPixelData() {
        return (GrayPixel*) pixels_.data();
    }

    std::vector<GrayPixel> pixels() { return pixels_; }
    int width() { return w_; }
    int height() { return h_; }

private:
    std::vector<GrayPixel> pixels_;
    int w_;
    int h_;
};

#endif // IMAGING_XRAYIMAGE_H