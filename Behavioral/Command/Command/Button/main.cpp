#include <iostream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto el : vec) {
        os << el << " ";
    }
    os << std::endl;
    return os;
}

class Canvas {
    std::vector<std::string> m_shapes;
public:
    void AddShape(std::string& shape) {
        m_shapes.push_back(shape);
    }
    
    void ClearAll() {
        m_shapes.clear();
    }

    std::vector<std::string> GetShapes() {
        return m_shapes;
    }
};

class ICommand {

public:
    ~ICommand() = default;
    virtual void Execute() = 0;
};

class Button {
    ICommand* m_command;
public:
    Button (ICommand* command) : m_command {command} {}
    ~Button() {
        delete m_command;
    }
    void Click() {
        if (m_command != nullptr)
            m_command->Execute();
    }
};

class AddShapeCommand : public ICommand {
    Canvas *m_canvas;
    std::string m_shapeName;
public:
    AddShapeCommand(const std::string& shapeName, Canvas* canvas) : 
        m_canvas {canvas}, 
        m_shapeName {shapeName}
    {}

    void Execute() override {
        m_canvas->AddShape(m_shapeName);
    }
};

class ClearCommand : public ICommand {
    Canvas* m_canvas;
public:
    ClearCommand(Canvas* canvas) : m_canvas {canvas} {}

    void Execute() override {
        m_canvas->ClearAll();
    }
};

int main(int argc, char const *argv[])
{
    Canvas* canvas = new Canvas();
    auto addSquareShapeButton   = new Button(new AddShapeCommand("square", canvas));
    auto addCircleShapeButton   = new Button(new AddShapeCommand("circle", canvas));
    auto addTriangleShapeButton = new Button(new AddShapeCommand("triangle", canvas));
    auto clearShapesButton      = new Button(new ClearCommand(canvas));

    std::cout << "Initialized canvas " << std::endl;

    std::cout << "Current shapes : ";
    auto shapes = canvas->GetShapes();
    std::cout << shapes;

    std::cout << "Add Square, Circle" << std::endl;
    addSquareShapeButton->Click();
    addCircleShapeButton->Click();

    std::cout << "Current shapes : ";
    shapes = canvas->GetShapes();
    std::cout << shapes;

    std::cout << "Clearing all " << std::endl;
    clearShapesButton->Click();

    std::cout << "Current shapes : ";
    shapes = canvas->GetShapes();
    std::cout << shapes;

    std::cout << "Add triangle" << std::endl;
    addTriangleShapeButton->Click();

    std::cout << "Current shapes : ";
    shapes = canvas->GetShapes();
    std::cout << shapes;

    std::cout << "Clearing all " << std::endl;
    clearShapesButton->Click();

    std::cout << "Current shapes : ";
    shapes = canvas->GetShapes();
    std::cout << shapes;


    delete canvas;
    return 0;
}
