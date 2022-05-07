## 2. Command Pattern

#### When should I use the command pattern?
Use this pattern to reduce coupling between classes that call one another and make functionality more reusable between similar classes.

#### Example situation 

- Clear canvas button needs to clear figures in the canvas.
- Calls done

```mermaid
flowchart TD
id1(Clear Canvas) --> id2("editor.ClearAll();")
id2 --> id3("strokes = [];")
```

- **Problem:** 
    - Forms tight coupling between different pieces of code
    - Buttons know about the canvas.


#### :heavy_check_mark: Solution

- Represent events or changes that can occur in our program as their own classes, which implement a common command interface.

```mermaid
classDiagram
class Command {
    <<interface>>
    + execute()
}
class ClearCanvasCommand {
    - target : Canvas
    - params
    + setTarget(target)
    + execute()
}
class DrawLineCommand {
    - target : Canvas
    - x1
    - x2
    - y1
    - y2
    + setTarget(target)
    + execute()
}
class ClearCanvasButton {
    - command
    + setCommand(command)
}
class DrawLineButton {
    - command
    + setCommand(command)
}
Command <|..ClearCanvasCommand
Command <|..DrawLineCommand
ClearCanvasCommand <-- ClearCanvasButton
DrawLineCommand <-- DrawLineButton
```