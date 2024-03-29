# DesignPatternsCPP

## 1. Single Responsiblity Principle

- Every software component should have one and only one responsibility
  - `Component` can be a class, method, or a module.
- E.g: Swiss army knife - Software component should not be like this!

**Every software component should have one and only one ~~responsibility~~ reason to change.**

### Cohesion 

_It is the degree to which the various parts of a software components are related._  
  
E.g : Scattered Garbage (low cohesion) -> Segregated garbage bin bags (high cohesion)

```java
public class Square {
  int side = 5;
  
  // --- High cohesion between calculateArea and calculatePerimeter
  public int calculateArea() {
    return side * side;
  }
  
  public int calculatePerimeter() {
    return 4 * side;
  }
  
  // --- High cohesion between draw and rotate
  public void draw() {
    if (hightResolutionMonitor) {
      // Reder a high resolution image
    }
    else {
      // Render a normal resolution image
    }
  }
  
  public void rotate(int degree) {
    // rotate the image to required degree and re render
  }
}
```

```java
public class Square {
  int side = 5;
  public int calculateArea() {
    return side * side;
  }
  
  public int calculatePerimeter() {
    return 4 * side;
  }
}

public class SquareUI {

  public void draw() {
    if (hightResolutionMonitor) {
      // Reder a high resolution image
    }
    else {
      // Render a normal resolution image
    }
  }
  
  public void rotate(int degree) {
    // rotate the image to required degree and re render
  }
}
```
**Square:** Responsibility of measurement of squares  
**SquareUI:** Responsibility of rendering images of squares.  

> ✔️**NOTE:** _"Higher cohesion helps attain better adherence to the single responsiblity principle"_


### Coupling

_"Coupling is defined as the level of inter dependency between various software components"_

E.g: Train is tightly coupled to it's rail, but not in Software components.

```java
public class Student {
  private String studentId;
  private Date studentDOB;
  private String address;
  
  // --- Tightly coupled to database here !
  public void save() {
    // Serialize object in to string
    String objectStr = MyUtils.serializeIntoAString(this);
    Connection connection = null;
    Statement stmt = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      connection = DriverManager.getconnection("jdbc:mysql://localhost:3306/MyDB", "root", "password");
      stmt = connection.createStatement();
      stmt.execute("INSERT INTO STUDENT VALUES (" + objectStr + ")");
    }
    catch (Exception e ) {
      e.printStackTrace();
    }
  }
  
  public String getStudentId() {
    return studentId;
  }
  
  public void setStudentId(String studentId) {
    this.studentId = studentId;
  }
}
```
Splitting the code : 

```java
// Reasons to change : Change in student profile
public class Student {
  private String studentId;
  private Date studentDOB;
  private String address;
  
  public void save() {
    new StudentRepository().save(this);
  }
  
  public String getStudentId() {
    return studentId;
  }
  
  public void setStudentId(String studentId) {
    this.studentId = studentId;
  }
}

// Reasons to change : Change in database.
public class StudentRepository {
  public void save(Student student) {
    // Serialize object in to string
    String objectStr = MyUtils.serializeIntoAString(student);
    Connection connection = null;
    Statement stmt = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      connection = DriverManager.getconnection("jdbc:mysql://localhost:3306/MyDB", "root", "password");
      stmt = connection.createStatement();
      stmt.execute("INSERT INTO STUDENT VALUES (" + objectStr + ")");
    }
    catch (Exception e ) {
      e.printStackTrace();
    }
  }
}
```

**Student:** Responsibility to handle core student profile data  
**StudentRepository:** Responsibility to handle database operations  

> ✔️**NOTE:** _"Loose coupling helps attain better adherence to the Single Responsibility Principle."_

***

## 2. Open closed Principle

_"Software Components should be closed for modification, but open for extension._

E.g : To add any feature, we did not do any change in the hardware of the existing console. But made it possible to add new features (extensions) like steering, guns. etc. 

