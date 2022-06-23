#ifndef IMAGING_XRAYIMAGE_H
#define IMAGING_XRAYIMAGE_H

#include <vector>

template <typename GrayPixel>
class XrayImage {
public:
    XrayImage<GrayPixel>(std::vector<GrayPixel> pixels, int width, int height)
        : pixels_(pixels), w_(width), h_(height)
    {
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
