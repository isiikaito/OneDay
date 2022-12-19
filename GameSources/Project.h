/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#endif



#include "ProjectShader.h"
#include "ProjectBehavior.h"
#include "Scene.h"
#include "GameStage.h"
#include "Character.h"
#include "Player.h"
#include "StageFloor.h"
#include "StageWall.h"
#include "StageBuilding.h"
#include "StageGate.h"
#include "MyCamera.h"
#include "Villager.h"
#include "Timer.h"
#include "Title.h"
#include"TitleStage.h"
#include"GameOver.h"
#include"GameOverStage.h"
#include"GameClear.h"
#include"GameClearStage.h"
#include"Key.h"
#include"KeySprite.h"
#include "StateMchine.h"
#include "EnemyState.h"
#include "BaseEnemy.h"
#include"PlayerHeartSpriteLeft.h"
#include"PlayerHeartSpriteMiddle.h"
#include"PlayerHeartSpriteRight.h"
#include"SurprisedSprite.h"
#include "ClockSprite.h"
#include"LoseSightOf.h"
#include"Hunter.h"
#include"AlertlevelGauge.h"
#include"Arrow.h"
#include"WoodenBox.h"
#include"FadeOut.h"
#include"Wood.h"
#include"KeyParticle.h"
#include "EfkInterfece.h"
