### When do we need ?

- Use of `new` requires name of class ! (Calling code tightly coupled with the class) 
- What if the application does not know which object to create at compile time ? 

### Intent

Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory method lets class defer instantiation to the subclasses.
- **Provide a constructor method, which can be overriden by the concrete classes.**
- Factory method also known as virtual constructor**


## Examples in std

### unique_ptr

### shared_ptr
