#include <cassert>

#include "Image.h"

Image::Image(unsigned width, unsigned height, const Color& color) :
    _width(width),
    _height(height),
    _pixels(height, width, false, color) {
}

Image::Image(const Image& image) {
    _width = image._width;
    _height = image._height;
    _pixels = image._pixels;
}

Image::~Image() {
}

void Image::setPixel(unsigned x, unsigned y, Color color) {
    _pixels.setElementK(y, x, color);
}

Color Image::getPixel(unsigned x, unsigned y) const {
    return _pixels(y, x);
}

Color& Image::operator()(unsigned x, unsigned y) {
    return _pixels(y, x);
}

Color Image::operator()(unsigned x, unsigned y) const {
    return _pixels(y, x);
}

bool operator==(const Image& image1, const Image& image2) {
    return image1._pixels == image2._pixels;
}

bool operator!=(const Image& image1, const Image& image2) {
    return !(image1 == image2);
}

void Image::writePPM(std::ostream& s) const {
    s << "P6\n" << _width << " " << _height << "\n255\n";
    unsigned int i;
    double gamma = 1.0 / 2.2;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {

            _pixels(y, x) = Color(
                pow(_pixels(y, x)[0], gamma),
                pow(_pixels(y, x)[1], gamma),
                pow(_pixels(y, x)[2], gamma)
            );

            i = 256.0 * _pixels(y, x)[0];
            if (i > 255)
                i = 255;
            s.put((unsigned char) i);

            i = 256.0 * _pixels(y, x)[1];
            if (i > 255)
                i = 255;
            s.put((unsigned char) i);

            i = 256.0 * _pixels(y, x)[2];
            if (i > 255)
                i = 255;
            s.put((unsigned char) i);
        }
    }
}

void Image::readPPM(std::string file_name) {
    std::ifstream in;
    in.open(file_name.c_str());
    if (!in.is_open()) {
        std::cerr << "Can't open file \'" << file_name << "\'" << std::endl;
        exit(-1);
    }

    char ch, type;
    char red, green, blue;
    int x, y, cols, rows;
    int num;

    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;

    _width = cols;
    _height = rows;

    _pixels = Matrix<Color>(_height, _width, false, Color());

    in.get(ch);

    for (y = 0; y < _height; y++) {
        for (x = 0; x < _width; x++) {
            in.get(red);
            in.get(green);
            in.get(blue);
            _pixels(y, x) = Color(
                (float) ((unsigned char)red)/255.0,
                (float) ((unsigned char)green)/255.0,
                (float) ((unsigned char)blue)/255.0
            );
        }
    }
}

void Image::readReversePPM(std::string file_name) {
    std::ifstream in;
    in.open(file_name.c_str());
    if (!in.is_open()) {
        std::cerr << "Can't open file \'" << file_name << "\'." << std::endl;
        exit(-1);
    }

    char ch, type;
    char red, green, blue;
    int x, y, cols, rows;
    int num;

    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;

    _width = cols;
    _height = rows;

    _pixels = Matrix<Color>(_height, _width, false, Color());

    in.get(ch);

    for (y = _height-1; y >= 0; y--) {
        for (x = 0; x < _width; x++) {
            in.get(red);
            in.get(green);
            in.get(blue);
            _pixels(y, x) = Color(
                (float) ((unsigned char)red)/255.0,
                (float) ((unsigned char)green)/255.0,
                (float) ((unsigned char)blue)/255.0
            );
        }
    }
}

void Image::printImage(const char* fileName) const {
    std::ofstream myfile;
    myfile.open(fileName);
    writePPM(myfile);
    myfile.close();
}
