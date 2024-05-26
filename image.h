#pragma once

#include <cstdint>
#include <vector>

#include "exception.h"

#pragma pack(push, 1)

const int16_t BMP_FILE_TYPE = 0x4D42;
const int16_t BITS_PER_PIXEL = 24;
const int32_t BMPINFOHEADER_SIZE = 40;
const int32_t COLOURS_NUMBER = 255;

struct FileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t offset_data;
};

struct ImageHeader {
    int32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    int16_t bi_planes;
    int16_t bi_bit_count;
    int32_t bi_compression;
    int32_t bi_size_image;
    int32_t bi_x_pixels_per_meter;
    int32_t bi_y_pixels_per_meter;
    int32_t bi_clr_used;
    int32_t bi_clr_important;
};

struct DoubleColour {
    double r;
    double g;
    double b;

    DoubleColour();

    DoubleColour(uint8_t ir, uint8_t ig, uint8_t ib);

    DoubleColour(double dr, double dg, double db);

    void Standardize();
};

struct IntColour {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    IntColour();

    explicit IntColour(double dr, double dg, double db);
};

DoubleColour &operator+=(DoubleColour &lhs, const DoubleColour &rhs);

DoubleColour operator*(const DoubleColour &lhs, const double value);

#pragma pack(pop)

class Image {
public:
    void Read(const char *file_name);

    void Write(const char *file_name) const;

    void UpdateSize();

    int32_t GetWidth() const;

    void SetWidth(int32_t new_width);

    int32_t GetHeight() const;

    void SetHeight(int32_t new_height);

    DoubleColour GetColour(int32_t i, int32_t j) const;

    void SetColour(int32_t i, int32_t j, DoubleColour new_colour);

    std::vector<std::vector<DoubleColour>> GetData() const;

private:
    FileHeader file_header_;
    ImageHeader bmp_info_header_;
    std::vector<std::vector<DoubleColour>> data_;
};
