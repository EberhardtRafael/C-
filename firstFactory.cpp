#include <iostream>
#include <memory>
#include <new> 
#include<math.h>
#include <typeinfo>
#include <vector>
#include<cassert>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------Stuff I coded just for learning porposes-------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

/*
//-------------------------------------------------------------------------------------------------------------------------------
//Public structure

struct MyClass {
    
    private:
      string name;
      
    public:
          
        MyClass() { //Constructor
            std::cout << "constructed [" << this << "]\n";
        }
        //There's no destructor for now.
        
        //setter
        void setName(string n){
            name = n;
        }
        
        //getter
        string getName(){
            return name;
        }
        
        //Whats I tended to do
        void printName(){
            cout<< name << "\n";
        }
        
        MyClass(const MyClass& other) = delete;
        
        ~MyClass(){ //Destructor.
            cout << "Destructing [" << this << "]" << endl;
        }
};

//-------------------------------------------------------------------------------------------------------------------------------
//Public Method

void UseRawPointer()
{
    // Using a raw pointer -- not recommended.
    MyClass * p1 = new MyClass;
    
    p1->setName("Teste");
    p1->printName();
    
    // Don't forget to delete!
    delete p1; 
}

//-------------------------------------------------------------------------------------------------------------------------------
//Public Method

//-------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------SMART POINTER-------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

void UseSmartPointer()
{
    // Declare a smart pointer on stack and pass it the raw pointer.
    //unique_ptr<MyClass> bla(new MyClass); //Not recomended
    auto bla = std::make_unique<MyClass>(); //Much better
    
    bla->setName("Teste2");
    bla->printName();
    

} // bla is deleted automatically here.

//-------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------HOW NOT to implement Factory Method----------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Geometric class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

/*
class Creator{

    public:
        virtual ~Creator() = default; //Elegant way to declare a destructor which I'm not customizing. Alternative: virtual ~Creator(){};
        virtual Geometric* FactoryMethod() const = 0; //Pure virtual FactoryMethod() function.
    */
        
    /**
       * Also note that, despite its name, the Creator's primary responsibility is
       * not creating products. Usually, it contains some core business logic that
       * relies on Geometric objects, returned by the factory method. Subclasses can
       * indirectly change that business logic by overriding the factory method and
       * returning a different type of product from it.
   */
   
       /*   
       //Now I need to make this useful for my case.
       float someOperation() const {
            // Call the factory method to create a Geometric object.
            Geometric* geometricElement = this->FactoryMethod();
            //Now use the GeometricElement.
            float result = 1;
            //float result =  geometricElement.getLength();
            //string result = "TESTE"; //Come back and change!!!!!!!!!
            delete geometricElement;
            return result;
       }
};*/


/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
 
//class LineSectionCreator : public Creator {

    /**
   * Note that the signature of the method still uses the abstract product type,
   * even though the concrete product is actually returned from the method. This
   * way the Creator can stay independent of concrete product classes.
   */
   
    /*public: 
        Geometric* FactoryMethod() const override{
            Point p1(0, 0);
            Point p2(5, 115);
            return new LineSection(p1, p2); //*(CRIME!)* I'm commiting a crime, cause my concrete objects don't have same interface. *(CRIME!)* 
        }
};

class TriangleCreator : public Creator {

    public: 
        Geometric* FactoryMethod() const override{
            Point p1(0, 0);
            Point p2(5, 115);
            Point p3(10, 6);
            return new Triangle(p1, p2, p3); //*(CRIME!)* I'm commiting a crime, cause my concrete objects don't have same interface. *(CRIME!)* 
        }
};  */

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
/*
void ClientCode(const Creator& creator) {
  // ...
  cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.someOperation() << endl;
  // ...
}*/

//Example above shows HOW NOT to implement Factory Method.

//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Actual work---------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------Stuff that was given me-----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

struct lengthInterface{
    virtual float getLength() const = 0; //I changed from int to float.
};

struct AreaInterface{
    virtual float getArea() const = 0;
};

class Geometric{
    public:
    virtual ~Geometric() = default; //This is the destructor.
};


class Point : public Geometric{
    int x, y;
      public:
          Point(int x_=0, int y_=0) : x(x_), y(y_) {}
          
          
          //(QUESTION!)
          //Changes I have made (without them, I couldn't make it):
          //(QUESTION!)
          
         virtual int getX() const { //Need to tell the compiler I'm not gonna change anything, so I need to make this const.
              return x;
          }
          
          virtual int getY() const { 
              return y;
          }
          
};

//-------------------------------------------------------------------------------------------------------------------------------
//------------------------------1) Construa o corpo das seguintes classes:-------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//Private class
class LineSection : public Geometric, public lengthInterface{
    
    private:
        Point p1, p2;
        
