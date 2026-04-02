#ifndef MENU_H
#define MENU_H
#include<vector>
#include<memory>
#include<set>
#include<string>
#include<algorithm>
#include "Image.h"

///creates singleton menu to manage interface and gallery
class Menu {
    static Menu* instance;
    std::vector<Image> gallery;

    ///set of valid filters, others are thrown with OptionException()
    const std::set<std::string> validFilters={"BlackAndWhite","OrangeAndTeal","Retro","GoldenHour","Pastels","MoodyBlues",
    "Vintage","Cinematic","Summer","Spring","Winter","Autumn",
    "Blur","Contrast","Grain","Resize","Crop"};

    Menu();   ///private constructor

    public:
    static Menu* getInstance() ;
    void run() ;
    void addImage();
    void editImage();
    void deleteImage();
    void saveImage();
    void showGallery();
};
#endif

