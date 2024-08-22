#include <iostream>
#include "../header/triangle.hpp"
#include "../header/rectangle.hpp"

using namespace std;

Rectangle R;
Triangle T;
int h = 0;
int w = 0;
int t = 0;
int b = 0;
char a;

int main () {
    cout << "Please choose a triangle or rectangle. Type T for triangle and R for rectangle." << endl;
    cin >> a;


    if (a == 'R') {
        cout << "Please enter the height of the rectangle." << endl;
        cin >> h;
        if (h < 0) {
            cout << "Invalid height value." << endl;
            return 0;
        }
        else if (cin.fail()) {
            cout << "Invalid height value" << endl;
            return 0;
        }
        else {
        R.set_height(h);
        }

        cout << "Please enter the width of the rectangle." << endl;
        cin >> w;
        if (w < 0) {
            cout << "Invalid width value." << endl;
            return 0;
        }
        else if (cin.fail()) {
            cout << "Invalid width value" << endl;
            return 0;
        }
        else {
        R.set_width(w);
        }
        cout << "Rectangle Area is: " << R.area() << endl;

    }
    else if (a == 'T') {
        cout << "Please enter the height of the triangle." << endl;
        cin >> t;
        if (t < 0) {
            cout << "Invalid height value." << endl;
            return 0;
        }
        else if (cin.fail()) {
            cout << "Invalid height value" << endl;
            return 0;
        }
        else {
        T.t_set_height(t);
        }
        cout << "Please enter the base length of the triangle." << endl;
        cin >> b;
        if (b < 0) {
            cout << "Invalid base value." << endl;
            return 0;
        }
        else if (cin.fail()) {
            cout << "Invalid base value" << endl;
            return 0;
        }
        else {
        T.t_set_base(b);
        }
        cout << "Triangle Area is: " << T.t_area() << endl;

    }
    else if ( a != 'T' || a != 'R') {
        cout << "Invalid Input" << endl;
        return 0;
    }
    


}   