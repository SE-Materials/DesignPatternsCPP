//
//  Console.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 19/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#ifndef Console_hpp
#define Console_hpp

#include <stdio.h>
#include <vector>
//#include <Window.h>

class Window;
class TextBuffer;
class ViewPort;
class Point;

class Console
{
    std::vector<std::shared_ptr<Window>> windows;

    std::shared_ptr<Window> single(const std::string& title, uint8_t charsWide, uint8_t charsHigh)
    {
        auto w = std::make_shared<Window>(title, charsWide*charsWidth, charsHigh*charsHeight);
        auto buffer = std::make_shared<TextBuffer>(charsWide, charsHigh);
        w->buffers.push_back(buffer);
        
        auto viewPort = std::make_shared<ViewPort>(buffer);
        w->viewports.push_back(viewPort);
        
        windows.push_back(w);
        return w;
    }
    
    std::shared_ptr<Window> multiColumn(const std::string& title, uint8_t columnCount, uint8_t columnWidth, uint8_t charsHigh)
    {
        auto w = std::make_shared<Window>(title, columnCount*columnWidth*charsWidth, charsHigh*charsHeight);
        
        for (uint8_t c = 0; c<columnWidth; c++)
        {
            auto buffer = std::make_shared<TextBuffer>(columnWidth, charsHigh);
            w->buffers.push_back(buffer);
            
            auto viewPort = std::make_shared<ViewPort>(buffer, buffer->get_size(), Point{}, Point{columnWidth*c, 0});
            w->viewports.push_back(viewPort);
            
            windows.push_back(w);
        }
        return w;
    }
    
    static Console& instance()
    {
        static Console console;
        return console;
    }

private:
    const int charsWidth {10}, charsHeight{14};

    Console(){}
    Console(const Console& other) = delete;
    const Console& operator=(const Console& other) = delete;
};

#endif /* Console_hpp */
