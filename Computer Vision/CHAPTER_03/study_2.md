# CHAPTER 03. OpenCV 주요 클래스 (2)

## 3.2 Mat 클래스
* [3.2.1 Mat 클래스 개요](#321-mat-%ED%81%B4%EB%9E%98%EC%8A%A4-%EA%B0%9C%EC%9A%94)
* [3.2.2 행렬의 생성과 초기화]()
* [3.2.3 행렬의 복사]()
* [3.2.4 부분 행렬 추출]()
* [3.2.5 행렬의 원소 값 참조]()
* [3.2.6 행렬 정보 참조하기]()
* [3.2.7 행렬 연산]()
* [3.2.8 크기 및 타입 변환 함수]()

<br/>

### 3.2.1 Mat 클래스 개요
`Mat 클래스`는 행렬(matrix)을 표현하는 클래스로 OpenCV에서 가장 많이 사용하는 클래스 
* 일반적인 2차원 행렬뿐만 아니라 고차원 행렬을 표현할 수 있으며, 한 개 이상의 채널을 가질 수 있다.
* 정수, 실수, 복소수 등으로 구성된 행렬 또는 벡터를 저장할 수 있다.
* 그레이스케일 또는 컬러 영상을 저장할 수 있다.
* 경우에 따라서 벡터 필드, 포인트 클라우드, 텐서, 히스토그램 등 정보를 저장하는 용도로 사용한다.   

⇒ 실제적으로는 2차원 영상 데이터를 저장하고 처리하는 용도로 가장 많이 사용되고 있다.

```c++
class Mat
{
public:
  Mat();
  Mat(int rows, int cols, int type);
  Mat(Size size, int type);
  Mat(int rows, int cols, int type, const Scalar& s);
  Mat(Size size, int type, const Scalar& s);
  Mat(const Mat& m);
  ~Mat();
 
  void create(int rows, int cols, int type);
  bool empty() const;
 
  Mat clone() const;
  void copyTo(OutputArray m) const;
  Mat& setTo(InputArray value, InputArray mask=noArray());
 
  static MatExpr zeros(int rows, int cols, int type);
  static MatExpr ones(int rows, int cols, int type);
 
  Mat& operator = (const Mat& m);
  Mat operator() (const Rect& roi) const;
 
  template<typename _Tp> _Tp* ptr(int i0 = 0);
  template<typename _Tp> _Tp& at(int row, int col);
 
  int dims;
  int rows, cols;
  uchar* data;
  MatSize size;
  ···
};
```

* `깊이`: Mat 클래스에서 행렬이 어떤 자료형을 사용하는지에 대한 정보   
* `채널`: Mat 행렬 원소를 구성하는 각각의 값   
  * 그레이스케일 영상은 1채널 행렬, 트루컬러 영상은 3채널 행렬로 표현
* `타입`: Mat 행렬의 깊이 정보 + 채널 수 정보   
  * CV_<bit-depty>{U|S|F}C(<number_of_channels>)
