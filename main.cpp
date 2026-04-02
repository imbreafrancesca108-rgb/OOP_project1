#include <iostream>
#include <vector>
#include "Image.h"
#include "Exceptions.h"
#include "Menu.h"
#include "Presets.h"

int main() {
    Menu::getInstance()->run();

    return 0;
}
