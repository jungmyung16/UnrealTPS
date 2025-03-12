# TPS Project

언리얼 엔진(UE5)을 활용하여 제작한 간단한 3인칭 슈팅(TPS) 게임 프로젝트입니다. 플레이어가 적을 제거하며 다양한 미션을 수행하는 게임입니다.

## 🎯 프로젝트 개요

이 프로젝트는 플레이어가 TPS(Third Person Shooter) 시점에서 다양한 무기를 사용하여 적을 제거하고, 목표 지점에 도달하여 스테이지를 클리어하는 방식으로 구성되었습니다. 플레이어는 캐릭터를 자유롭게 조작하여 다양한 전투 상황을 극복해야 합니다.

주요 기능으로는 미니맵 기능, 플레이어를 추적하는 적 캐릭터의 AI 기능, 스나이핑 조준 기능 등이 포함되어 있습니다.

## 🛠️ 상세 프로젝트 구조

```
TPSProject
├─ Source
│   ├─ Bullet
│   │   ├─ Bullet.cpp (총알 생성, 이동, 충돌 처리)
│   │   └─ Bullet.h (총알 클래스 정의)
│
├─ Enemy
│   ├─ Enemy.cpp (적 기본 클래스 정의 및 동작 관리)
│   ├─ Enemy.h (적 캐릭터 상태 및 속성 정의)
│   ├─ EnemyFSM.cpp (적 상태 머신 로직 및 플레이어 추적 기능)
│   ├─ EnemyFSM.h (적 AI 상태 관리 정의)
│   ├─ EnemyAnim.cpp (적 애니메이션 관리)
│   ├─ EnemyAnim.h (적 캐릭터 애니메이션 정의)
│   ├─ EnemyManager.cpp (적 캐릭터 스폰 및 관리)
│   └─ EnemyManager.h (적 관리 클래스 정의)
│
├─ Player
│   ├── TPSPlayer.cpp (플레이어 메인 클래스)
│   ├── TPSPlayer.h (플레이어 상태 및 속성 관리)
│   ├── PlayerMove.cpp (플레이어 이동, 점프 및 카메라 조작)
│   ├── PlayerMove.h (플레이어 이동 관련 정의)
│   ├── PlayerFire.cpp (플레이어 무기 사용 및 조준, 스나이핑 구현)
│   ├── PlayerFire.h (공격 및 무기 교체 정의)
│   ├── PlayerAnim.cpp (플레이어 애니메이션 관리)
│   └── PlayerAnim.h (플레이어 애니메이션 상태 정의)
│
├── MiniMapWidget.cpp (미니맵 UI 구현 및 플레이어 위치 표시)
├── MiniMapWidget.h (미니맵 기능 클래스 정의)
├── MusicManager.cpp (배경음악 재생 및 사운드 관리)
├── MusicManager.h (사운드 관리 클래스 정의)
├── VictoryManager.cpp (게임 목표 및 승리 조건 관리)
├── VictoryManager.h (게임 클리어 상태 관리 정의)
├── VictoryWidget.cpp (클리어 화면 UI 관리)
└── VictoryWidget.h (게임 클리어 UI 클래스 정의)
```

## 📌 주요 파일 상세 역할

| 파일명                | 세부 역할 및 기능                                    |
| --------------------- | ---------------------------------------------------- |
| Bullet.cpp/.h         | 총알 생성 및 이동, 충돌 처리                         |
| Enemy.cpp/.h          | 적 기본 동작, 속성 및 상태 관리                      |
| EnemyFSM.cpp/.h       | 적 AI 상태 전환 및 플레이어 추적 기능                |
| EnemyAnim.cpp/.h      | 적 애니메이션 동작 및 상태 전환 처리                 |
| EnemyManager.cpp/.h   | 적의 생성 위치 설정 및 게임 내 스폰 관리             |
| TPSPlayer.cpp/.h      | 플레이어 캐릭터 상태, 체력, UI 연결                  |
| PlayerMove.cpp/.h     | 플레이어 캐릭터의 이동, 점프, 카메라 동작 관리       |
| PlayerFire.cpp/.h     | 플레이어 공격 액션, 무기 변경 및 조준, 스나이핑 구현 |
| PlayerAnim.cpp/.h     | 플레이어 움직임에 따른 애니메이션 상태 관리          |
| MiniMapWidget.cpp/.h  | 미니맵 UI 관리 및 플레이어 실시간 위치 표시          |
| MusicManager.cpp/.h   | 게임 배경음악 및 효과음 재생 관리                    |
| VictoryManager.cpp/.h | 게임 목표 달성 상태, 승리 조건 및 클리어 로직 관리   |
| VictoryWidget.cpp/.h  | 게임 클리어 시 UI 화면 출력 및 이벤트 관리           |

## 📸 게임 주요 화면

|                                                     전체 맵 화면                                                      |                                                  플레이어 전투 장면                                                   |
| :-------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------: |
| <img src="https://github.com/user-attachments/assets/173a051a-590a-4f74-ac9e-523a8683eb34" alt="Image" width="400" /> | <img src="https://github.com/user-attachments/assets/3ece17fd-ec86-4c1f-b83f-f7ba4a7758b6" alt="Image" width="400" /> |

|                                                   게임 클리어 화면                                                    |                                                    게임 오버 화면                                                     |                                                  스나이퍼 조준 화면                                                   |
| :-------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------: |
| <img src="https://github.com/user-attachments/assets/de84ef33-38f1-4900-9e04-5cffd0e61f22" alt="Image" width="400" /> | <img src="https://github.com/user-attachments/assets/f3d6d800-8575-48b3-857a-88e401b063da" alt="Image" width="400" /> | <img src="https://github.com/user-attachments/assets/ee182068-41bb-414e-85e9-ca56094031ad" alt="Image" width="400" /> |

## 🎮 조작법 안내

| 동작          | 키            |
| ------------- | ------------- |
| 이동          | WASD          |
| 점프          | 스페이스 바   |
| 달리기        | Shift         |
| 총 발사       | 마우스 좌클릭 |
| 무기 교체     | 숫자 키       |
| 스나이퍼 조준 | 마우스 우클릭 |

---

**사용된 엔진**: Unreal Engine 5  
**프로그래밍 언어**: C++

---
