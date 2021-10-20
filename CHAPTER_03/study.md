# CHAPTER 03. OpenCV 주요 클래스

## 3.1 기본 자료형 클래스

* 픽셀의 좌표를 표현하는 [Point_ 클래스](#%ED%81%B4%EB%9E%98%EC%8A%A4)
* 사각형 영역의 크기를 표현하는 Size_ 클래스
* 사각형의 위치와 크기 정보를 나타내는 Rect_ 클래스
* 회전된 사각형을 표현하는 RotatedRect 클래스
* 범위를 표현하는 Range 클래스
* 문자열을 표현하는 String 클래스

<br/>

### 3.1.1 Point_ 클래스

`Point_ 클래스`는 2차원 평면 위에 있는 점의 좌표를 표현하는 템플릿 클래스

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

