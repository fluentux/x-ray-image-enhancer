#include "imagereader.h"
#include "imagereaderexception.h"
#include "xrayimage.h"
#include <opencv2/imgcodecs.hpp>

ImageReader::ImageReader()
{
}

std::unique_ptr<XrayImageAbstract> ImageReader::read(std::string url)
{
    cv::Mat image = cv::imread(url, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        throw ImageReaderException("Failed to read image");
    }

    if (image.depth() == CV_8U) {
        XrayImage<uint8_t> xRayImage(image.data, image.cols, image.rows);
        return std::make_unique<XrayImage<uint8_t>>(xRayImage);
    }

    if (image.depth() == CV_16U) {
        XrayImage<uint16_t> xRayImage(image.data, image.cols, image.rows);
        return std::make_unique<XrayImage<uint16_t>>(xRayImage);
    }

    return std::unique_ptr<XrayImageAbstract>(nullptr);
}