    public:
        LineSection(Point _p1 = Point(0, 0), Point _p2 = Point(1, 0)) : p1(_p1), p2(_p2) {}
        
        //(SEARCH) Search for Move semantics. (SEARCH)
           
    public:
        
        // (QUESTION!)
        // I don't think I should have two getters, so I should come back here and see this through, but this is the happy path:
        //(QUESTION!)
        //(Solved)
        
        void setPoints(Point p1_, Point p2_){
            p1 = p1_;
            p2 = p2_; 
        }
        
        Point getP1() const{
            return p1;
        }
        
        Point getP2() const{
            return p2;
        }
        //Go for pair!!!
        //std::makePair()...
        //C++ 2017 standard
        
        float getLength() const override { //override seems optional.
           int deltax = p2.getX() - p1.getX();
           int deltay = p2.getY() - p1.getY();    
           return sqrt(deltax*deltax + deltay*deltay);     
        }
    
    ~LineSection() = default;

};
//-------------------------------------------------------------------------------------------------------------------------------

//Pending: READ ABOUT const.

//-------------------------------------------------------------------------------------------------------------------------------
//Private class

class Triangle : public Geometric, public lengthInterface, public AreaInterface{

    private:
        Point p1, p2, p3;
        
    public:
        Triangle(Point _p1 = Point(0, 0), Point _p2 = Point(0, 1), Point _p3 = Point(1, 0) ) : p1(_p1), p2(_p2), p3(_p3){}
       
        // (QUESTION!) Should I have ScalarProduct class? (QUESTION!) (solved)
        // (QUESTION!) Should I have class just to measure stuff in the triangle? (QUESTION!) (solved)
        float getArea() const{
            //Make a triangle with same characteristics at the origin:
            Point p1_(0, 0);
            Point p2_(p2.getX() - p1.getX(), p2.getY() - p1.getY());
            Point p3_(p3.getX() - p1.getX(), p3.getY() - p1.getY());
            LineSection l1(p1, p2), l2(p1, p3), l3(p2, p3);
            //Scalar product between the sides with angle at the origin:
            float cosa = (p2_.getX()*p3_.getX() + p2_.getY()*p3_.getY())/(l1.getLength() * l2.getLength()); 
            float a = acos(cosa); //Get the angle at the origin.
            float h = sin(a)*l1.getLength(); //Get the hight with simple trigonometry.
            return l2.getLength()*h/2.; //Get the area.
        }
        
        float getLength() const override { //Returns the perimeter, actually.
            LineSection l1(p1, p2), l2(p1, p3), l3(p2, p3);
            return l1.getLength() + l2.getLength() + l3.getLength(); //Keep it simple, stupid.
        }
    
        ~Triangle() = default;

};
//-------------------------------------------------------------------------------------------------------------------------------

class Point2 :public lengthInterface, public AreaInterface, public Point {
    
    std::unique_ptr<Geometric> g;
    Point* p;
    
    public:
        Point2(std::unique_ptr<Geometric> G){
            p =  dynamic_cast<Point*>(G.get()); 
            assert(p);
            if(p){
                g = std::move(G);
            }
        }
        
       float getLength() const override {
           return 0;
       } 
        
	float getArea() const override {
           return 0;
       }
       
       int getX() const override { //Need to tell the compiler I'm not gonna change anything, so I need to make this const.
              if(p) return p->getX();
              else throw std::runtime_error("No point found.");
          }
          
          int getY() const override { 
              if(p) return p->getY();
              else throw std::runtime_error("No point found.");
          }
};
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
//--------------------------2) Construa uma factory de Elementos Geométricos-----------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

// I already have one abstract class determining the interface of the whole bunch of concrete geometric objects.
// I already have implemented said concrete classes.
//Now I need a creator class.

//-------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Parametrized Factory Method:-----------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

std::unique_ptr<Geometric> CreateGeometricElement(int Id, Point p1 = Point(0, 0), Point p2 = Point(1, 0), Point p3 = Point(0, 1)) {
    
      
    //Point p1(0, 0), p2(1, 0), p3(1, 1); 
    
    std::unique_ptr<Geometric> geometricElement;
    
    switch(Id) {
        case 1:
            geometricElement = std::make_unique<Point>(p1);
            break;
        case 2:
            geometricElement = std::make_unique<LineSection>(p1, p2);
            break;
        case 3:
            geometricElement = std::make_unique<Triangle>(p1, p2, p3);    
            break;
    }
    
    return geometricElement; 
}


//Go for exceptions in C++.

//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
//----------------------------2)Construa uma classe para armazenar os elementos geométricos--------------------------------------
//-------------------crie um método para retornar o somatório dos perímetros de todos os elementos-------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

class vecGeometricElement {
    
    vector< std::unique_ptr<Geometric> > geometricElementsVector;
    
