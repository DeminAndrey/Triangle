#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <math.h>

//���� ��� ���� ������:
//ADD � �������� ������ � �����;
//PRINT � ��� ������ ������ � ������ ����������� ��������, �������� � �������.

//��������� ������������ ��� ���� �����: �������������, ����������� � ����. �� ���������� ����������� ���:
//ADD RECT width height � �������� ������������� � ��������� width � height (��������, ADD RECT 2 3).
//ADD TRIANGLE a b c � �������� ����������� �� ��������� a, b � c (��������, ADD TRIANGLE 3 4 5).
//ADD CIRCLE r � �������� ���� ������� r (��������, ADD CIRCLE 5).

#define PI 3.14

using namespace std;

//������� ����� ������
class Figure
{
protected:
    string name; //��� ������
    double perimeter; //��������
    double area; //�������
public:
    virtual string Name()=0; //����������� ����� ���������� ��� ������
    virtual double Perimeter()=0; //����������� ����� ���������� ��������
    virtual double Area()=0; //����������� ����� ���������� �������
};

//����� �����������
class Triangle: public Figure
{
protected:
    //���� ��� �������� ���� ������ ������������
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

//����� �������������
class Rect: public Figure
{
protected:
    //���� ��� �������� ���� ������ ��������������
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

//����� ����
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

//������� ��� �������� ���������� ������ - ������
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
    //��������� ��� �������� �����
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
