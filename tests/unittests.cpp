#define BOOST_TEST_MODULE UnitTests

#include "boost/test/unit_test.hpp"
#include "binning.h"

BOOST_AUTO_TEST_SUITE(binning_test_suite)
    BOOST_AUTO_TEST_CASE(binning_with_even_columns_and_rows)
    {
        Binning binning(2, 2);

        std::vector<uint8_t> pixels = {
          10, 10, 10, 10,
          10, 10, 10, 10,
          10, 10, 10, 10,
          10, 10, 10, 10
        };

        XrayImage<uint8_t> image(pixels, 4, 4);

        auto binnedImage = binning.calculate(image);

        auto actual = binnedImage.pixels();
        std::vector<uint16_t> expected = {
          40, 40,
          40, 40,
        };

        bool equal = std::equal(actual.begin(), actual.end(), expected.begin());

        BOOST_TEST(equal == true);
    }

    BOOST_AUTO_TEST_CASE(binning_with_odd_columns_and_rows)
    {
        Binning binning(2, 2);

        std::vector<uint8_t> pixels = {
          20, 20, 20,
          20, 20, 20,
          20, 20, 20,
        };

        XrayImage<uint8_t> image(pixels, 3, 3);

        auto binnedImage = binning.calculate(image);

        auto actual = binnedImage.pixels();
        std::vector<uint16_t> expected = {
          80, 80,
          80, 80,
        };

        bool equal = std::equal(actual.begin(), actual.end(), expected.begin());

        BOOST_TEST(equal == true);
    }

    BOOST_AUTO_TEST_CASE(binning_with_larger_pixel_values)
    {
        Binning binning(2, 2);

        std::vector<uint8_t> pixels = {
          10, 20, 30, 40,
          50, 60, 70, 80,
          90, 100, 110, 120,
          130, 140, 150, 160
        };

        XrayImage<uint8_t> image(pixels, 4, 4);

        auto binnedImage = binning.calculate(image);

        auto actual = binnedImage.pixels();
        std::vector<uint16_t> expected = {
          140, 220,
          460, 540,
        };

        bool equal = std::equal(actual.begin(), actual.end(), expected.begin());

        BOOST_TEST(equal == true);
    }

    BOOST_AUTO_TEST_CASE(binning_with_3x1_block)
    {
        Binning binning(3, 1);

        std::vector<uint8_t> pixels = {
          100, 200, 100, 200, 100, 200, 100,
          200, 100, 200, 100, 200, 100, 200,
          100, 200, 100, 200, 100, 200, 100,
          200, 100, 200, 100, 200, 100, 200,
          100, 200, 100, 200, 100, 200, 100,
        };

        XrayImage<uint8_t> image(pixels, 7, 5);

        auto binnedImage = binning.calculate(image);

        auto actual = binnedImage.pixels();
        std::vector<uint16_t> expected = {
          400, 500, 300,
          500, 400, 600,
          400, 500, 300,
          500, 400, 600,
          400, 500, 300,
        };

        bool equal = std::equal(actual.begin(), actual.end(), expected.begin());

        BOOST_TEST(equal == true);
    }

BOOST_AUTO_TEST_SUITE_END()


#include "xrayimage.h"

BOOST_AUTO_TEST_SUITE(xrayimage_test_suite)

    BOOST_AUTO_TEST_CASE(create_8_bit_image)
    {
        std::vector<uint8_t> pixels = { 1, 2, 3, 4 };

        XrayImage<uint8_t> image(pixels, 2, 2);

        BOOST_TEST(image.pixels().size() == 4);
    }

    BOOST_AUTO_TEST_CASE(create_16_bit_image)
    {
        std::vector<uint16_t> pixels = {
            0, 65535, 0, 100,
            0, 1000, 5, 40000
        };

        XrayImage<uint16_t> image(pixels, 4, 2);

        BOOST_TEST(image.pixels().size() == 8);
    }

    BOOST_AUTO_TEST_CASE(format_of_8_bit_x_ray_image_is_gray8)
    {
        std::vector<uint8_t> pixels = {
            255, 0, 255, 255,
            255, 0, 255, 255,
            255, 0, 255, 0
        };

        XrayImage<uint8_t> image(pixels, 4, 3);

        BOOST_CHECK(image.getFormat() == XrayImageFormat::Gray8);
    }

    BOOST_AUTO_TEST_CASE(format_of_16_bit_x_ray_image_is_gray16)
    {
        std::vector<uint16_t> pixels = {
            65535, 0, 65535,
            0, 10000, 30000,
            0, 20000, 65535
        };

        XrayImage<uint16_t> image(pixels, 3, 3);

        BOOST_CHECK(image.getFormat() == XrayImageFormat::Gray16);
    }

BOOST_AUTO_TEST_SUITE_END()