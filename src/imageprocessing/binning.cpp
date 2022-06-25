#include "binning.h"
#include "xrayimage.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

Binning::Binning(unsigned int blockWidth, unsigned int blockHeight)
    : blockWidth_(blockWidth), blockHeight_(blockHeight)
{
}

XrayImage<uint16_t> Binning::calculate(XrayImageAbstract& sourceImage)
{
    int blockWidth = blockWidth_;
    int blockHeight = blockHeight_;

    // Create 8-bit image matrix from pixels
    cv::Mat grayImage(sourceImage.height(), sourceImage.width(), CV_8UC1, sourceImage.getPixelData());

    // Convert image to 16-bit grayscale
    grayImage.convertTo(grayImage, CV_16UC1);

    // Calculate required padding to the image to get full blocks
    int bottomPadding = 0;
    int rightPadding = 0;
    while ((grayImage.rows + bottomPadding) % blockHeight != 0) bottomPadding++;
    while ((grayImage.cols + rightPadding) % blockWidth != 0) rightPadding++;

    // Add padding to image
    cv::Mat paddedGrayImage;
    copyMakeBorder(grayImage, paddedGrayImage, 0, bottomPadding, 0, rightPadding, cv::BORDER_REPLICATE);

    int rows = paddedGrayImage.rows / blockHeight;
    int columns = paddedGrayImage.cols / blockWidth;

    // Calculate sum for each adjacent pixel in NxN block
    auto index = 0;
    std::vector<uint16_t> binnedImagePixels(rows * columns);
    for (int row = 0; row <= paddedGrayImage.rows - blockHeight; row += blockHeight) {
        for (int col = 0; col <= paddedGrayImage.cols - blockWidth; col += blockWidth) {
            cv::Rect block(col, row, blockWidth, blockHeight);
            auto sum = cv::sum(paddedGrayImage(block));
            binnedImagePixels.at(index++) = ((uint16_t)sum[0]);
        }
    }

    XrayImage<uint16_t> binnedXrayImage(binnedImagePixels, columns, rows);

    return binnedXrayImage;
}
