# CHAPTER 03. 쉽게 구현하는 영상처리
* **개요**
  * 영상 처리에 특정 언어를 사용할 이유 X
* **Visual C++을 사용하는 이유**
  * Window 프로그램 작성 용이
  * 영상 처리 알고리즘을 한 프로그램에 통합 용이
<br/>

## 3.1 Visual-C++ 프로젝트 만들기
1. [File]-[New]-[Project] 메뉴 선택
2. [New Project] 창: [Visual C++]-[Empty Project] 선택
3. [Solution Explorer] 창: [Source Files] 폴더의 컨텍스트 메뉴에서 [Add]-[New Item] 선택 → C++ 파일 추가
4. 소스 코드 입력
<br/>

## 3.2 간단한 영상처리 코드 입력
* **RAW 파일 사용의 문제점**
  * 영상의 크기를 알 수 X
  * Color depth를 알 수 X
    * 컬러영상인지 흑백영상인지 알 수 없음
    * 컬러영상이라면 사용하는 컬러의 수가 몇 개인지의 정보도 알 수 없음

* **VC++ 프로젝트 관련 파일**
  * `sln`: 솔루션 파일
  * `vcxproj`: 프로젝트 파일
  * `cpp`: C++ 소스파일, `h`: C++ 헤더 파일
  * `pch.cpp`, `pch.h`: pre-compiled source/header 파일
  * `raw`: 데이터 파일
<br/>

## 3.3 비트맵에 대한 소개
* **컴퓨터 그래픽**
  * ✅ **비트맵 그래픽**
    * 픽셀의 2D 행렬로 구성: 픽셀의 밝기나 색을 숫자로 표시
    * 사진이나 사실적인 그림을 정교하게 표현하는 데 적합
    * 데이터 양이 많고, 확대/축소가 자유롭지 X → 데이터 손상 때문
  * **벡터 그래픽**
    * 기하학적인 개체(선, 원, 다각형)의 조합으로 영상정보를 표현
    * 데이터 양이 적고, 확대/축소가 자유로움
    * 정교한 묘사에 제한이 있음

* **비트맵(Bitmap)**
  * **종류**
    * **DDB(Device Dependent Bitmap)**
      * 장치가 직접 처리할 수 있는 비트맵: 비트맵을 이루는 픽셀의 형식과 배열이 장치와 동일
        * 장치가 가지고 있는 부가적인 정보(팔레트, 픽셀 포맷 등)를 따로 보관X
      * 출력 장치의 설정에 따라 출력이 다르게 나타나는 비트맵 → 특정 장치에 종속
    * ✅ **DIB(Device Independent Bitmap)**
      * 장치와 상관없이 비트맵을 출력하는데 필요한 모든 정보(팔레트, 픽셀 포맷 등)를 가지고 있는 비트맵
      * 출력장치가 달라지더라도 항상 정상적인 형태로 출력되는 비트맵

  * **컬러 모드**
    <p align = "left">
      <img src = "/assets/bmp_color_mode.png" width="50%">
    </p>
    
    * **트루(true) 컬러 이미지**
      * R,G,B 각각 8비트씩 → 한 픽셀당 3바이트(24비트) 사용
    * **인덱스(indexed) 이미지**
      * 픽셀에 컬러 값이 저장되는 것이 아니라, 팔레트(=컬러테이블) 번호를 가리키는 인덱스가 저장됨
      * 영상 데이터 저장 공간의 절약
    * **Gray-scale 이미지**
      * Indexed 컬러 이미지의 특별한 경우 (= RGB 컬러 값이 모두 동일)
      * 저장된 인덱스가 밝기 값이 됨

  * **Raw/DIB 파일 형식 비교**
    <p align = "left">
      <img src = "/assets/raw_dib_format.png" width="45%">
    </p>
    
<br/>

## 3.4 비트맵 포맷의 구조
* **헤더 구조체 변수들**
  <p align = "left">
    <img src = "/assets/bmp_format.png" width="40%">
  </p>
  
  <br/>
  
* **BITMAPFILEHEADER**
  * 비트맵 파일에 대한 정보 저장
  
    ```c++
    typedef struct tagBITMAPFILEHEADER 
    {
       WORD bfType;  // “BM”이라는 값 저장
       DWORD bfSize;  // 전체 파일 크기 (바이트 단위)
       WORD bfReserved1;  // Reserved (예약된 변수)
       WORD bfReserved2;  // Reserved (예약된 변수)
       DWORD bfOffBits;  // 영상데이터 위치까지의 거리
    } BITMAPFILEHEADER;
    ```
    
* **BITMAPINFOHEADER**
  * 비트맵 영상에 대한 정보 저장
  
    ```c++
    typedef struct tagBITMAPINFOHEADER
    {
       DWORD biSize;  // 이 구조체의 크기
       LONG biWidth;  // 영상의 폭(픽셀 단위)
       LONG biHeight;  // 영상의 높이
       WORD biPlanes;  // 비트 플레인 수 (항상 1)
       WORD biBitCount  // 픽셀당 비트수 (컬러, 흑백 구별)
       DWORD biCompression;  // 압축 유무
       DWORD biSizeImage;  // 영상의 크기
       LONG biXPelsPerMeter;  // 가로 해상도
       LONG biYPelsPerMeter;  // 세로 해상도
       DWORD biClrUsed;  // 팔레트의 색깔 수 (실제 사용 색상 수)
       DWORD biClrImportant;  // 비트맵 표시에 반드시 필요한 색깔 수 (중요한 색상 인덱스)
    } BITMAPINFOHEADER; 
    ```

* **RGBQUAD**
  * 팔레트 정보 저장
  * RGBQUAD 구조체의 배열은 트루컬러 비트맵에서는 존재하지 X
  * Gray-scale 비트맵의 경우, (0, 0, 0, 0)~(255, 255, 255, 0) 이 차례대로 저장됨
  
    ```c++
    typedef struct tagRGBQUAD
    {
       BYTE rgbBlue;  // B 성분
       BYTE rgbGreen;  // G 성분
       BYTE rgbRed;  // R 성분
       BYTE rgbReserved;  // Reserved (예약된 변수)
    } RGBQUAD;
    ```
  <br/>
  
* **DIB 사용 시 주의점**
  * **픽셀 데이터**
    * Gray-sclae 비트맵: RGBQUAD 배열의 인덱스 저장
    * 트루 컬러 비트맵: (B, G, R) 순서로 픽셀 값 저장
    * 영상의 가로 길이는 4 바이트의 배수로 저장됨
      * 즉, 흑백 영상 3 x 3 은 4 x 3 크기로, 78 x 60 은 80 x 60 크기로 저장됨
        
        ```c++
        #define WIDTHBYTES(bits) (((bits)+31)/32*4) 
        호출시: rwsize = WIDTHBYTES(biBitCount*biWidth) 
        ```
      
    * 상하가 뒤집힌 상태로 저장 (bottom-up)
      ```c++
      for (i = 0; i < biHeight; i++)
      {
         for(j = 0; j < biWidth; j++)
         {
            GrayImg[i*biWidth+j] = lpMem[(biHeight-i-1)*rwsize+j]
         }
      }
      ```
