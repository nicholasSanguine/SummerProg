#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

//Pass in our cout command and hold onto our input color. For current example red = i / 255.0, green = j / 255.0, blue = 0.25
void write_color(std::ostream& out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif