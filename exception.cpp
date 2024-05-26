#include "exception.h"

ImageProcessorException::ImageProcessorException(const std::string &message) : message_(message) {
}

ParserException::ParserException(const std::string &message) : ImageProcessorException(message) {
}

const char *ParserException::what() const noexcept {
    static std::string result = base_message_ + message_;
    return result.c_str();
}

ReadImageException::ReadImageException(const std::string &message) : ImageProcessorException(message) {
}

const char *ReadImageException::what() const noexcept {
    static std::string result = base_message_ + message_;
    return result.c_str();
}

FilterException::FilterException(const std::string &message) : ImageProcessorException(message) {
}

const char *FilterException::what() const noexcept {
    static std::string result = base_message_ + message_;
    return result.c_str();
}

WriteImageException::WriteImageException(const std::string &message) : ImageProcessorException(message) {
}

const char *WriteImageException::what() const noexcept {
    static std::string result = base_message_ + message_;
    return result.c_str();
}
