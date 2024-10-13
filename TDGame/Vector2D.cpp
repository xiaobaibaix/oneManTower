#include "Vector2D.h"
#include <algorithm>

// 构造函数
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

// 加法操作符重载
Vector2D Vector2D::operator+(const Vector2D& vec) const {
    return Vector2D(x + vec.x, y + vec.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2D Vector2D::operator+(float val) const {
    return Vector2D(x + val, y + val);
}

Vector2D& Vector2D::operator+=(float val) {
    x += val;
    y += val;
    return *this;
}

// 减法操作符重载
Vector2D Vector2D::operator-(const Vector2D& vec) const {
    return Vector2D(x - vec.x, y - vec.y);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2D Vector2D::operator-(float val) const {
    return Vector2D(x - val, y - val);
}

Vector2D& Vector2D::operator-=(float val) {
    x -= val;
    y -= val;
    return *this;
}

// 乘法操作符重载
Vector2D Vector2D::operator*(const Vector2D& vec) const {
    return Vector2D(x * vec.x, y * vec.y);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Vector2D Vector2D::operator*(float val) const {
    return Vector2D(x * val, y * val);
}

Vector2D& Vector2D::operator*=(float val) {
    x *= val;
    y *= val;
    return *this;
}

// 除法操作符重载
Vector2D Vector2D::operator/(const Vector2D& vec) const {
    return Vector2D(x / vec.x, y / vec.y);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
    x /= vec.x;
    y /= vec.y;
    return *this;
}

Vector2D Vector2D::operator/(float val) const {
    return Vector2D(x / val, y / val);
}

Vector2D& Vector2D::operator/=(float val) {
    x /= val;
    y /= val;
    return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& v)
{
    if (this != &v) {
        this->x = v.x;
        this->y = v.y;
    }
    return *this;
}

Vector2D& Vector2D::operator-()
{
    x = -x;
    y = -y;
    return *this;
}

bool Vector2D::operator==(const Vector2D& v)
{
    if (this->x == v.x && this->y == v.y)return true;
    return false;
}

double Vector2D::getMode_length()
{
    return sqrt(x*x+y*y);
}

bool Vector2D::about_zero()
{
    if (this->getMode_length() <= 0.01)return true;
    return false;
}

Vector2D Vector2D::normalization()
{
    return Vector2D(this->x/abs(this->x),this->y/abs(this->y));
}

Rect::Rect():
    leftUp((0,0)),
    rightDown((0, 0))
{

}

Rect::Rect(Point leftUp, Point rightDown):
    leftUp(leftUp),
    rightDown(rightDown)
{

}

Rect::Rect(float w, float h) :
    leftUp(Vector2D(0, 0)),
    rightDown(w,h)
{

}

float Rect::getW()const
{
    return (rightDown - leftUp).x;
}

float Rect::getH()const
{
    return (rightDown - leftUp).y;
}

Vector2D Rect::getRightUp()
{
    return Vector2D(rightDown.x,leftUp.y);
}

const Vector2D& Rect::getLeftUp()const
{
    return leftUp;
}

Vector2D Rect::getLeftDown()
{
    return Vector2D(leftUp.x,rightDown.y);
}

const Vector2D& Rect::getRightDown()const
{
    return rightDown;
}

void Rect::setRect(const Point& lp, const Point& rd)
{
    leftUp = lp;
    rightDown = rd;
}

void Rect::setRect(const Point& pos, float w, float h)
{
    leftUp = pos;
    rightDown = pos + Point(w, h);
}

Rect Rect::operator+(const Point& pos)const
{
    Point lu=leftUp + pos;
    Point rd=rightDown + pos;
    return Rect(lu, rd);
}


void Rect::divisionAverage(Rect& r1, Rect& r2, bool flag)
{
    division(r1,r2,flag,0.5);
}

void Rect::division(Rect& r1, Rect& r2, bool x_y, float ratio)
{
    float w, h;
    if (x_y) {//y裁剪
        w = this->getW();
        h = this->getH() * ratio;
        r2.setRect(this->getLeftUp() + Vector2D(0, h), w, this->getH()-h);
    }
    else {//x裁剪
        w = this->getW() * ratio;
        h = this->getH();
        r2.setRect(this->getLeftUp() + Vector2D(w, 0), this->getW()-w, h);
    }
    r1.setRect(this->getLeftUp(), w, h);
}

void Rect::moveTo(Point pos)
{
    leftUp = pos;
    rightDown = pos;
}

Rect Rect::intersectingRectangle(const Rect& r)
{
    float x=std::max(leftUp.x,r.leftUp.x);
    float y=std::max(leftUp.y,r.leftUp.y);

    float w = std::min(rightDown.x, r.rightDown.x) - x;
    float h = std::min(rightDown.y, r.rightDown.y) - y;

    if (w < 0)w = 0;
    if (h < 0)h = 0;

    return Rect(Point(x, y),Point(x+w,y+h));
}

std::vector<Rect> Rect::subtract(const Rect& r)
{
    Rect _r = intersectingRectangle(r);
    std::vector<Rect> rects;

    if (_r.getW() == 0 && _r.getH() == 0)return rects;

    float x1 = getLeftUp().x;
    float y1 = getLeftUp().y;
    float x2 = getRightDown().x;
    float y2 = getRightDown().y;

    float _x1 = _r.getLeftUp().x;
    float _y1 = _r.getLeftUp().y;
    float _x2 = _r.getRightDown().x;
    float _y2 = _r.getRightDown().y;

    /*x1, y1, x2, y2 = rect
        ix1, iy1, ix2, iy2 = intersection

        remaining_rects = []

        # 上方矩形
        if iy1 > y1:
    remaining_rects.append((x1, y1, x2, iy1))
        # 下方矩形
        if iy2 < y2:
    remaining_rects.append((x1, iy2, x2, y2))
        # 左侧矩形
        if ix1 > x1:
    remaining_rects.append((x1, max(y1, iy1), ix1, min(y2, iy2)))
        # 右侧矩形
        if ix2 < x2:
    remaining_rects.append((ix2, max(y1, iy1), x2, min(y2, iy2)))*/

    if (_y1>y1) {
        rects.push_back(Rect(Point(x1, y1), Point(x2, _y1)));
    }
    if (_y2<y2) {
        rects.push_back(Rect(Point(x1, _y2), Point(x2, y2)));
    }
    if (_x1 > x1) {
        rects.push_back(Rect(Point(x1, std::max(y1,_y1)), Point(_x1, std::min(y2,_y2))));
    }
    if (_x2 < x2) {
        rects.push_back(Rect(Point(_x2, std::max(y1, _y1)), Point(_x2, std::min(y2, _y2))));
    }

    return rects;
}

bool Rect::inRect(const Point& p)
{
    return p.x>= leftUp.x&&p.y>= leftUp.y&&p.x<= rightDown.x&&p.y<= rightDown.y;
}

bool Rect::inRect(const Rect& r2)
{
    return  this->inRect(r2.getLeftUp()) &&this->inRect(r2.getRightDown());
}
