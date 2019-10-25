//
//  main.cpp
//  AdapterCaching
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include "Geometry.h"


std::vector<std::shared_ptr<VectorObject>> vectorObjects {
    std::make_shared<VectorRectangle> (10, 10, 100, 100),
    std::make_shared<VectorRectangle> (30, 30, 60, 60)
};

struct LineToPointCachingAdapter
{
    typedef std::vector<Point> Points;
    
    LineToPointCachingAdapter(Line& line)
    {
        boost::hash<Line> hash;
        line_hash = hash(line);
        
        if (cache.find(line_hash) != cache.end())
            return;
        
        // Counter
        static int count = 0;
        //        TRACE("%d: Generating points for line \n", count++);
        
        Points points;
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
        
        cache[line_hash] = points;
        
    }
    
    virtual Points::iterator begin(){return cache[line_hash].begin();}
    virtual Points::iterator end(){return cache[line_hash].end();}
    
private:
    std::size_t line_hash;
    static std::map<std::size_t, std::vector<Point>> cache;
};
std::map<std::size_t, std::vector<Point>> LineToPointCachingAdapter::cache;


struct LineToPointAdapter
{
    typedef std::vector<Point> Points;
    
    LineToPointAdapter(Line& line)
    {
        // Counter
        static int count = 0;
        //        TRACE("%d: Generating points for line \n", count++);
        
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
            LineToPointCachingAdapter lpo{l};
            DrawPoints(lpo.begin(), lpo.end());
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
