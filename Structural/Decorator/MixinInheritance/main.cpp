//
//  main.cpp
//  MixinInheritance
//
//  Created by Aniket Bhushan on 19/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <sstream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;
    Circle() = default;
    explicit Circle(const float radius) : radius{radius} {}
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss << "A circle of radius : " << radius;
        return ss.str();
    }
};

struct Square : Shape
{
    float side;
    
    explicit Square(const float side) : side{side}
    {
    }
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss << "A square with side = " << side;
        return ss.str();
    }
};

struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;
    
    explicit ColoredShape(Shape& shape, const std::string& color) : shape{shape}, color{color} {}
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss << shape.str() << " has the color " << color;
        return ss.str();
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;
    
    explicit TransparentShape(Shape& shape, const uint8_t transparency) : shape{shape}, transparency{transparency}
    {}
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss <<  shape.str() << " has " << static_cast<float>(transparency)/255.f*100.f << " % transparency";
        return ss.str();
    }
};


template <typename T>
struct ColoredShape2 : T
{
    std::string color;
    ColoredShape2() {};
    
    explicit ColoredShape2(const std::string& color ) : color{color} {}
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss << T::str() << " has the color " << color;
        return ss.str();
    }
};

template <typename T>
struct TransparentShape2 : T
{
    uint8_t transparency;
    
    explicit TransparentShape2(const uint8_t transparency) : transparency{transparency}
    {}
    
    std::string str() const override
    {
        std::ostringstream ss;
        ss <<  T::str() << " has " << static_cast<float>(transparency)/255.f*100.f << " % transparency";
        return ss.str();
    }
};

int main(int argc, const char * argv[]) {
    
    //    Circle circle(5);
    //    std::cout << circle.str() << std::endl;
    //
    //    ColoredShape redCircle(circle, "red");
    //    std::cout << redCircle.str() << std::endl;
    //
    //    TransparentShape halfTransparentCircle {circle, 128};
    //    std::cout << halfTransparentCircle.str() << std::endl;
    //
    //    TransparentShape halfTransparentRedCircle {redCircle, 128};
    //    std::cout << halfTransparentRedCircle.str() << std::endl;
    
    ColoredShape2<Circle> redCircle{"red"};
    redCircle.radius = 5;
    
    std::cout << redCircle.str() << std::endl;
    
    TransparentShape2<ColoredShape2<Circle>> redHalfTransparentCircle{127};
    redHalfTransparentCircle.color = "red";
    redHalfTransparentCircle.radius = 10;
    
    std::cout << redHalfTransparentCircle.str() << std::endl;
    
    return 0;
}