**Closed for modification :**
- New features getting added to the sofware component, should NOT have to modify the existing code.

**Open for extension:**
- A software component should be extendable to add a new feature or to add a new behaviour to it. 


_**One State Insurance - For all your health insurance needs.**_
```java
public class InsurancePremiumDiscountCalculator {
  public int CalculatePremiumDiscountPercent(HealthInsuranceCustomerProfile customer) {
    if (customer.isLoyalCustomer()) {
      return 20;
    }
    return 0;
  }
}

public class HealthInsuranceCustomerProfile {
  public boolean isLoyalCustomer() {
    return true; // or false
  }
}
```

One State insurance acquires a vehicle insurance company...   

_**One State Insurance - For all your health and vehicle insurance needs.**_

Add a method and an overloaded method  
```java
public class VehicleInsuranceCustomerProfile {
  public boolean isLoyalCustomer() {
    return true; // or false
  }
}

public class InsurancePremiumDiscountCalculator {
  public int CalculatePremiumDiscountPercent(HealthInsuranceCustomerProfile customer) {
    if (customer.isLoyalCustomer()) {
      return 20;
    }
    return 0;
  }
  
  public int CalculatePremiumDiscountPercent(VehicleInsuranceCustomerProfile customer) {
    if (customer.isLoyalCustomer()) {
      return 20;
    }
    return 0;
  }
}
```

**Refactor to have a base class**

```mermaid
classDiagram
CustomerProfile <|-- HealthInsuranceCustomerProfile
CustomerProfile <|-- VehicleInsuranceCustomerProfile
CustomerProfile : public boolean isLoyalCustomer()
HealthInsuranceCustomerProfile : override public boolean isLoyalCustomer()
VehicleInsuranceCustomerProfile : override public boolean isLoyalCustomer()
class InsurancePremiumDiscountCalculator {
  + public int calculatePremiumDiscountPercent(CustomerProfile customer)
}
```

Now, if we need to say add another for Home insurance.. we do not need to modify any existing code. We just need to add an extra class `HomeInsuranceCustomerProfile`

### Takeaways
- Ease of adding new features
- Leads to minimal cost of developing and testing software.
- Open Closed Principle often requires decoupling, which in turn, automatically follows single responsibility principle.


***

## 3. Liskov Substitution Principle

_"Objects should be replaceable with their subtypes without affecting the correctness of the program."_

**Problem:** The 'Is-A' way of thinking.
- Gasoline is a fuel
- Car is a vehicle
- Ostrich is a bird. But..... Ostrich can not fly.

```java
public class Bird {
  public void fly() {
    // fly high
  }
}

public class Ostrich extends Bird {
  @override
  public void fly() {
    throw new RuntimeException();
  }
}
```

**Fails:** _"Objects should be replaceable with their subtypes without affecting the correctness of the program."_
If someone calls `fly` on ostrich.

> _**Change the `Is-A` way of thinking**_


Another example.

```mermaid
classDiagram
Car <|-- RacingCar
class Car {
  + public void getCabinWidth()
}
class RacingCar {
  + @override public void getCabinWidth() // unimplemented
  + public double getCockpitWidth()
}
```

```java
public class Car {
  public double getCabinWidth() {
    // return cabin width
  }
}

public class RacingCar extends Car {
  @override
  public double getCabinWidth() {
    // unimplemented
  }
  
  public double getCockpitWidth() {
    // return cock  pit width
  }
}
```

Usage:
```java
 public class CarUtils {
  public static void main(String[] args) {
    Car first = new Car();
    Car second = new Car();
    Car third = new RacingCar();
    
    List<Car> myCars = new ArrayList<>();
    myCars.add(first);
    myCars.add(second);
    myCars.add(third);
    
    for (Car car : myCars)
      System.out.Println(car.getCabinWidth()):
  }
 }
```


