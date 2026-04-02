#include "Image.h"
#include "Presets.h"
#include "Menu.h"
#include "Exceptions.h"
#include "ColorFilters.h"
#include "DetailFilters.h"
#include "SizeFilters.h"
#include<iostream>

///initialize static instance to null pointer
Menu* Menu::instance = nullptr;

///returns the single instance of Menu or it creates it if it doesn"t exist
Menu* Menu::getInstance() {
    if (!instance) instance = new Menu();
        return instance;
}

///private constructor
Menu::Menu() {}

///displays the menu and responds to user input
void Menu::run(){
    int option=-1;
    while(option!=6)
        {
            std::cout<<"-----PhotoEditor-----\n--Choose your option:--\n";
            std::cout<<"\n";
            std::cout<<"1. Add image to gallery.\n";
            std::cout<<"2. Edit image .\n";
            std::cout<<"3. Delete image from gallery.\n";
            std::cout<<"4. Save image to gallery.\n";
            std::cout<<"5. Exhibit gallery.\n";
            std::cout<<"6. Exit menu.\n";
            std::cout<<"\n";
            std::cout<<"Option: ";

            ///deals with an invalid input
            if(!(std::cin>>option))
            {std::cout<<"Enter a valid option!\n";
            std::cin.clear();
            std::cin.ignore(100,'\n');
            option=-1;
            }
            switch(option){
            case 1: addImage(); break;
            case 2:editImage(); break;
            case 3:deleteImage();break;
            case 4:saveImage();break;
            case 5:showGallery(); break;
            case 6: std::cout<<"Total images edited: "<<Image::getEditedImages()<< "\n";
                std::cout<<"Exiting menu...\n";
                break;
            default: std::cout<<"Invalid Option.\n"; break;
            }
    }
    }

///loads image from file and adds it to gallery
void Menu::addImage(){
    std::string path;
    std::cout<<"Choose path: ";
    std::cin.ignore();
    std::getline(std::cin, path);

    Image img;

    try{
    if(!img.load(path))
       throw OpenPath(path);
    else
        gallery.push_back(img);
       std::cout<<"The image was added to the gallery!\n";
    }
    catch (const OpenPath& e){
    std::cerr<<"Error: "<<e.what()<<"\n";
    }
    }

