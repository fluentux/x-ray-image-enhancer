#include "imagewriter.h"
#include "imagewriterexception.h"
#include "xrayimage.h"
#include <opencv2/imgcodecs.hpp>
#include <regex>

ImageWriter::ImageWriter()
{
}

void ImageWriter::write(std::unique_ptr<XrayImageAbstract>& image, std::string url)
{
    auto imageType = CV_16UC1;

    if (image->getType() == XrayImageType::Gray8) {
        imageType = CV_8UC1;
    }

    // Create image matrix from pixels
    cv::Mat grayImage(image->height(), image->width(), imageType, image->getPixelData());

    // Write file
    bool success = false;
    if (!grayImage.empty()) {
        success = cv::imwrite(url, grayImage);
    }

    if (!success) {
        throw ImageWriterException("Failed to write image to " + url);
    }
}
