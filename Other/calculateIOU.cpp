#include <iostream>
using namespace std;
struct Point
{
    double x, y;
    Point(double a, double b) : x(a), y(b) {}
};

struct Box
{
    Point TL, BR;
    Box(double a, double b, double c, double d) : TL(a, b), BR(c, d) {}
};

double calculateIOU(const Box &box1, const Box &box2)
{
    double insecArea = 0;

    double X1 = max(box1.TL.x, box2.TL.x);
    double X2 = min(box1.BR.x, box2.BR.x);
    double Y1 = max(box1.TL.y, box2.TL.y);
    double Y2 = min(box1.BR.y, box2.BR.y);

    insecArea = max(0.0, X2 - X1) * max(0.0, Y2 - Y1);

    double Area1 = (box1.BR.x - box1.TL.x) * (box1.BR.y - box1.TL.y);
    double Area2 = (box2.BR.x - box2.TL.x) * (box2.BR.y - box2.TL.y);

    return insecArea / (Area1 + Area2 - insecArea);
}

int main()
{
    Box box1(1.0, 2.0, 3.0, 4.0);
    Box box2(1.0, 2.0, 3.0, 5.0);

    cout << calculateIOU(box1, box2) << endl;
    return 0;
}