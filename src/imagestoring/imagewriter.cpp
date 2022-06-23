#include "imagewriter.h"
#include "xrayimage.h"
#include <opencv2/imgcodecs.hpp>

bool ImageWriter::write(std::string url, XrayImage<uint16_t> image)
{
    // Create 16-bit image matrix from pixels
    cv::Mat grayImage(image.height(), image.width(), CV_16UC1, image.pixels().data());

    // Write file
    cv::imwrite(url, grayImage);

    return true;
}
