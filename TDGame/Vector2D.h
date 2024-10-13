#pragma once
#include <vector>

class Vector2D {
public:
    // 构造函数
    Vector2D(float x = 0.0f, float y = 0.0f);

    Vector2D operator+(const Vector2D& vec) const;
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D operator+(float val) const;
    Vector2D& operator+=(float val);
    Vector2D operator-(const Vector2D& vec) const;
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D operator-(float val) const;
    Vector2D& operator-=(float val);
    Vector2D operator*(const Vector2D& vec) const;
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D operator*(float val) const;
    Vector2D& operator*=(float val);
    Vector2D operator/(const Vector2D& vec) const;
    Vector2D& operator/=(const Vector2D& vec);
    Vector2D operator/(float val) const;
    Vector2D& operator/=(float val);

    Vector2D& operator=(const Vector2D& v);
    Vector2D& operator-();
    bool operator==(const Vector2D& v);
    double getMode_length();
    bool about_zero();
    Vector2D normalization();//标准化

public:
    float x, y;
};

using Point = Vector2D;

class Rect {
public:
    Rect();
    Rect(Point leftUp, Point rightDown);
    Rect(float w, float h);

    float getW()const;
    float getH()const;

    Vector2D getRightUp();
    const Vector2D& getLeftUp()const;
    Vector2D getLeftDown();
    const Vector2D& getRightDown()const;
    void setRect(const Point& lp,const Point& rd);
    void setRect(const Point& pos, float w, float h);
    void setRect(Point& pos, float w,float h);

    Rect operator+(const Point& pos)const;

    void divisionAverage(Rect& r1, Rect& r2,bool x_y);//均分裁剪得到副本
    void division(Rect& r1, Rect& r2,bool x_y,float ratio);//标志ture为y与比例
    void moveTo(Point pos);

    Rect intersectingRectangle(const Rect& r);//相交矩形

    std::vector<Rect> subtract(const Rect& r);//矩形相减,可能返回多个矩形

    bool inRect(const Point& p);
    bool inRect(const  Rect& r2);

public:
    Point leftUp;
    Point rightDown;
};