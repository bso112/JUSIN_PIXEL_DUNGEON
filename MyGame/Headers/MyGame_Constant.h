#pragma once

BEGIN(MyGame)

const unsigned int		g_iWinCX = 1280;
const unsigned int		g_iWinCY = 720;
//#define MYDEBUG

#define TILECX 25
#define TILECY 25
#define WORLDX 400
#define WORLDY 400
//레벨 최대 층수
#define MAX_DEPTH 3


#define OBJ_NOEVENT 0
#define OBJ_CLICKED 1

enum SCENEID { SCENE_STATIC, SCENE_MENU, SCENE_LOADING, SCENE_CHARACTER_SELECT, SCENE_EDITOR, SCENE_STAGE, SCENE_END };
enum TIER { TIER_COMMON, TIER_RARE, TIER_LAGEND, TIER_END };
enum BODYPART { BODY_HAND, BODY_TORSO, BODY_FINGER, BODY_ARTEFACT, BODY_END };

#define TURN_NOEVENT	98
#define TURN_END		99

#define AC_DROP			L"버린다"
#define AC_THROW		L"던진다"
#define AC_EAT			L"먹는다"
#define AC_DRINK		L"마신다"
#define AC_EQUIP		L"장착한다"
#define AC_UNEQUIP		L"해제한다"
#define AC_READ			L"읽는다"
#define AC_ZAP			L"사용한다"
#define AC_PLANT		L"심는다"
#define MSG_WIN(OTHER)	 new wstring(L"당신은 " + wstring(OTHER) + L" 을(를) 쓰려뜨렸다!")
#define MSG_DAMAGE(OTHER, DAMAGE) new wstring(wstring(OTHER) + L"은(는) " + wstring(DAMAGE) + L"데미지를 받았다.")
#define MSG_PICK(OTHER)	 new wstring(L"당신은 " + wstring(OTHER) + L" 을(를) 얻었다.")
#define MSG_EAT(OTHER)	 new wstring(L"당신은 " + wstring(OTHER) + L" 을(를) 먹었다. 아주 맛있었다!")
#define MSG_EXHAUST(OTHER) new wstring(L"아무일도 일어나지 않았다. " + wstring(OTHER) + L" 을(를) 다 써버린듯 하다.")


#define COLOR_ORANGE	0xFFFF7F00
#define COLOR_YELLOW	0xFFF5E942
#define COLOR_GREEN		0xFF00FF1A
#define COLOR_RED		0xFFFF0000


END