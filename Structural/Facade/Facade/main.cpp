//
//  main.cpp
//  Facade
//
//  Created by Aniket Bhushan on 19/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include "Console.hpp"

int main(int argc, const char * argv[]) {
    
    // Single column setup
    auto window = Console::instance().single("Test", 50, 30);
    window->Show();
    
    // Multi column setup
    auto mcwindow = Console::instance().multiColumn("Test", 2, 40, 40);
    for(size_t i=0; i<40; ++i)
        mcwindow->buffers[1]->add_string("This is line" + boost::lexical_cast<std::string>(i));

    mcwindow->Show();
    
    return 0;
}
