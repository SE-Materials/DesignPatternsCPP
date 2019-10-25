#  Decorator pattern

Want to augment existing functionality.

Do not want to re write or alter existing code (OCP)

Want to keep new functionality separate (SRP)

Need to be able to interact with existing structures.

**Allows for adding behavior to individual objects without affecting the behavior of other objects of the same class.**

## Function Decorator

## Wrapping Decorator

## Mixin Decorator

* For above we have to create first circle to create a red circle !
* If circle has method to resize, but then red circle and transparentCircle will not have this method !!

Solution using mixin inheritance 

Here no need to have an instance or inherit. 
```
template <typename T> struct ColoredShape2 : T {}
```
Need default constructors here !


## Usability Improvements

1. We can have any class/ struct
 
 ```cpp
 struct NotAShape
 {
    virtual std::string str() const {return std::string{};}
 };
 
 ColoredShape2<NotAShape> legal; // !! I don't want this 
 
 So, we have to add that T should be 'Shape'
 
 template <typename T>
 struct ColoredShape2 : T 
 {
    static_assert(is_base_of<Shape, T>::value, "Template args must be a shape!");
 };
 ```
 
 2. Problem of constructor
 
 ``` cpp
 // We can't do this, we can only specify transparency not shape !!
 TransparentShape2<Square> hiddenSquare{0, 15};
 
 Solution : 
 
 template <typename T>
 struct TransparentShape
 {
    uint8_t transparency;
    
    // Add template to constructor
    template <typename ...Args>
    TransparentShape(const uint8_t transparency, Args ...args) : T::T(args...), transparency{transparency}
    {
    }
};

Now, 
TransparenctShape<Square> hiddenSquare{0, 15}; // Will work perfectly fine
std::cout << hiddenSquare.str() << std::endl;

 ```
* Delete the default constructor !

## Notes 

* Functional decorators let you wrap function with before/after code 
* An aggregate decorator does not give you the underlying object's features, but can be composed at runtime.
* A decorator based on mixin inheritance is more flexible, exposes underlying object's features, but is only constructible at compile time. 


