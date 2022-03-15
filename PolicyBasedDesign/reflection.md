Combine little classes with a single structural or behavioural responsibility (policies) to make a class with complex behaviour.

## How can we achieve this combining of little classes to a big one?

- There is always a multiplicity of solution like what's a good solution for it?  
    It can be:  
    - Events?
    - Objects?
    - Observers?
    - Callbacks?
    - Virtuals?
    - Templates?

    Well up to certain scale all of them work. But then difference between a software architect and beginner if the knowledge of what works and what doesn't!

    Experienced designer is like a good chess player!

- Do-It-All interface
    - Loss of static type safety. (enforcing constraints at compile time)
    - Gap between syntatically valid and semantically valid use of the library.
        - E.g: Single with thread safety, all or no access to thread !
    - Intellectual overhead
    - Designs enforce constraints; also must help user-crafted designs to enforce their own constraints instead of only predefined ones.  

- Multiple Inheritance
    - Can handle this combinatorial explosion through clever choice of base classes.
    - Fails :
        - No boilerplate code.
        - Missing type information
        - State manipulation: virtual inheritance.
        
- Template
- Policies and Policy Classes