### ✔️ Solution: Break the hierarchy if the substitution fails
```mermaid
classDiagram
Vehicle <|-- RacingCar
Vehicle <|-- Car
```

```java
public class Vehicle {
  public double getInteriorWidth() {
  }
}

public class Car extends Vehicle {
  @override
  public double getInteriorWidth() {
    return this.getCabinWidth();
  }
  
  public double getCabinWidth() {
    // return cabin width
  }
}

public class RacingCar extends Vehicle {
  @override
  public double getInteriorWidth() {
    return this.getCockpitWidth();
  }
  
  public double getCockpitWidth() {
    // return cock pit width
  }
}
```

Another example :

i.e, 
```
if (product instanceof InHousProduct)
  ((InHouseProduct)product).applyExtraDiscount();
product.getDiscount();


to 

product.getDiscount();
```

### ✔️ Solution: Tell don't ask !

```mermaid
classDiagram
Product <|-- InHouseProduct
class Product {
  # double discount
  + double getDiscount();
}
class InHouseProduct {
  + double getDiscount();
  + void applyExtraDiscount();
}
```

**Liskov substitution passes.**

```java
public class Product {
  protected double discount = 20;
  
  public double getDiscount() {
    return discount;
  }
}

public class InHouseProduct extends Product {
  
  @override 
  public double getDiscount() {
    applyExtraDiscount():
    return discount;
  }
  
  public void applyExtraDiscount() {
    discount = discount * 1.5;
  }
}
```

***

## 4. Interface Segregation principle

_"No client should be forced to depend on methods it does not use."_

Design to represent all things in the office
- Printer
- Scanner 

But came across multi purpose device (XeroxWork center) which supports nearly all of them.. 

```mermaid
classDiagram
class IMultiFunction {
  <<interface>>
  + void print();
  + void getPrintSpoolDetails();
  + void scan();
  + void scanPhoto();
  + void fax();
  + void internetFax();
}
IMultiFunction <|-- XeroxWorkCenter
IMultiFunction <|-- HPPrinterNScanner
IMultiFunction <|-- CanonPrinter

class XeroxWorkCenter {
  + void print();
  + void getPrintSpoolDetails();
  + void scan();
  + void scanPhoto();
  + void fax();
  + void internetFax();
}
class HPPrinterNScanner {
  + void print();
  + void getPrintSpoolDetails();
  + void scan();
  + void scanPhoto();
  + ~~empty impl~~ void fax();
  + ~~empty impl~~ void internetFax();
}
class CanonPrinter {
  + void print();
  + void getPrintSpoolDetails();
  + ~~empty impl~~ void scan();
  + ~~empty impl~~ void scanPhoto();
  + ~~empty impl~~ void fax();
  + ~~empty impl~~ void internetFax();
}
```

**Issue:**
- A programmer tries to send a fax using the canon.. but empty implementation !

### ✔️Solution : Split the big interface in to smaller interfaces.

```mermaid
classDiagram
class IPrint {
  <<interface>>
  + void print();
  + void getPrintSpoolDetails();
}
class IScan {
  <<interface>>
  + void scan();
  + void scanPhoto();
}
class IFax {
  <<interface>>
  + void fax();
  + void internetFax();
}
IPrint <|-- XeroxWorkCenter
IScan <|-- XeroxWorkCenter
IFax <|-- XeroxWorkCenter
IPrint <|-- HPPrinterNScanner
IScan <|-- HPPrinterNScanner
IPrint <|-- CanonPrinter

class XeroxWorkCenter {
  + void print();
  + void getPrintSpoolDetails();
  + void scan();
  + void scanPhoto();
  + void fax();
  + void internetFax();
}
class HPPrinterNScanner {
  + void print();
  + void getPrintSpoolDetails();
  + void scan();
  + void scanPhoto();
}
class CanonPrinter {
  + void print();
  + void getPrintSpoolDetails();
}
```

