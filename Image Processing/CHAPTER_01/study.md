# CHAPTER 01. 디지털 영상처리의 개념
> **`영상처리`** 란 디지털 영상을 특정 목적에 맞게 조작하는 기술에 대한 총칭
- 영상 개선: 영상의 화질 개선
- 영상 복원: 왜곡된 영상을 원래의 영상으로 복원
- 영상 분할: 객체와 배경의 분리
- 영상 분석: 영상으로부터 유용한 정보 추출
- 영상 합성: 새로운 영상의 합성
- 영상 압축: 영상의 중복된 내용 제거
- 영상 인식: 영상 안의 관심 있는 객체 인식
<br/>

> **`디지털 영상처리`** 란 사진 정보(아날로그 정보)를 "디지털 정보"로 변환, 디지털 컴퓨터에서 영상의 화질 강화나 변형을 수행하는 처리내용
- 입력/출력: 디지털 영상
<br/>

## 1.1 디지털 영상데이터의 흐름
* **영상 획득 세부 과정**
  <p align = "left">
      <img src = "/assets/image_data_flow.png">
  </p>

<br/>

## 1.2 디지털 영상의 내부
* **영상 데이터**
  * 형태: 2차원 배열 N x M, (N, M = 128, 256, 512)
  * Pixel(화소): picture element, 영상의 기본단위
    <p align = "left">
      <img src = "/assets/image_data_1.png" width="30%">
    </p>
    <p>
        <img src = "/assets/image_data_2.png" width="20%" align="top">
        <img src = "/assets/image_data_3.png" width="20%">
    </p>
                                                     
  * **Gray-scale 영상**
    * 각 픽셀값: 0(black) ~ 255(white)
    * 각 픽셀당 8 bit
    * N x M 흑백 영상의 크기 = N x M x 8 (bits) 
  * **Color 영상**
    * 각 픽셀값: R, G, B
      * R: 0 ~ 255
      * G: 0 ~ 255
      * B: 0 ~ 255
    * N x M 흑백 영상의 크기 = N x M x 8 x 3 (bits) 
<br/>

* **Addressing 방법**
  * ✅ **Row-major ordering**
    * Row-major ordering: A[row][col]:: offset = row * NUMCOLS + col
    * A[y][x] = A[y * W + x]
  * **Column-major ordering**
    * Column-major ordering: A[row][col]:: offset = col * NUMROWS + row
      * A[y][x] = A[x * H + y] 
<br/>

## 1.3 디지털 영상처리의 특징
- **정확성**
  - 디지털 데이터에 대한 컴퓨터에 의한 처리이므로 정확
- **재현성**
  - 정해진 알고리즘 적용, 같은 데이터에 대해 같은 결과가 얻어짐
- **제어가능성**
  - 동일 디지털 데이터에 대하여 다양한 알고리즘 적용, 서로 다른 처리 가능 
<br/>

## 1.4 디지털 영상처리의 응용분야
- DIP(Document Image Processing); 문서 이미지 처리
- 의료용 영상처리
- 위성사진의 처리
- FA용 영상처리
- 방송, 영화에서의 영상처리
- 자동 영상 인덱싱
- 고화질의 영상압축 및 통신
