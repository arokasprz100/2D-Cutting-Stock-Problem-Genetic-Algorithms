#pragma once

class Sheet 
{
public:

    static constexpr int width = 2800;
    static constexpr int height = 2070;

    static constexpr int area() {
        return width * height;
    }
};