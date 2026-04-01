# PhotoEditor

## 1.Project Description
This project is a mini-version of a photo editing application , written in C++ and following OOP coding principles. It allows the user to apply various effects and features to images using an interactive and simple menu. The options include color adjustments, size modifications and detail enhancements, as well as 6 presets combining these settings. 

## 2. Class Structure

**Core classes**

### **|. Image**
- defines the object
- stores pixel data, dimensions and rgb channels
- includes load/save operations
- includes the rule of 3(copy constructor, assignment operator, destructor)
- contains static member to track the total of edited images

### **||. ImageEditor**

- defines the interface for editing
- includes pure virtual methods:
##### ->applySettings() : modify the image according to each filter
##### ->getFilterName() : returns the description of the filter

 **Derived classes**
 
### **I. ColorFilters (derived from ImageEditor)**
Includes 6 chromatic transformations :

- **BlackAndWhite**: grayscale conversion using luminance formula
- **GoldenHour**: warmth-focused look, enhancing red and reducing blue
- **Retro**: old-style look using sepia transformation formula
- **OrangeAndTeal**: cinema-inspired color grading focused on warm highlights and cool-toned shadows
- **Pastels**: soft/dreamy color pallete enhancing pinks and greens
- **Moody-blues**: dark and cool tones

### **II. DetailFilters (derived from ImageEditor)**

Includes 3 quality modifiers:

- **Contrast**: adjust contrast with formula new_pixel = amount * (pixel - 128) + 128
- **Grain**: adds a vintage/film-like grain using noise
- **Blur**: adds a soft blur using 5*5 kernel average

### **III.SizeFilters (derived from ImageEditor)**

Includes 2 sizing tools:

- **Crop**: rescales the image to new dimensions
- **Resize**: scales the image based on percentage

### **IV.Diamond Inheritance**

Includes 6 presets combining both color and detail features, using **virtual inheritance** to solve the diamond problem:

- **Vintage** : BlackAndWhite + Grain+ Blur
- **Cinematic**: OrangeAndTeal + Grain
- **Summer**: GoldenHour+ high Contrast
- **Spring**: Pastels + Blur
- **Winter** : MooddyBlues + low Contrast
- **Autumn**: Retro+ Grain + high Contrast

### **V.Exceptions classes**
Defines 6 custom exceptions derived from std::runtime_error:

- **AmountException**: invalid detail parameter values
- **OpenPath**: file could not be found
- **SavePath**: saving path could not be found
- **CropException**: invalid crop dimensions
- **ResizeException**: invalid resizing percentage
- **OptionException**: invalid/non-existing editing filters

### **VI.Menu**
Singleton menu class containing:
- **AddImage**-loads image from files to gallery (JPG format-only)
- **EditImage**-applies filters from user input
- **DeleteImage**-removes images from gallery
- **SaveImage**-exports edited images to disk
- **ShowGallery**-displays all image-indexes from the gallery
- **Exit**-closes the application

## **3.Technical Implementation**
All classes are split into .h and .cpp files.
There are 22 classes, of which **14** are corelated to the abstract one **ImageEditor**.
##### Three-level hierarchy:
##### ImageEditor (abstract)
##### ├── ColorFilters
##### │ ├── BlackAndWhite, GoldenHour, Retro, OrangeAndTeal, Pastels, MoodyBlues
##### ├── DetailFilters
##### │ ├── Grain, Blur, Contrast
##### └── SizeFilters
##### ├── Crop, Resize

**Diamond inheritance**: presets inherit form both 'ColorFilters' and 'DetailFilters' using **virtual public**.
##### Static implementation: 

- static int totalEditedImages in Image class which counts all saved images across the application
- static int getEditedImages() which returns the total count
- static Menu* instance in Menu class which implements the Singleton 

#### Encapsulation and Resource Management
##### Access Modifiers (private, protected, public):

- **private** ->Image class members (width, height, pixels) - only accessible within Image class
- **protected** -> detail filter parameters (amountGrain, amountBlur,amountContrast)-to be accessible by derived classes in case there will be more made (HighContrast for example)
- **public** ->Interface methods (applySettings, getFilterName, load, save) - accessible to all

#### Rule of Three
Implemented in `Image` class:
- **Copy constructor** - Image(const Image& other) - deep copy of pixel data
- **Assignment operator** - Image& operator=(const Image& other) - prevents self-assignment, copies all members
- **Destructor** - ~Image()- cleans up resources

#### std::vector Usage

- std::vector<unsigned char> pixels - stores raw pixel data in Image class
- std::vector<Image> gallery - stores multiple images in Menu class

Vector manages memory automatically (no manual new/delete)

### Polymorphism (Virtual Methods & Abstract Classes)

#### Abstract Class
ImageEditor is an abstract class with pure virtual methods and many virtual functions throughout the programme which allow the system to treat different filter objects (BlackAndWhite, Contrast, Blur, etc.) uniformly through the same interface while they maintain their unique behaviors. 

## **4.Workflow**
After you run the project:
- The menu gets created and the user chooses a digit between 1-6 to access an option
- According to each input a different function is allocated with different errors being checked
- After pressing option 6 the programme stops

## **5.Additional mentions**
#### External Libraries
**- stb_image.h** - Image loading (supports JPG, PNG, BMP, TGA)

**- stb_image_write.h** - Image saving (JPG, PNG, BMP, TGA)
