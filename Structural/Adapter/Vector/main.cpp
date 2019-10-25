//
//  main.cpp
//  Vector
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Geometry.h"


std::vector<std::shared_ptr<VectorObject>> vectorObjects {
    std::make_shared<VectorRectangle> (10, 10, 100, 100),
    std::make_shared<VectorRectangle> (30, 30, 60, 60)
};

struct LineToPointAdapter
{
    typedef std::vector<Point> Points;
    
    LineToPointAdapter(Line& line)
    {
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        
        if (dx == 0)
        {
            for (int y=top; y<=bottom; ++y)
                points.emplace_back(Point{left, y});
        }
        else if (dy == 0)
        {
            for (int x=left; x<=right; ++x)
                points.emplace_back(Point{x, top});
        }
    }
    
    virtual Points::iterator begin(){return points.begin();}
    virtual Points::iterator end(){return points.end();}
    
private:
    Points points;
};

//
void DrawPoints
(
/*CPaintDC& dc,*/
 std::vector<Point>::iterator begin,
 std::vector<Point>::iterator end
 )
{
    for (auto i=begin; i<end; ++i);
    //        dc.SetPixel(i->x, i->y, 0);
}

void onPaint()
{
    for (auto& o : vectorObjects)
    {
        for (auto& l : *o)
        {
            LineToPointAdapter lpo{l};
            DrawPoints(lpo.begin(), lpo.end());
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
