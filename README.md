# 2025 - 2 융합전공 캡스톤 디자인 개인 프로젝트

---

1. 장르
   - TPS 싱글 플레이 게임
2. 개발 기간
   - 2025.09.04 ~
3. 사용 툴
   - Unreal Engine 5.5
   - Visual Studio 2022
   - C++

---
## 2025.09.11
- Enhanced Input & ABP Setup (향상된 입력 및 애님 블루프린트 셋업)

## 2025.09.15
- Commit : Line Tracing & Spawn Niagara (라인 트레이싱 수행, 나이아가라 스폰)

## 2025.09.21
- Play Fire Sound (사격 사운드 추가, 적 캐릭터 추가)

## 2025.09.23
- Create Health Component, Apply Damage & AnyDamage (체력 액터 컴포넌트 추가, 적 캐릭터에 대해 Apply Damage, Any Damage 구현)

## 2025.09.25
- GameMode & PlayerController Setup, Break Constraint (게임 모드에서 캐릭터 사망 처리, 플레이어 컨트롤러에서 사망 여부에 따른 플레이어 입력 처리, 사망 시 본 분리로 로봇의 특성 연출)

## 2025.09.27
- Revise Character Died Logic (캐릭터 사망 처리를 델리게이트를 사용하여 로직변경. 약한결합으로 코드 리팩토링)

## 2025.09.29
- Add CameraShake (블루프린트 내 카메라 쉐이크 추가 및 공격 시 카메라 쉐이크 시작 적용)

## 2025.10.02
- AI Move (블랙보드 기반 태스크, 비헤이비어 트리, AI Controller 작업)

## 2025.10.09
- AI Attack Logic (AIController 를 통한 시각,청각,데미지 감각 셋업, 공격 로직 작성)

## 2025.10.15
- Enemy Fire & Spawn Bullet (태스크를 활용한 적 공격 AI 구현, 델리게이트와 타이머 핸들을 활용하여 총알 스폰)

## 2025.10.28
- Bullet Destroy & Apply Damage (총알 피격 시 삭제 및 Apply Damage)

## 2025.11.04
- Enemy Rotate Bug (적 사격 시, 플레이어 방향으로 회전하지 않는 버그 수정)
- Bullet Spread & Angle Interpolation (탄착군이 벌어지도록 수정, 플레이어에게 사격 시 각도가 안맞던 문제 수정 및 보간)

## 2025.11.06
- Dynamic Crosshair (동적 크로스헤어 구현)

## 2025.11.14
- Create Health Widget (플레이어 체력 바 위젯 구현)
