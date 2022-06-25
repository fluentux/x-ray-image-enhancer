#include "imagereader.h"
#include "xrayimage.h"
#include <opencv2/imgcodecs.hpp>

ImageReader::ImageReader()
{
}

std::unique_ptr<XrayImageAbstract> ImageReader::read(std::string url)
{
    cv::Mat image = cv::imread(url, cv::IMREAD_GRAYSCALE);

    if (image.depth() == CV_8U) {
        std::vector<uint8_t> pixels(image.rows * image.cols * image.channels());
        pixels.assign(image.data, image.data + image.total() * image.channels());

        XrayImage<uint8_t> xRayImage(pixels, image.cols, image.rows);
        return std::make_unique<XrayImage<uint8_t>>(xRayImage);
    }

    if (image.depth() == CV_16U) {
        std::vector<uint16_t> pixels(image.rows * image.cols * image.channels());
        pixels.assign(image.data, image.data + image.total() * image.channels());

        XrayImage<uint16_t> xRayImage(pixels, image.cols, image.rows);
        return std::make_unique<XrayImage<uint16_t>>(xRayImage);
    }

    return std::unique_ptr<XrayImageAbstract>(nullptr);
}
