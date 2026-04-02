#ifndef IMAGE_H
#define IMAGE_H
#include<vector>
#include<string>
class Image{
    int width;
    int height;
    int rgb;       ///rgb channels
    std::vector<unsigned char> pixels;       ///raw pixel data
    static int totalEditedImages;
    std::string filename;
public:
    Image();
    Image(int w, int h, int c, unsigned char* p);
    ~Image();
    Image(const Image& other);
    Image& operator=(const Image& other);
    int getWidth() const ;
    int getHeight() const ;
    int getRGBChannels() const ;
    std::vector<unsigned char>& getPixels();
    int isValid() const;
    static int getEditedImages();
    void saveImage(const std::string& path) const;
    void setWidth(int w);
    void setHeight(int h);
    bool load(const std::string& path);
    std::string getFilename() const ;
};

#endif
