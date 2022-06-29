#ifndef IMAGESTORING_IMAGEWRITEREXCEPTION_H
#define IMAGESTORING_IMAGEWRITEREXCEPTION_H

#include <string>

class ImageWriterException {
public:
    ImageWriterException(const std::string& what) : what_(what) {}
    std::string getWhat() const { return what_; }

private:
    std::string what_;
};

#endif // IMAGESTORING_IMAGEWRITEREXCEPTION_H
