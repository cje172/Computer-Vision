# CHAPTER 03. OpenCV 주요 클래스 (1)

## 3.1 기본 자료형 클래스

* 픽셀의 좌표를 표현하는 [Point_ 클래스](#311-point_-%ED%81%B4%EB%9E%98%EC%8A%A4)
* 사각형 영역의 크기를 표현하는 [Size_ 클래스](#312-size_-%ED%81%B4%EB%9E%98%EC%8A%A4)
* 사각형의 위치와 크기 정보를 나타내는 [Rect_ 클래스](#313-rect_-%ED%81%B4%EB%9E%98%EC%8A%A4)
* 회전된 사각형을 표현하는 [RotatedRect 클래스](#314-rotatedrect-%ED%81%B4%EB%9E%98%EC%8A%A4)
* 범위를 표현하는 [Range 클래스](#315-range-%ED%81%B4%EB%9E%98%EC%8A%A4)
* 문자열을 표현하는 [String 클래스](#316-string-%ED%81%B4%EB%9E%98%EC%8A%A4)

<br/>

### 3.1.1 Point_ 클래스

`Point_ 클래스`는 2차원 평면 위에 있는 점의 좌표를 표현하는 템플릿 클래스   
→ 2차원 좌표를 나타내는 x와 y라는 이름의 멤버 변수를 가진다.

```c++
template<typename _Tp> class Point_
{
public:
  Point_();
  Point_(_Tp _x, _Tp _y);
  Point_(const Point_& pt);
  
  Point_& operator = (const Point_& pt);
  
  _Tp dot(const Point_& pt) const;
  double ddot(const Point_& pt) const;
  double cross(const Point_& pt) const;
  bool inside(const Rect_<_Tp>& r) const;
  ···
  
  _Tp x, y;
};

typedef Point_<int> Point2i;
typedef Point_<int64> Point2l;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;
```

### 3.1.2 Size_ 클래스
`Size_ 클래스`는 영상 또는 사각형 영역의 크기를 표현하는 템플릿 클래스   
→ 사각형 영역의 가로와 세로 크기를 나타내는 width와 height 멤버 변수를 가진다.

```c++
template<typename _Tp> class Size_
{
public:
  Size_();
  Size(_Tp _width, _Tp _height);
  Size(cosnt Size_& sz);
  
  Size_& operator = (const Size_& sz);
  
  _Tp area() const;
  bool empty() const;
  
  _Tp width, height;
};

typedef Size_<int> Size2i;
typedef Size_<int64> Size2l;
typedef Size_<float> Size2f;
typedef Size_<double> Size2d;
typedef Size2i Size;
```

### 3.1.3 Rect_ 클래스
`Rect_ 클래스`는 사각형의 위치와 크기 정보를 표현하는 템플릿 클래스   
→ 사각형의 좌측 상단 점의 좌표를 나타내는 x, y 멤버 변수와 사각형의 가로 및 세로 크기를 나타내는 width, height 멤버 변수를 가진다.

```c++
template<typename _Tp> class Rect_
{
public:
  Rect_();
  Rect_(_Tp _x, _Tp _y);
  Rect_(const Rect_& r);
  Rect_(const Point_<_Tp>& org, const Size_<_Tp>& sz);
  Rect_(const Point_<_Tp>& pt1, const Point_<_Tp>& pt2);
  
  Rect_& operator = (const Rect_& r);
  
  Point_<_Tp> t1() const;
  Point_<_Tp> br() const;
  Size_<_Tp> size() const;
  _Tp area() const;
  bool empty() const;
  bool contains(const Point_<_Tp>& pt) const;
  
  _Tp x, y, width, height;
};

typedef Rect_<int> Rect2i;
typedef Rect_<float> Rect2f;
typedef Rect_<double> Rect2d;
typedef Rect2i Rect;
```

### 3.1.4 RotatedRect 클래스
`RotatedRect 클래스`는 회전된 사각형을 표현하는 클래스   
→ 회전된 사각형의 중심 좌표를 나타내는 center, 사각형의 가로 및 세로 크기를 나타내는 size, 회전 각도 정보를 나타내는 angle을 멤버 변수로 가진다.

```c++
class RotaedRect
{
public:
  RotatedRect();
  RotatedRect(const Point2f& _center, const Size2f& _size, float _angle);
  RotatedRect(const Point2f& _point1, const Point2f& _point2, const Point2f& _point3);
  
  void points(Point2f pts[]) const;
  Rect boundingRect() const;
  Rect_<float> boundingRect2f() const;
  
  Point2f center;
  Size2f size;
  float angle;
};
```

### 3.1.5 Range 클래스
`Range 클래스`는 범위 또는 구간을 표현하는 클래스
→ 범위의 시작과 끝을 나타내는 start와 end 멤버 변수를 가진다.

```c++
class Range
{
public:
  Range();
  Range(int _start, int _end);
  
  int size() const;
  bool empty() const;
  static Range all();
  
  int start, end;
};
```

### 3.1.6 String 클래스
`String 클래스`는 문자열을 저장하고 처리하는 클래스   
→ c++ 표준 라이브러리의 std::string 클래스를 String 클래스로 이름 재정의 ⇒ OpenCV 4.0 버전부터 std::string 클래스와 String 클래스는 완전히 같은 클래스

* OpenCV 제공 함수
```c++
> String format(const char* fmt, ...);
  * fmt : 형식 문자열
  * ... : 가변 인자
  * 반환값 : 지정한 형식으로 생성된 문자열
```
