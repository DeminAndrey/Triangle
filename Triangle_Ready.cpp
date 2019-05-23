#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <math.h>

//≈сть два вида команд:
//ADD Ч добавить фигуру в набор;
//PRINT Ч дл€ каждой фигуры в наборе распечатать название, периметр и площадь.

//ѕрограмма поддерживает три вида фигур: пр€моугольник, треугольник и круг. »х добавление описываетс€ так:
//ADD RECT width height Ч добавить пр€моугольник с размерами width и height (например, ADD RECT 2 3).
//ADD TRIANGLE a b c Ч добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
//ADD CIRCLE r Ч добавить круг радиуса r (например, ADD CIRCLE 5).

#define PI 3.14

using namespace std;

//базовый класс ‘»√”–ј
class Figure
{
protected:
    string name; //им€ фигуры
    double perimeter; //периметр
    double area; //площадь
public:
    virtual string Name()=0; //виртуальный метод возвращает им€ фигуры
    virtual double Perimeter()=0; //виртуальный метод возвращает периметр
    virtual double Area()=0; //виртуальный метод возвращает площадь
};

//класс “–≈”√ќЋ№Ќ» 
class Triangle: public Figure
{
protected:
    //пол€ дл€ хранени€ длин сторон треугольника
    double a;
    double b;
    double c;
public:
    Triangle(double x, double y, double z)
    {
        name="TRIANGLE";
        a=x;
        b=y;
        c=z;
        perimeter=x+y+z;
        double res=(x+y+z)/2;
        area=sqrt(res*(res-x)*(res-y)*(res-z));
    }
    string Name()
    {
        return name;
    }
    double Perimeter()
    {
        return perimeter;
    }
    double Area()
    {
        return area;
    }
};

//класс ѕ–яћќ”√ќЋ№Ќ» 
class Rect: public Figure
{
protected:
    //пол€ дл€ хранени€ длин сторон пр€моугольника
    double width;
    double height;
public:
    Rect(double x, double y)
    {
        name="RECT";
        width=x;
        height=y;
        perimeter=2*x+2*y;
        area=x*y;
    }
    string Name()
    {
        return name;
    }
    double Perimeter()
    {
        return perimeter;
    }
    double Area()
    {
        return area;
    }
};

// ласс  –”√
class Circle: public Figure
{
protected:
    double r;
public:
    Circle(double rad)
    {
        name="CIRCLE";
        r=rad;
        perimeter=2*PI*rad;
        area=PI*rad*rad;
    }
    string Name()
    {
        return name;
    }
    double Perimeter()
    {
        return perimeter;
    }
    double Area()
    {
        return area;
    }
};

//функци€ дл€ создани€ экземпл€ра класса - фигуры
shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string str;
    is>>str;
    if(str=="TRIANGLE")
    {
        int x,y,z;
        is>>x>>y>>z;
        return make_shared<Triangle>(x, y, z);
    }
    else if(str=="RECT")
    {
        int x, y;
        is>>x>>y;
        return make_shared<Rect>(x, y);
    }
    else if(str=="CIRCLE")
    {
        int rad;
        is>>rad;
        return make_shared<Circle>(rad);
    }
}


int main()
{
    //контейнер дл€ хранени€ фигур
    vector<shared_ptr<Figure>> figures;

    for (string line; getline(cin, line); )
    {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "ADD")
        {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto& current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }


    return 0;
}
