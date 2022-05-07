### Initial design

```mermaid
classDiagram
class Canvas {
    - std::vector<std::string> shapes;
    + void addShape(std::string& newShape);
    + void clearAll();
    + std::vector<std::string> getShapes();
}
class Button {
    <<interface>>
    + virtual ~Button();
    + virtual click();
}
class AddTriangleButton {
    - Canvas* canvas
    + AddTriangleButton(Canvas* canvas)
    + void click() override
}
class AddSquareButton {
    - Canvas* canvas
    + AddSquareButton(Canvas* canvas)
    + void click() override
}
class ClearButton {
    - Canvas* canvas
    + ClearButton(Canvas* canvas)
    + void click() override
}
Button <|..AddTriangleButton
Button <|..AddSquareButton
Button <|..ClearButton
AddTriangleButton --> Canvas
AddSquareButton --> Canvas
ClearButton --> Canvas
```
#### Problem:
- If we want to duplicate the functionality of say AddTriangleButton.. then we need to duplicate the code in to a new subclass.
- All of them contain reference to a `Canvas`, so limited to canvas only.

### Solution :

```mermaid
classDiagram
class Canvas {
    - std::vector<std::string> shapes;
    + void addShape(std::string& newShape);
    + void clearAll();
    + std::vector<std::string> getShapes();
}
class Button {
    - Command* command
    + Button(Command* command);
    + virtual click();
}
class Command {
    <<interface>>
    + virtual ~Button();
    + virtual click();
}
class AddShapeCommand {
    - Canvas* canvas
    - std::string shapeName
    + AddShapeCommand(std::string &shapeName, Canvas* canvas)
    + void execute() override
}
class ClearCommand {
    - Canvas* canvas
    + ClearButton(Canvas* canvas)
    + void click() override
}
Command <|..AddShapeCommand
Command <|..ClearCommand
AddShapeCommand --> Canvas
ClearCommand --> Canvas
Button --> Command
```