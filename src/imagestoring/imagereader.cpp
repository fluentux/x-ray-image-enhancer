#include "imagereader.h"
#include "xrayimage.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

ImageReader::ImageReader()
{
}

XrayImage<uint8_t> ImageReader::read(std::string url)
{
    cv::Mat image = cv::imread(url, cv::IMREAD_GRAYSCALE);

    std::vector<uint8_t> pixels(image.rows * image.cols * image.channels());
    pixels.assign(image.data, image.data + image.total() * image.channels());

    XrayImage<uint8_t> xRayImage(pixels, image.cols, image.rows);

    return xRayImage;
}