///applies selected filters to image chosen by the user
void Menu::editImage(){
    if(gallery.empty()){
        std::cout<<"Gallery is empty. Load a picture.\n";
        return ;
    }

    ///display the gallery and get user input
    showGallery();
    int index;
    std::cout<<"Choose index: ";
    std::cin>>index;

    if(index<0||index>=(int)gallery.size())
    {
        std::cout<<"Invalid index\n";
        return ;
    }

    ///copy the image to be edited
    Image imgEdited=gallery[index];

    ///get filter from user
    std::string filter;
    std::cout<<"Choose your filter :";
    std::cin>>filter;

    try{///check if the filter exists in the pre-made list
        if(validFilters.find(filter)==validFilters.end()){
            throw OptionException(filter);} ///invalid filter

            std::cout<<"Applying: "<<filter<<"...\n";

            if(filter=="Resize")
            {double percentage;
                std::cout<<"Resize percentage: ";
                std::cin>>percentage;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');}
                if(percentage<=0)
                    throw ResizeException(); ///throws exception if the percentage makes the dimensions negative or zero
                Resize r(percentage);
                r.applySettings(imgEdited);
            }
            else if(filter=="Crop")
                {int nw,nh;
                std::cout<<"New dimensions: ";
                std::cin>>nw>>nh;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');}
                if(nw<=0||nh<=0)
                throw CropException(); ///throws exception if the new dimenions are larger than the previous ones
                Crop c(nw,nh);
                c.applySettings(imgEdited);
            }
            else if(filter=="Contrast")
                {double a;
                std::cout<<"Contrast amount: ";
                std::cin>>a;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');}
                if(a<=0||a>20)
                throw AmountException();///invalid amounts
                Contrast cr(a);
                cr.applySettings(imgEdited);
            }
            else if(filter=="Grain")
                {double a;
                std::cout<<"Grain amount: ";
                std::cin>>a;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');}
                if(a<=0||a>1)
                throw AmountException();
                Grain g(a);
                g.applySettings(imgEdited);
            }
            else if(filter=="Blur")
                {double a;
                std::cout<<"Blur amount: ";
                std::cin>>a;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');}
                if(a<=0||a>20)
                throw AmountException();
                Blur b(a);
                b.applySettings(imgEdited);
            }
            else if(filter=="GoldenHour")
                {
                GoldenHour gh;
                gh.applySettings(imgEdited);
            }
            else if(filter=="OrangeAndTeal")
                {
                OrangeAndTeal ot;
                ot.applySettings(imgEdited);
            }
            else if(filter=="Retro")
                {
                Retro rt;
                rt.applySettings(imgEdited);
            }
            else if(filter=="MoodyBlues")
                {
                MoodyBlues mb;
                mb.applySettings(imgEdited);
            }
            else if(filter=="Pastels")
                {
                Pastels ps;
                ps.applySettings(imgEdited);
            }
            else if(filter=="BlackAndWhite")
                {
                BlackAndWhite bw;
                bw.applySettings(imgEdited);
            }
            else if(filter=="Vintage")
                {
                Vintage vt;
                vt.applySettings(imgEdited);
            }
            else if(filter=="Cinematic")
                {
                Cinematic ct;
                ct.applySettings(imgEdited);
            }
            else if(filter=="Summer")
                {
                Summer sm;
                sm.applySettings(imgEdited);
            }
            else if(filter=="Spring")
                {
                Spring sp;
                sp.applySettings(imgEdited);
            }
            else if(filter=="Winter")
                {
                Winter wt;
                wt.applySettings(imgEdited);
            }
            else if (filter=="Autumn")
                {
                Autumn au;
                au.applySettings(imgEdited);
            }

            ///replace originals with the edited version
            gallery[index]=imgEdited;
            std::cout<<"The image was edited!\n";
    }

    catch(const std::exception& e){
        std::cerr<<"Error: "<<e.what()<<"\n";
    }
    }

///removes images from gallery with the index indicated by the user
void Menu::deleteImage(){
    if(gallery.empty())
        {
            std::cout<<"There's nothing to delete!\n";
            return ;
        }

    showGallery();
    int index;
    std::cout<<"Choose index: ";
    std::cin>>index;

    if(index<0||index>=(int)gallery.size())
    {
        std::cout<<"Invalid index\n";
        return ;
    }
    else
    {
        gallery.erase(gallery.begin()+index);
        std::cout<<"Image "<<index<<" removed from gallery. \n";

    }

}

///saves images from the gallery to disk
void Menu::saveImage(){
    if(gallery.empty())
    {
        std::cout<<"There's nothing to edit. Add an image first!\n";
        return ;
    }

    showGallery();
    int index;
    std::cout<<"Choose index: ";
    std::cin>>index;

    if(index<0||index>=(int)gallery.size())
    {
        std::cout<<"Invalid index\n";
        return ;
    }

    std::string path;
    std::cout<<"Choose path: ";
    std::cin>>path;

    try{
        gallery[index].saveImage(path);
    }
    catch(const SavePath& e)
    {
        std::cerr<<"Error: "<<e.what()<<"\n";
    }
}

///displays images with indexes
void Menu::showGallery()
{
    if(gallery.empty())
    {
        std::cout<<"There's nothing to show!\n";
        return ;
    }

    std::cout<<"---- PhotoGallery -----\n";
    std::cout<<"\n";
    for(size_t i=0;i<gallery.size();++i)
    {
        std::cout<<"Image "<<i<<" "<<gallery[i].getFilename()<<std::endl;
    }

    std::cout<<"\n";
}

