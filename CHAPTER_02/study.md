# CHAPTER 02. OpenCV 설치와 기초 사용법

## 2.1 OpenCV 개요와 설치
`OpenCV`는 오픈 소스로 개발되고 있는 컴퓨터 비전 및 머신 러닝 라이브러리(Open Source Computer Vision Library)이다.

* **OpenCV 모듈**
  * 모듈: OpenCV에서 제공하는 다양한 클래스와 함수를 그 기능과 성격에 따라 모아서 만들어 놓은 OpenCV의 부분 라이브러리
    * OpenCV 모듈은 각각 별도의 *.lib 파일과 *.dll 파일로 만들어짐 
  * world 모듈: OpenCV 모듈을 모두 합쳐서 하나의 모듈로 재구성한 것 
<br>

> OpenCV 공식 사이트: https://opencv.org/   
> OpenCV 문서 사이트: https://docs.opencv.org/

<br>

* **OpenCV 설치하기**
  * OpenCV와 관련된 헤더 파일, LIB 파일, DLL 파일을 컴퓨터에 생성하는 작업을 의미
  * OpenCV 공식 사이트 접속 후, 상단의 RELEASES 메뉴를 클릭해서 설치 실행 파일 내려 받기
    * C:\opencv\폴더 아래에 sources 폴더와 build 폴더 생성됨
      * C:\opencv\sources 폴더: OpenCV 소스 코드 파일
      * C:\opencv\build 폴더: 소스 코드로부터 만들어진 라이브러리 파일과 헤더 파일, 기타 유용한 파일
        * C:\opencv\build\x64\cv15\bin 폴더: OpenCv 프로그램 실행 시 필여한 DLL 파일과 OpenCV 유틸리티 프로그램 저장
        * C:\opencv\build\x64\cv15\lib 폴더: OpenCV DLL 파일이 생성될 때 함께 만들어지는 import library 파일 저장
  * 시스템 환경 변수 PATH에 OpenCV DLL 파일이 있는 폴더 추가하기  

<br>

## 2.2 OpenCV 사용하기: HelloCV
* **OpenCV 프로젝트 만들기**
  * 프로젝트의 solution platform을 x64로 변경
  * OpenCV 프로젝트 속성 설정 
    <p align = "center">
      <img src = "/assets/security-3.png">
    </p>
    
* **BMP 영상의 화면 출력**
  * OpenCV에서 영상 데이터는 Mat 클래스를 이용하여 표현
    * Mat 클래스는 다양한 자료형의 행렬을 표현할 수 있는 범용 행렬 클래스
  * BMP 파일에 저장된 영상을 화면에 출력하기 위해서는
  * 영상 파일로부터 Mat 객체 생성, 생성한 Mat 객체를 화면에 출력하는 OpenCV 함수 호출

    ```c++
    #include "opencv2/opencv.hpp"
    #include <iostream>
    
    using namespace cv;
    using namespace std;
    
    int main(void)
    {
      cout << "Hello OpenCV" << CV_VERSION << endl;
    
      Mat img;
      img = cv.imread("lenna.bmp");
      
      if (img.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
      }
      
      namedWindow("image");
      imshow("image",img);
      
      waitKey();
      return 0;
     }
    ```

* **OpenCV 주요 함수**
  * `imread() 함수`: filename 영상 파일을 불러와 Mat 객체로 변환하여 반환
  * `imwrite() 함수`: Mat 객체에 저장되어 있는 영상 데이터를 파일로 저장
  * `Mat::empty() 함수`: 영상 데이터가 정상적으로 불러왔는지를 확인하기 위해 사용
  * `namedWindow() 함수`: 영상 출력을 위한 빈 창을 생성하기 위해 사용
  * `destroyWindow() 함수` 또는 `destroyAllWindows() 함수`: 각각 하나의 창을 닫을 때, 열려 있는 모든 창을 닫을 때 사용
  * `movedWindow() 함수`: 창 위치를 변경하는 함수
  * `resizeWindow() 함수`: 창의 크기를 변경하고 싶을 때 사용
    * WINDOW_AUTOSIZE 플래그를 사용하여 만들어진 영상 출력 창에는 크기 변경 불가 
  * `imshow() 함수`: Mat 클래스 객체에 저장된 영상 데이터를 화면에 출력
  * `waitKey() 함수`: 사용자로부터 키보드 입력을 받는 용도로 사용
    * 그리기 이벤트를 처리하는 기능도 수행 → 대부분의 OpenCV 소스코드에서 imshow() 함수와 waitKey() 함수를 연속하여 호출하는 형태로 사용
