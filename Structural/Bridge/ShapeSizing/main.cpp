//
//  main.cpp
//  ShapeSizing
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer: Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Drawing a vector circle of radius : " << radius << std::endl;
    }
};

struct RasterRenderer: Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing circle of radius : " << radius << std::endl;
    }
};

struct Shape
{
protected:
    Renderer& renderer;
    Shape(Renderer& rendered) : renderer(renderer) {}
    
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    Circle(Renderer& renderer, float x, float y, float radius) :
    Shape{renderer}, x{x}, y{y}, radius{radius}
    {
        
    }
    
    void draw() override
    {
        renderer.render_circle(x, y, radius);
    }
    
    void resize(float factor) override
    {
        radius *= factor;
    }
    
    float x, y, radius;
    
};

int main(int argc, const char * argv[]) {
    RasterRenderer rr;
    Circle raster_circle {rr, 10, 10, 4};
    
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();
    return 0;
}
