## 1. Chain of Responsibility

Examples:
- Various levels of authentication
- Validate a string given as input

#### Naive approach : 

Using if else or nested if else.

:x: Problem 
- What if we want to do the same thing for password
- Or if we want to change the order !

#### :heavy_check_mark: Solution : 
- Represent sequential check marks as a chain of handlers (or objects)!
- Each handler handles the situation or passes on the responsibility to the next handler.

```mermaid
classDiagram
class Handler {
    <<interface>>
    + Handler setNext(h : Handler)
    + handle(..)
}
class PasswordTooShortHandler {
    - h : Handler
    + Handler setNext(h : Handler)
    + handle(..)
}
class PasswordCharactersHandler {
    - h : Handler
    + Handler setNext(h : Handler)
    + handle(..)
}
Handler <|.. PasswordTooShortHandler
Handler <|.. PasswordCharactersHandler

```
#### Example

```mermaid
classDiagram
class StringValidator {
    <<interface>>
    + StringValidator* setNext(nextValidator : StringValidator*)
    + std::string Validate(std::string testString)
    + ~StringValidator()
}
class BaseValidator {
    # next : StringValidator*
    + StringValidator* setNext(nextValidator : StringValidator*)
    + std::string Validate(std::string testString)
    + ~BaseValidator()
}
class NonEmptyValidator {
    + std::string Validate(std::string testString)
}
class LengthValidator {
    - minLength : int
    + LengthValidator(minLength : int)
    + std::string Validate(std::string testString)
}
class RegexValidator {
    - patternName : std::string
    - regexString : std::string
    + RegexValidator(std::string patternName, std::string regexString)
    + std::string Validate(std::string testString)
}
class HistoryValidator {
    - historyItems : std::vector<std::string>
    + HistoryValidator(historyItems : std::vector<std::string>)
    + std::string Validate(std::string testString)
}
StringValidator <|.. BaseValidator
BaseValidator <|-- NonEmptyValidator
BaseValidator <|-- LengthValidator
BaseValidator <|-- RegexValidator
BaseValidator <|-- HistoryValidator
```