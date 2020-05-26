#include <iostream>
#include <cmath>

using namespace std;

struct Point             //Структура с координатами "x" и "y"
{
    int x, y;
    Point(int x, int y)
        : x(x), y(y) {};
};


class Figure
{
private:
    Point* point = NULL;
    int tops;
public:
    Figure(int tops, Point* point)
    {
        this->tops = tops;
        this->point = point;
    }

    virtual void Name()
    {
        cout << "Фигура: " << endl;
    }

    virtual float Square()
    {
        float square = 0;
        for (int i = 0; i < tops - 1; i++)
        {
            square += 0.5 * abs(point[i].x * point[i + 1].y - point[i + 1].x * point[i].y);
        }
        square += 0.5 * abs(point[tops].x * point[0].y - point[0].x * point[tops].y);

        return square;
    }
    virtual float Perimetr()
    {
        float perimetr = 0;
        for (int i = 0; i < tops - 1; i++)
        {
            perimetr += sqrt(pow(point[i + 1].x - point[i].x, 2) + pow(point[i + 1].y - point[i].y, 2));
        }
        perimetr += sqrt(pow(point[tops - 1].x - point[0].x, 2) + pow(point[tops - 1].y - point[0].y, 2));

        return perimetr;
    }
};

class Rectangle : public Figure //класс Rectangle наследник Figure
{
private:
    int w = NULL;
    int h = NULL;
public:
    Rectangle(int h, int w) : Figure(4, new Point[4]{ Point{0,0}, Point{0,h}, Point{w,h},Point{w,0} }) //4 вершины, и сами вершины прямоуголньика
    {
        this->h = h;
        this->w = w;
    }
    void Name()
    {
        cout << "Прямоугольник" << endl;
    }
    float Square() //площадь прямоугольника
    {
        return w * h;
    }
    float Perimetr() //периметр прямоугольника
    {
        return 2 * (w + h);
    }
};

class Foursquare :public Rectangle //класс Foursquare наследник класса Rectangle
{
private:
    int a = NULL;
public:
    Foursquare(int a) :Rectangle(a, a)
    {
        this->a = a;
    }
    void Name()
    {
        cout << "Квадрат" << endl;
    }
};

class Ellipse :public Figure
{
private:
    int r = NULL;
    int R = NULL;
public:
    Ellipse(int r, int R) :Figure(4, new Point[4]{ Point{ 0,R }, Point{ -r,0 }, Point{0 ,-R },Point{r,0 } })
    {
        this->R = R;
        this->r = r;
    }
    float Square()
    {
        return 3.14 * r * R;
    }
    float Perimetr()
    {
        return 2 * 3.14 * sqrt(pow(R, 2) * pow(r, 2) / 2);
    }
    void Name()
    {
        cout << "Эллипс" << endl;
    }
};

class Circle : public Ellipse
{
private:
    int Radius = NULL;
public:
    Circle(int Radius) :Ellipse(Radius, Radius)
    {
        this->Radius = Radius;
    }
    float Perimetr()
    {
        return 2 * 3.14 * pow(Radius, 2);
    }
    void Name()
    {
        cout << "Круг" << endl;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    const int count = 100;

    Figure* figure[count];

    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
            figure[i] = new Rectangle(i, i * 2);
        else if (i % 3 == 0)
            figure[i] = new Foursquare(i);
        else if (i % 5 == 0)
            figure[i] = new Circle(i / 5);
        else
            figure[i] = new Ellipse(i / 2, i);
    }

    for (int i = 0; i < count; i++) //вывод значений
    {
        figure[i]->Name();
        cout << "Площадь = " << figure[i]->Square() << endl;
        cout << "Периметр = " << figure[i]->Perimetr() << endl;
        cout << "" << endl;
    }

    for (int i = 0; i < count; i++)  //удаление значений из динамической памяти
    {
        delete figure[i];
    }

    return 0;
}
