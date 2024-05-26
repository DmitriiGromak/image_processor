#include "image.h"

#include <algorithm>
#include <fstream>
#include <iostream>

DoubleColour::DoubleColour() : r(0), g(0), b(0) {
}

DoubleColour::DoubleColour(uint8_t ir, uint8_t ig, uint8_t ib) {
    r = static_cast<double>(ir) / COLOURS_NUMBER;
    g = static_cast<double>(ig) / COLOURS_NUMBER;
    b = static_cast<double>(ib) / COLOURS_NUMBER;
}

DoubleColour::DoubleColour(double dr, double dg, double db) : r(dr), g(dg), b(db) {
}

void DoubleColour::Standardize() {
    r = std::max(0.0, std::min(r, 1.0));
    g = std::max(0.0, std::min(g, 1.0));
    b = std::max(0.0, std::min(b, 1.0));
}

DoubleColour &operator+=(DoubleColour &lhs, const DoubleColour &rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    return lhs;
}

DoubleColour operator*(const DoubleColour &lhs, const double value) {
    DoubleColour res = lhs;
    res.r *= value;
    res.g *= value;
    res.b *= value;
    return res;
}

IntColour::IntColour() : r(0), g(0), b(0) {
}

IntColour::IntColour(double dr, double dg, double db) {
    r = static_cast<int32_t>(dr * COLOURS_NUMBER);
    g = static_cast<int32_t>(dg * COLOURS_NUMBER);
    b = static_cast<int32_t>(db * COLOURS_NUMBER);
}

void Image::UpdateSize() {
    file_header_.bf_size = sizeof(file_header_) + sizeof(bmp_info_header_) +
                           bmp_info_header_.bi_width * bmp_info_header_.bi_height * 3 * sizeof(uint8_t);
    file_header_.bf_size +=
        ((4 - (3 * bmp_info_header_.bi_width) % 4) % 4) * bmp_info_header_.bi_height * sizeof(uint8_t);
}

template <typename Struct>
void ReadStruct(std::ifstream &inp, Struct &current) {
    inp.read(reinterpret_cast<char *>(&current), sizeof(Struct));
}

template <typename Struct>
void WriteStruct(std::ofstream &of, const Struct &current) {
    of.write(reinterpret_cast<const char *>(&current), sizeof(Struct));
}

int32_t Image::GetWidth() const {
    return bmp_info_header_.bi_width;
}

void Image::SetWidth(int32_t new_width) {
    if (new_width >= bmp_info_header_.bi_width) {
        return;
    }
    for (auto &row : data_) {
        row.resize(new_width);
    }
    bmp_info_header_.bi_width = new_width;
    UpdateSize();
}

int32_t Image::GetHeight() const {
    return bmp_info_header_.bi_height;
}

void Image::SetHeight(int32_t new_height) {
    if (new_height >= bmp_info_header_.bi_height) {
        return;
    }
    data_.resize(new_height);
    bmp_info_header_.bi_height = new_height;
    UpdateSize();
}

DoubleColour Image::GetColour(int32_t i, int32_t j) const {
    return data_[i][j];
}

void Image::SetColour(int32_t i, int32_t j, DoubleColour new_colour) {
    data_[i][j] = new_colour;
}

std::vector<std::vector<DoubleColour>> Image::GetData() const {
    return data_;
}

void Image::Read(const char *file_name) {
    std::ifstream inp{file_name, std::ios_base::binary};
    if (!inp) {
        throw ReadImageException("unable to open the input image file\n");
    }
    ReadStruct(inp, file_header_);
    if (file_header_.bf_type != BMP_FILE_TYPE) {
        throw ReadImageException("unknown file format\n");
    }
    ReadStruct(inp, bmp_info_header_);
    if (bmp_info_header_.bi_size != BMPINFOHEADER_SIZE) {
        throw ReadImageException("unknown DIB header\n");
    }
    if (bmp_info_header_.bi_width < 0) {
        throw ReadImageException("invalid bmp file (width < 0)\n");
    }
    if (bmp_info_header_.bi_planes != 1) {
        throw ReadImageException("invalid bmp file (colour planes != 1)\n");
    }
    if (bmp_info_header_.bi_bit_count != BITS_PER_PIXEL) {
        throw ReadImageException("only works with 24 bits per pixel images\n");
    }
    if (bmp_info_header_.bi_compression != 0) {
        throw ReadImageException("only works with not compressed images\n");
    }
    inp.seekg(file_header_.offset_data, inp.beg);
    bool reversed = false;
    if (bmp_info_header_.bi_height < 0) {
        bmp_info_header_.bi_height = -bmp_info_header_.bi_height;
        reversed = true;
    }
    data_.resize(bmp_info_header_.bi_height, std::vector<DoubleColour>(bmp_info_header_.bi_width));
    for (int32_t i = bmp_info_header_.bi_height - 1; i >= 0; --i) {
        for (int32_t j = 0; j < bmp_info_header_.bi_width; ++j) {
            IntColour current;
            ReadStruct(inp, current);
            data_[i][j] = DoubleColour(current.b, current.g, current.r);
        }
        inp.ignore(static_cast<std::streamsize>((4 - (bmp_info_header_.bi_width * 3) % 4) % 4 * sizeof(uint8_t)));
    }
    if (reversed) {
        std::reverse(data_.begin(), data_.end());
    }
    uint32_t old_size = file_header_.bf_size;
    UpdateSize();
    if (old_size != file_header_.bf_size) {
        throw ReadImageException("there is extra data in the file (probably colour table)\n");
    }
}

void Image::Write(const char *file_name) const {
    std::ofstream of{file_name, std::ios_base::binary};
    if (!of) {
        throw WriteImageException("unable to open the output image file\n");
    }
    WriteStruct(of, file_header_);
    WriteStruct(of, bmp_info_header_);
    for (int32_t i = bmp_info_header_.bi_height - 1; i >= 0; --i) {
        for (int32_t j = 0; j < bmp_info_header_.bi_width; ++j) {
            IntColour current(data_[i][j].b, data_[i][j].g, data_[i][j].r);
            WriteStruct(of, current);
        }
        for (int j = 0; j < (4 - (bmp_info_header_.bi_width * 3) % 4) % 4; ++j) {
            uint8_t padding = 0;
            WriteStruct(of, padding);
        }
    }
}