    public:
//        vecGeometricElement() {} I don't need to declare the constructor. C++ does the job for me. Except when my class depends on a class that doesn't have a standard constructor
        
        void insertElement(std::unique_ptr<Geometric> element){ //(SEARCH) Read about templates. (SEARCH)
            geometricElementsVector.push_back(std::move(element));
        }
        
        float getPerimeterSum(){
            float perimeterSum = 0;
            for(int i = 0; i < geometricElementsVector.size(); i++){
                auto l =  dynamic_cast<lengthInterface*>(geometricElementsVector[i].get()); 
                if(l){
	  	    perimeterSum += l->getLength();
	  	}
            }
            // (SEARCH) Pointer = indirection. (SEARCH)
            //C++: strongly typed.
            //Python minimally typed.
            return perimeterSum;
        }
        
        std::unique_ptr<Geometric> getElement(int i){
            auto bla = move(geometricElementsVector[i]);	
            return bla;         
        }
        
        int size(){
            return geometricElementsVector.size();
        }
};


int minXinLines(LineSection l1, LineSection l2){
    int xmin = l1.getP1().getX();
    
    int Xs[4] = {l1.getP1().getX(), l1.getP2().getX(), l2.getP1().getX(), l2.getP2().getX()};
    
    for(int i = 0; i < 4; i++)
        if(Xs[i] < xmin) xmin = Xs[i];
    
    return xmin;
}

int minYinLines(LineSection l1, LineSection l2){
    int ymin = l1.getP1().getX();
    
    int Ys[4] = {l1.getP1().getY(), l1.getP2().getY(), l2.getP1().getY(), l2.getP2().getY()};
    
    for(int i = 0; i < 4; i++)
        if(Ys[i] < ymin) ymin = Ys[i];
    
    return ymin;
}

int maxXinLines(LineSection l1, LineSection l2){
    int xmax = l1.getP1().getX();
    
    int Xs[4] = {l1.getP1().getX(), l1.getP2().getX(), l2.getP1().getX(), l2.getP2().getX()};
    
    for(int i = 0; i < 4; i++)
        if(Xs[i] > xmax) xmax	 = Xs[i];
    
    return xmax;
}

int maxYinLines(LineSection l1, LineSection l2){
    int ymax = l1.getP1().getX();
    
    int Ys[4] = {l1.getP1().getY(), l1.getP2().getY(), l2.getP1().getY(), l2.getP2().getY()};
    
    for(int i = 0; i < 4; i++)
        if(Ys[i] > ymax) ymax = Ys[i];
    
    return ymax;
}


LineSection sumLines(LineSection l1, LineSection l2){

    return LineSection(Point(l1.getP1().getX() + l2.getP1().getX(), l1.getP1().getY() + l2.getP1().getY()), Point(l1.getP2().getX() + l2.getP2().getX(), l1.getP2().getY() + l2.getP2().getY()));
}


//-------------------------------------------------------------------------------------------------------------------------------


