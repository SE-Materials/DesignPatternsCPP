//
//  main.cpp
//  VirtualProxy
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

struct Image
{
    virtual ~Image() = default;
    virtual void Draw() = 0;
};

struct Bitmap : Image {
    
    Bitmap(const std::string& filename)
    {
        std::cout << "Loading a file from " << filename << std::endl;
    }
    
    void Draw() override
    {
        std::cout << "Drawing Image" << std::endl;
    }
};

struct LazyBitmap : Image{
    LazyBitmap(const std::string& filename) : filename{filename}, bmp{nullptr} {}
    ~LazyBitmap()
    {
        delete bmp;
    }
    
    void Draw() override
    {
        if (bmp == nullptr)
            bmp = new Bitmap{filename};
        
        bmp->Draw();
    }
private:
    Bitmap* bmp;
    std::string filename;
};

void draw_image(Image& image)
{
    std::cout << "About to draw the image" << std::endl;
    image.Draw();
    std::cout << "Done drawing the image" << std::endl;
}

void virtual_proxy ()
{
    // Here image is loaded when constructor is called not at the time of drawing !
    Bitmap bmp{"pokemon.png"};
    draw_image(bmp);
    
    LazyBitmap lbmp{"lazyPokemon.png"};
    draw_image(lbmp);
    draw_image(lbmp);
}

int main(int argc, const char * argv[]) {
    virtual_proxy();
    return 0;
}
