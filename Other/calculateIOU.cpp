#include <iostream>
using namespace std;

struct Box
{
    double x1, x2, y1, y2;

    // assert x1<=x2, y1<=y2
    Box(double a, double b, double c, double d) : x1(a), x2(b), y1(c), y2(d)
    {
        cout << "en" << endl;
    }
};

double calculateIOU(const Box &box1, const Box &box2)
{
    double insecArea = 0;

    double X1 = max(box1.x1, box2.x1);
    double X2 = min(box1.x2, box2.x2);
    double Y1 = max(box1.y1, box2.y1);
    double Y2 = min(box1.y2, box2.y2);

    insecArea = max(0.0, X2 - X1) * max(0.0, Y2 - Y1);

    double Area1 = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
    double Area2 = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);

    return insecArea / (Area1 + Area2 - insecArea);
}

int main()
{
    Box box1(1, 2, 3, 4);
    Box box2(1, 2, 3, 5);

    cout << calculateIOU(box1, box2) << endl;
    return 0;
}