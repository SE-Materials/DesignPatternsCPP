//
//  main.cpp
//  FactoryMethod
//
//  Created by Aniket Bhushan on 15/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

class Button
{
    Button()
    {
        
    }
    
public:
    void Render(int a, int b)
    {
        std::cout << "Rendering : " << a << ", " << b << std::endl;
    }
    
    void OnClick()
    {
        std::cout << "Button clicked" << std::endl;
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
