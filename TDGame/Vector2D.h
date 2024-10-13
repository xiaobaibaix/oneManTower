#pragma once
#include <vector>

class Vector2D {
public:
    // ���캯��
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
    Vector2D normalization();//��׼��

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

    void divisionAverage(Rect& r1, Rect& r2,bool x_y);//���ֲü��õ�����
    void division(Rect& r1, Rect& r2,bool x_y,float ratio);//��־tureΪy�����
    void moveTo(Point pos);

    Rect intersectingRectangle(const Rect& r);//�ཻ����

    std::vector<Rect> subtract(const Rect& r);//�������,���ܷ��ض������

    bool inRect(const Point& p);
    bool inRect(const  Rect& r2);

public:
    Point leftUp;
    Point rightDown;
};