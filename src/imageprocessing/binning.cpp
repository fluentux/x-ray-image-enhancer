#include "binning.h"
#include "xrayimage.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

Binning::Binning(unsigned int blockWidth, unsigned int blockHeight)
    : blockWidth_(blockWidth), blockHeight_(blockHeight)
{
}

// Binning algorithm. Image is divided into blocks of NxN pixels and
// average value of the each pixel block is calculated.
// A new image is created from the average pixel values.
// For calculation, image borders are padded with replicated pixels when necessary.
// Either 8-bit or 16-bit image can be given as input.
std::unique_ptr<XrayImageAbstract> Binning::execute(XrayImageAbstract& sourceImage)
{
    int blockWidth = blockWidth_;
    int blockHeight = blockHeight_;

    auto sourceImageType = sourceImage.getType() == XrayImageType::Gray8 ? CV_8UC1 : CV_16UC1;

    // Create image matrix from pixels
    cv::Mat grayImage(sourceImage.height(), sourceImage.width(),
                      sourceImageType, sourceImage.getPixelData());

    // Convert 8-bit grayscale image to 16-bit
    // Scale pixel values from [0,255] to range [0,65535]
    if (sourceImageType == CV_8UC1) {
        grayImage.convertTo(grayImage, CV_16UC1, 257);
    }

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
            auto mean = cv::mean(paddedGrayImage(block));
            auto pixelValue = static_cast<uint16_t>(round(mean[0]));
            binnedImagePixels.at(index++) = pixelValue;
        }
    }

    XrayImage<uint16_t> binnedXrayImage(binnedImagePixels, columns, rows);

    return std::make_unique<XrayImage<uint16_t>>(binnedXrayImage);
}
