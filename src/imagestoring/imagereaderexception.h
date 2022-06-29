#ifndef IMAGESTORING_IMAGEREADEREXCEPTION_H
#define IMAGESTORING_IMAGEREADEREXCEPTION_H

#include <string>

class ImageReaderException {
public:
    ImageReaderException(const std::string& what) : what_(what) {}
    std::string getWhat() const { return what_; }

private:
    std::string what_;
};

#endif // IMAGESTORING_IMAGEREADEREXCEPTION_H
