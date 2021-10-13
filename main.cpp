// fractal_images.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include <math.h>
#include "FractalCreator.h"
#include "RGB.h"


using namespace std;
using namespace caveofprogramming;

int main()
{   
    int width = 800;
    int height = 600;

    RGB rgb1(4, 5, 6);
    
    FractalCreator fractal(width, height);
    fractal.addRange(0.0, RGB(0, 0, 0));
    fractal.addRange(0.3, RGB(255, 0, 0));
    fractal.addRange(0.5, RGB(255, 255, 0));
    fractal.addRange(1.0, RGB(255, 255, 255));

    cout << fractal.getRange(400) << endl;
    // add more zoom (optional)
    //fractal.addZoom(Zoom(232, 69, 0.1));

    fractal.run("test.bmp");
    cout << "finished";
}

