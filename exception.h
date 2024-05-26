#pragma once

#include <exception>
#include <string>

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const std::string &message);

protected:
    std::string message_;
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string &message);

    const char *what() const noexcept override;

private:
    const std::string base_message_ = "Parser exception with message: ";
};

class ReadImageException : public ImageProcessorException {
public:
    explicit ReadImageException(const std::string &message);

    const char *what() const noexcept override;

private:
    const std::string base_message_ = "Read image exception with message: ";
};

class FilterException : public ImageProcessorException {
public:
    explicit FilterException(const std::string &message);

    const char *what() const noexcept override;

private:
    const std::string base_message_ = "Filter exception with message: ";
};

class WriteImageException : public ImageProcessorException {
public:
    explicit WriteImageException(const std::string &message);

    const char *what() const noexcept override;

private:
    const std::string base_message_ = "Write image exception with message: ";
};
