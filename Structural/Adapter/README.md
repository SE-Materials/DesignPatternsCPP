#  Adapter

A constructor which adapts to an existing interface X to  conform to the required interace Y. 

## Stack 

Adapter over an existing container. 

```cpp
template <class Ty, Container = deque<Ty>>
class Stack
{
public:
    void pop()
    {
        c.pop_back();
    }
protected:
    Container c;
};

We can also do 

std::stack<int, std::vector<int>> s;

// If we try to use struct :
struct T {};

std::stack<int, T> s; // This will not work as T needs to satisfy some interface

```

## String

An adapter for providing an interface like to_lower and split

## Vector / Raster

A line to point adapter
But this has a problem !! See below

## Adapter Caching

Since there are eight lines, so 8 calls makes sense to LineToPointAdapter. 
But as the dialog is dragged around it gets called alot many times. 

### Solution : Generate hash

```cpp
friend std::size_t hash_value(const Point& obj)
{
    std::size_t seed = 0x1E44943F;
    boost::hash_combine(seed, obj.x);
    boost::hash_combine(seed, obj.y);
    return seed;
}

Similar for Line

friend std::size_t hash_value(const Line& obj)
{
    std::size_t seed = 0x1E44943F;
    boost::hash_combine(seed, obj.start);
    boost::hash_combine(seed, obj.end);
    return seed;
}

struct LineToPointCachingAdapter
{
LineToPointCachingAdapter(Line& line)
{
    // return points based on cached content
    // If cached return that, else create a new ones and cache it
}
private:
    std::size_t line_hash;
    static std::map<std::size_t, std::vector<Point>> cache;
};
```
## Notes

* Determine the API that you have and the API you need
* Create a component which aggregates (has a reference to) the adaptee
* Intermediate representations can pile up; use caching and other optimizations.
