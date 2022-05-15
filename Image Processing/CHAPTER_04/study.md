# CHAPTER 04. MFC를 이용한 영상처리
* **MFC 프로젝트 생성**
1. [File]-[New]-[Project] 메뉴 선택
2. [New Project] 창: [Visual C++]-[MFC Application] 선택
<br/>

## 4.1 MFC 프로그램 구조
|구조 옵션|설명|
|------|---------------------|
|Single documents(SDI)|하나의 프로그램에 하나의 창만 존재하는 구조. ex) Internet Explorer|
|Multiple documents(MDI)|프로그램 내에 여러 개의 창이나 문서를 열 수 있는 구조. 많은 응용 프로그램들이 이 구조를 사용함. ex) Photoshop|
|Dialog based|메시지박스나 이와 같은 구조를 사용하는 프로그램|

* **MDI 구성요소**
  <p align = "left">
    <img src = "https://user-images.githubusercontent.com/68229317/168479098-2c446e52-f821-4a29-9e53-16ae1acaf29f.png" width="50%">
  </p>

* **MDI 구조**

  |클래스|설명|
  |------|---------------------------------------|
  |CTestMDIApp|TestMDI 프로그램의 전체를 관리하는 클래스. 프로그램 동작 시 오직 하나의 인스턴스만 생성된다. 문서 템플릿(document template), 메인프레임 윈도우 등을 생성한다.|
  |CMainFrame|메인 프레임 윈도우의 기능을 담당. 윈도우 외각을 둘러싸는 경계로 제목 표시줄, 메뉴, 툴바, 상태바, 창의 경계 등으로 구성|
  |CChildFrame|차일드 프레임 윈도우의 기능을 담당. 제목 표시줄, 창의 경계 등으로 구성된다. 툴바 및 상태바를 추가할 수도 있다.|
  |CTestMDIDoc|데이터의 보관 및 관리를 담당. 다중 문서 인터페이스인 경우 여러 개의 인스턴스가 생성될 수 있다.|
  |CTestMDIView|차일드 프레임 윈도우 안에 존재하며 데이터의 출력을 담당.|

<br/>

## 4.2 간단한 MFC 기반 영상처리 프로그램


<br/>

## 4.3 고속 화면 출력
