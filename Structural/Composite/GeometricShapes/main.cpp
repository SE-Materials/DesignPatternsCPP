//
//  main.cpp
//  GeometricShapes
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicObject
{
    void draw() override
    {
        std::cout << "Circle" << std::endl;
    }
};

struct Group : GraphicObject
{
    std::string name;
    std::vector<GraphicObject*> objects;
    
    Group(const std::string& name) : name{name} {}
    
    void draw() override
    {
        std::cout << "Group : " << name << " contains : " << std::endl;
        for (auto& o : objects) o->draw();
    }
};

int main(int argc, const char * argv[]) {

    Group root("root");
    
    Circle c1, c2;
    root.objects.push_back(&c1);
    
    Group subGroup("sub");
    subGroup.objects.push_back(&c2);
    root.objects.push_back(&subGroup);
    
    root.draw();
    return 0;
}
