## Mediator

### Problem
Consider a form, 

* First Name
* Last Name
* Employment Status
* Marital Status

Now, if the person is employed.. then add few more ...
* Employer Name
* Position Title
* Number of years at the company


If married
* Spouse's First Name
* Spouse's Last Name

**This creates complex dependency of Text boxes on the logic, We can not reuse the text box, if we want to reuse it.**


### The mediator patterns' solution

*Instead of having each class know about other classes, create a mediator object that manages all the relationships between these classes.*


```mermaid
classDiagram
    class Mediator {
        <<Interface>>
        + mediate(Mediated m)
    }

    class ConcreteMediator {
        + mediate(Mediated m)
    }

    class Mediated {
        <<Interface/Abstract>>
        - Mediator m 
        + doSomething()
    }
    Mediator <|.. ConcreteMediator
```


```mermaid
classDiagram
    class InterfaceElement {
        - std::string name
        - bool visibility
        + InterfaceElement(std::string name, bool visibility)
        + std::string GetDescription()
    }
    InterfaceElement <|.. ButtonElement
    class ButtonElement {
        <<Interface>>
        + ButtonElement(std::string name, bool visibility)
        + void Click() = 0
    }
    InterfaceElement <|.. TextBox
    class TextBox {
        <<Interface>>
        - std::string textValue
        + TextBox(std::string name, bool visibility)
        + void ChangeText(std::string newText)
    }
    InterfaceElement <|.. CheckBox
    class CheckBox {
        <<Interface>>
        - bool isChecked
        + CheckBox(std::string name, bool visibility)
        + void SetIsChecked(bool isChecked)
    }
    ButtonElement <|.. SubmitButton
    class SubmitButton {
    }
    TextBox <|.. NameTextBox
    class NameTextBox {
        - SubmitButton *submitButton;
    }
    TextBox <|.. SpousesNameTextBox
    class SpousesNameTextBox {
    }
    CheckBox <|.. IsMarriedCheckbox
    class IsMarriedCheckbox {
        - SpousesNameTextBox *spousesNameTextBox;
    }
    SubmitButton <-- NameTextBox
    SpousesNameTextBox <-- IsMarriedCheckbox

```

```mermaid
classDiagram
    class Mediator {
        <<Interface>>
        + void mediate(std::string& event)
    }
    InterfaceElement --> Mediator
    class InterfaceElement {
        # Mediator* mediator
        # std::string name
        # bool visibility
        + InterfaceElement(std::string name, bool visibility, Mediator* mediator)
        + std::string GetDescription()
    }
    InterfaceElement <|.. ButtonElement
    class ButtonElement {
        <<Interface>>
        + ButtonElement(std::string name, bool visibility, Mediator*)
        + void Click() = 0
    }
    InterfaceElement <|.. TextBox
    class TextBox {
        <<Interface>>
        - std::string textValue
        + TextBox(std::string name, bool visibility, Mediator*)
        + void ChangeText(std::string newText)
    }
    InterfaceElement <|.. CheckBox
    class CheckBox {
        <<Interface>>
        - bool isChecked
        + CheckBox(std::string name, bool visibility, Mediator*)
        + void SetIsChecked(bool isChecked)
    }
    Mediator <|.. UserInterface
    class UserInterface {
        - TextBox* nameTextBox
        - CheckBox* isMarriedCheckBox
        - TextBox* spouseNameTextBox
        - ButtonElement* submitButton
        + mediate(std::string& event) override
    }

```