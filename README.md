# BABA IS YOU clone project

## 프로젝트 소개

["BABA IS YOU"](https://namu.wiki/w/Baba%20Is%20You)를 따라서 C언어를 기반으로 하여, `<stdio.h>`, `<conio.h>`, `<Windows.h>` 라이브러리만을 사용하여 개발된 텍스트 기반 퍼즐 게임입니다. 그래픽 라이브러리를 사용하지 않고, **콘솔 터미널에서 문자를 이용해 그래픽을 표현**함으로써, 플레이어가 조작하는 문자들을 통해 게임의 규칙을 변경하며 퍼즐을 해결해 나가는 독특한 게임 메커니즘을 가지고 있습니다.
### [:link: 소개영상![Apr-05-2024 16-14-17.gif](Apr-05-2024%2016-14-17.gif)](https://www.youtube.com/watch?v=0g92GeLWkFA&t=66)
 

- [:video_game:실행파일](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbTVrbUw2dDdrQ1BERzhTNFRGN0otV3lFd0xuZ3xBQ3Jtc0trdFRTU1IyUDJ6RDdfcWxoOGVkeExCMFRvREdtSEVFZzhGUVlqV1RRTGozbTJYbGY2SW9Ua3BVUks2dWJtZTB2SmsxcUdrZFJzRjdUT0JScERDM2cxMFUtUmRJTllLak40Vnp1alV3bjE2eTRoQXpHMA&q=https%3A%2F%2Fdrive.google.com%2Ffile%2Fd%2F1naEuS60GRZw3eapNwr5DCsEkD62KOjEh%2Fview%3Fusp%3Dsharing&v=0g92GeLWkFA)

## 기능

### 조작법

- **방향키**: 캐릭터 움직이기
- **R**: 현재 레벨 초기화
- **ESC**: 레벨 나가기
- **Enter**: 레벨 선택하기

### 동작 방식
- 문장을 완성해 물체를 바꿀 수 있어요
![Apr-05-2024 16-15-12.gif](Apr-05-2024%2016-15-12.gif)

- 문장을 완성해 규칙을 만들 수 있어요
![Apr-05-2024 16-15-17.gif](Apr-05-2024%2016-15-17.gif)

### 퍼즐 승리 조건

"BABA IS YOU" 게임의 핵심은 'You'의 주어가 되는 오브젝트가 'Win'의 주어가 되는 오브젝트에 닿으면 승리하는 조건을 가집니다.
예를 들어, "BABA IS YOU", "FLAG IS WIN"이라는 규칙이 설정되면 BABA가 FLAG에 닿을 때 승리합니다. 
만약 "BABA IS YOU", "BABA IS WIN"처럼 YOU와 WIN이 같은 대상을 가리킬 경우, 게임은 즉시 승리로 끝납니다.

