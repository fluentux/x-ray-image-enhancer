#include "imagewriter.h"
#include "xrayimage.h"
#include <opencv2/imgcodecs.hpp>

ImageWriter::ImageWriter()
{
}

bool ImageWriter::write(std::string url, std::unique_ptr<XrayImageAbstract>& image)
{
    auto format = CV_16UC1;

    if (image->getFormat() == XrayImageFormat::Gray8) {
        format = CV_8UC1;
    }

    // Create image matrix from pixels
    cv::Mat grayImage(image->height(), image->width(), format, image->getPixelData());

    // Write file
    cv::imwrite(url, grayImage);

    return true;
}