int main() {



//(QUESTION) What is a friend class? (QUESTION) (solved)


//-------------------------------------------------------------------------------------------------------------------------------
//------------------Just me learning how to implement stuff (gonna leave it just for the reccord)--------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

//UseRawPointer();
//UseSmartPointer();

//MyClass MyObj;
//MyObj.setName("Teste3");
//cout << MyObj.getName() << "\n";

//unique_ptr<Geometric> geometricElement(new Geometric); //This might be a way to declare a unique pointer.
//auto geometricElement = std::make_unique<Geometric>();
//Geometric* geometricElement = std::make_unique<Geometric>();
//Geometric* geometricElement = CreateGeometricElement(2);
//unique_ptr<Geometric> bla = CreateGeometricElement(1);
//Point* p = dynamic_cast<Point*>(bla.get()); //.get() return the raw pointer
//Point* p =  dynamic_cast<Point*>(bla);
//LineSection* l =  dynamic_cast<LineSection*>(geometricElement); //This is sure a long way to instantiate an object. 

//if(bla){
//    cout << p->getX() << endl;
//}else cout << "Oops." << endl;

//cout << l->getP1().getX() << endl;
//l->setPoints(p1, p2);
//cout << l->getP1().getX() << endl;

//-------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------Testing implementation of the Factory Method--------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

//auto geometricElement = CreateGeometricElement();
//Point* bla =  dynamic_cast<Point*>(geometricElement); //Success!!!
//
//if(bla){
//    cout << bla->getX() << endl;
//}else cout << "Idiot" << endl;

//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
//---Testing implementation of the function that receives a bunch of Geometric elements and returns the sum of the perimeters----
//-------------------------------------------------------------------------------------------------------------------------------

/*
//Geometric array: //This is not needed, but I wanted to test around.
Geometric arr[] = {p, l, t, l};

for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
    if(typeid(a[i]) == typeid(LineSection)) cout << i  << endl;
    else cout << i << "No" << endl;
} 

//Geometric vector using smart pointers:
std::vector<Geometric> a;
auto b = std::make_unique<Geometric[]>();
std::unique_ptr<Geometric> c;

a.push_back(p);
a.push_back(l);
a.push_back(t);

//The following doesn't work because p, l and t are not pointers. I lose information about their type hence.
if(typeid(l) == typeid(LineSection)) cout << "Yeah"  << endl;
else cout << "No" << endl;
if(typeid(p) == typeid(LineSection)) cout << "Yeah"  << endl;
else cout << "No" << endl;
if(typeid(a[0]) == typeid(Geometric)) cout << "Yeah"  << endl;
else cout << "No" << endl; //Since a is Geometric, its elements are Geometric to this function, no longer Point or Linesection.


for(int i = 0; i < a.size(); i++){
    if(typeid(a[i]) == typeid(LineSection)) cout << i  << endl;
    else cout << i << "No" << endl;
} 

cout << a[0].getX() << endl;

//cout << sizeof(a)/sizeof(a[0]) << endl; Kinda works, but use size().
//cout << typeid(a).name()  << endl;
*/
//-------------------------------------------------------------------------------------------------------------------------------

//This is how above tentative should work:
vecGeometricElement vecGeo;

vecGeo.insertElement(CreateGeometricElement(1, Point(0, 0))); //I could yet insert Points as parameters instead of using the default.
vecGeo.insertElement(CreateGeometricElement(2, Point(0, 0), Point(0, 0)));
vecGeo.insertElement(CreateGeometricElement(3, Point(0, 0), Point(0, 0), Point(0, 0)));

cout << "Perimeter sum of Geometric elements: " << vecGeo.getPerimeterSum() << endl;

//-------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------Unit Tests-------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

auto p_ = std::make_unique<Point2>(CreateGeometricElement(1, Point(1, 1)));

vecGeo.insertElement(std::move(p_)); //No can do. (QUESTION) HOW???? (QUESTION)

//Smart way
for(int i = 0; i < vecGeo.size(); i++){
    auto bla = vecGeo.getElement(i);
    auto ele =  dynamic_cast<lengthInterface*>(bla.get()); 
    if(ele){
        if(ele->getLength() == 0) cout << "Passed." << endl;
        else cout << "Failed test." << endl;
    }
}

//Long way
//Point
Point p(1, 1), p1(0, 0), p2(1, 0), p3(0,1); //I'm not using the factory cause I don't want a pointer, I want just an instance.

if(p.getX() == 1) cout << "Passed." << endl;
else cout << "Failed test." << endl;

if(p.getY() == 1) cout << "Passed." << endl;
else cout << "Failed test." << endl;

//LineSection
LineSection l1(p1, p2), l2(p1, p1), l3(p1, p2);

if(l1.getLength() == 1) cout << "Passed." << endl;
else cout << "Failed test." << endl;

if(l2.getLength() == 0) cout << "Passed." << endl;
else cout << "Failed test." << endl;

if(l3.getLength() == 1) cout << "Passed." << endl;
else cout << "Failed test." << endl;

//Triangle
Triangle t(p1, p2, p3);

if(t.getLength() == (float)(2. + sqrt(2))) cout << "Passed." << endl; //If I don't make sqrt(2) float, it has grater precision than float. 
else cout << "Failed test." << endl;

if(t.getArea() == 0.5) cout << "Passed." << endl;
else cout << "Failed test." << endl;

//Use auto instead of unique_ptr<Geometric>, cause I'm pointing to a unique pointer of the Type Geometric already.
//auto bla = CreateGeometricElement(1, Point(5, 1)); //Yes, this works.
//Point* P =  dynamic_cast<Point*>(bla.get());
//cout << P->getX() << endl;
//Point2 p_(bla); //Doesn't work, cause I'm using unique pointer.
//Do this instead:

/*
cout << typeid(p_).name() << endl;

if(p_->getArea() == 0) cout << "Passed." << endl;
else cout << "Failed test." << endl;

if(p_->getLength() == 0) cout << "Passed." << endl;
else cout << "Failed test." << endl;
*/
//Opeator overload. 

//Haven't found Clara Maria Figueira

//LineSection l;
//std::unique_ptr<Geometric> l = ;

//Point2 bla(CreateGeometricElement(2));

//cout << bla.getLength() << endl;
LineSection _l1(Point(0, 0), Point(1, 0)), _l2(Point(0, 0), Point(1, -5));;

LineSection l4 = sumLines(_l1, _l2);

cout << l4.getLength() << endl;
cout << sqrt(29) << endl;

return 0;
} 
