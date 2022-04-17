# CHAPTER 02. PhotoShop을 이용한 영상처리

## 2.1 입출력 영상

* [File] → [Open]
  * 입력 영상 형식: BMP, GIF, JPG, RAW, EPS, TIF, PNG 등
    <p align = "left">
      <img src = "/assets/input_output_image.png" width="30%">
    </p>
* [File] → [Save As] 
  * 출력 영상 형식: BMP, GIF, JPG, RAW, EPS, TIF, PNG 등
* RAW
  * 파일의 헤더 정보(크기, color depth, 팔레트 등) 없음
    * 장점: 영상을 읽고 저장하기 편리
    * 단점: 영상의 크기정보를 미리 알아야 함
    * → 독립적으로 사용하기에 불편한 포맷
<br/>

## 2.2 히스토그램 기능
* [Image] → [Histogram]
* **`히스토그램`**: 영상의 픽셀 값 분포를 그래프의 형태로 표현한 것
  <p align = "left">
      <img src = "/assets/histogram.png" width="70%">
  </p>
  
  그레이스케일 → Luminosity 
<br/>

## 2.3 간단한 영상처리
* **이미지 확대/축소**
  * [Image] → [Image Size]
    <p align = "left">
      <img src = "/assets/image_size.png" width="50%">
    </p>
  * 양선형 보간법(Bilinear interpolation): 원본 영상에서 인접한 네 개의 픽셀 값을 이용하여 실수 좌표 상의 픽셀 값을 계산하는 방법
    <p align = "left">
      <img src = "/assets/bilinear_interpolation_1.png" width="20%">
      <img src = "/assets/bilinear_interpolation_2.png" width="20%">
    </p>
  
* **이미지 회전**
  * [Image] → [Rotate Canvas]
    <p align = "left">
      <img src = "/assets/image_rotation.png" width="50%">
    </p>
  
* **이미지 스무딩**
  * [Filter] → [Blur] → [Gaussian Blur]
    <p align = "left">
      <img src = "/assets/image_smoothing.png" width="50%">
    </p>
  
* **에지 검출**
  * [Filter] → [Stylize] → [Find Edges]
    <p align = "left">
      <img src = "/assets/edge_detection.png" width="50%">
    </p>
  
  * 에지(edge): 물체의 경계
* **노이즈 추가 및 제거**
  * [Filter] → [Noise] → [Add Noise]
  * [Filter] → [Noise] → [Despeckle] 
    <p align = "left">
      <img src = "/assets/image_noise.png" width="50%">
    </p>
  
* **Gamma Correction**
  * [Image] → [Adjust] → [Levels]
    <p align = "left">
      <img src = "/assets/gamma_correction_1.png" width="30%">
    </p>

  * 목적: 영상센서, 출력기 및 필름 등에서 발생하는 비선형적인 반응들을 보상하기 위해 수행함
  * 변환식
    <p align = "left">
      <img src = "/assets/gamma_correction_formula.png" width="20%">
    </p>
    
    * γ = 1.0 : Null 변환
    * 0.0 < γ < 1.0 : 지수곡선 → 영상을 어둡게 함
    * γ > 1.0 : 로그곡선 → 영상을 밝게 함
    <p align = "left">
      <img src = "/assets/gamma_correction_2.png" width="50%">
    </p>
    
* **히스토그램 균등화**
  * [Image] → [Adjust] → [Equalize] 
    <p align = "left">
      <img src = "/assets/histogram_equalization.png" width="50%">
    </p>
  
* **히스토그램 스트레칭**
  * [Image] → [Adjust] → [Levels]
    <p align = "left">
      <img src = "/assets/histogram_stretching.png" width="50%">
    </p>
  
* **음영상**
  * [Image] → [Adjust] → [Invert] 
    <p align = "left">
      <img src = "/assets/negative_image.png" width="50%">
    </p>
  
* **Posterize**
  * [Image] → [Adjust] → [Posterize]
    * 8-level 변환, 임계값을 이용한 변환(2-level) 등 
  * 정의: 영상에서 화소가 가질 수 있는 명암 값의 범위(# of gray levels)를 축소하는 변환
    <p align = "left">
      <img src = "/assets/posterize.png" width="50%">
    </p>
  
* **Solarize**
  * [Filter] → [Stylize] → [Solarize] 
  * 정의: 영상의 톤(tone)이 부분적으로 reverse되는 변환
    <p align = "left">
      <img src = "/assets/solarize.png" width="50%">
    </p>
  
* **컬러 성분 분석**
  * [Channels] 패널: Red/Green/Blue 채널 선택
  * **RGB 컬러 모델**
    * 빛의 삼원색(R,G,B)을 기본색으로 하는 컬러 모델
    * Additive model: 기본색을 더하여 새로운 색을 생성
    * 응용 분야: CRT 모니터, 컴퓨터 그래픽스
  * **CMY 컬러 모델**
    * Cyan(청록), Megenta(자홍), Yellow(노랑)을 기본색으로 함
    * Subtractive model: 보색을 흡수하고 나머지를 반사
    * 응용 분야: 컬러 출판, 컬러 프린터
  * **HSI(HSL, HSV) 컬러 모델**
    * 색상, 채도, 명도의 세 가지 속성을 이용
    * 인간의 시각 모델과 가장 흡사한 모델
    * 응용 분야: 색상, 명도, 채도를 각각 다루는 시스템