#### Techniques to identify violations of ISP
- Fat Interfaces. : Interfaces with high number of methods.
- Interfaces with Low cohesion : In above, fax, photoscan .. are totally different (no cohesion)
- Empty Method Implementations.


#### Relations with other solid principles
- Following automatically SRP
- Follows Liskov substituion principle.


***

## 5. Dependency Inversion principle (DIP)

- _"High-level modules should not depend on low-level modules. Both should depend on abstractions"_
- _"Abstractions should not depend on details. Details should depend on abstractions."_

#### High level / Low level module

* The term is relative. 

```mermaid
flowchart TD
  id1(ProductCatalog) --> id2(SQLProductRepository)
  id3(PaymentProcessor) --> id4(GooglePayGateway)
  id3 --> id5(WireTransfer)
  id6(CustomerProfile) --> id7(Communication)
  id7 --> id8(EmailSender)
  id7 --> id9(VoiceDialer)
  subgraph 1
  id1
  id3
  id6
  end
  subgraph 2
  id2
  id4
  id5
  id7
  end
  subgraph 3
  id8
  id9
  end
```

❌ **Breaks DIP as high level modules depends on low modules**

```java
public class ProductCatalog {
  public void listAllProducts() {
    SQLProductRepository sqlProductRepository = new SQLProductRepository();
    
    List<String> allProductNames = sqlProductRepository.getAllProductNames();
  }
}


public class SQLProductRepository  {
  public List<String> getAllProductNames() {
    return Arrays.asList("soap", "toothpaste");
  }
}
```

#### ✔️ Solution: Both should depend on abstractions !

```java
public class ProductCatalog {
  public void listAllProducts() {
    ProductRepository productRepository = ProductFactory.create();
    
    List<String> allProductNames = productRepository.getAllProductNames();
  }
}

public class ProductFactory {
  pubilc static ProductRepository create(){
    return new SQLProductRepository();
  }
}

public interface ProductRepository {
  public List<String> getAllProductNames();
}

public class SQLProductRepository  {
  public List<String> getAllProductNames() {
    return Arrays.asList("soap", "toothpaste");
  }
}
```

```mermaid
flowchart TD
  id1(ProductCatalog) --> id10(ProductRepository)
  id2(SQLProductRepository) --> id10
  id1 --> id11(ProductFactory)
```

* **First i.e, high level do not depend onthe low level.**
* **Second i.e, the detail is dependent on the abstract**

#### Dependency Injection
- Even with the above solution the responsibilty of creation is with the ProductCatalog class. we do not want that !
- Avoids tight coupling
- Avoids a class creating it's dependencies.
- Inversion of control

```java
public class ECommerceMainApplication {
  public static main(String[] args) {
    ProductRepository productRepository = new ProductFactory.create();
    ProductCatalog productCatalog = new ProductCatalog(productRepository);
    productCatalog.listAllProducts();
  }
}
public class ProductCatalog {
  private ProductRepository productRepository;
  
  public ProductCatalog( ProductRepository productRepository) {
    this.productRepository = productRepository;
  }
  
  public void listAllProducts() {
    List<String> allProductNames = productRepository.getAllProductNames();
  }
}

public class ProductFactory {
  pubilc static ProductRepository create(){
    return new SQLProductRepository();
  }
}

public interface ProductRepository {
  public List<String> getAllProductNames();
}

public class SQLProductRepository  {
  public List<String> getAllProductNames() {
    return Arrays.asList("soap", "toothpaste");
  }
}
```

#### Inversion of Control (IOC)

- In the above code, injection is happening in the main control flow of the program!
- i.e, in the main thread.. what if we want this to happen in different thread or context ?

##### ✔️ Sprint IOC Container

- main context
- spring context

> _Spring context --> Here is the productCatalog object. I have already provided it all its dependencies - a new SQLProductRepository object. --> Main context_





