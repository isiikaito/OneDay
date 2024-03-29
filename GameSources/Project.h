/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

#if _DEBUG
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#endif



#include "ProjectShader.h"
#include "ProjectBehavior.h"
#include "Scene.h"
#include "GameStage.h"
#include "Player.h"
#include "StageFloor.h"
#include "StageWall.h"
#include "StageBuilding.h"
#include "StageGate.h"
#include "MyCamera.h"
#include "Villager.h"
#include "Timer.h"
#include"TitleStage.h"
#include"GameOver.h"
#include"GameClearStage.h"
#include"Key.h"
#include "StateMchine.h"
#include "EnemyState.h"
#include "BaseEnemy.h"
#include"SurprisedSprite.h"
#include "CircleClockSprite.h"
#include"LoseSightOf.h"
#include"Hunter.h"
#include"AlertlevelGauge.h"
#include"Arrow.h"
#include"WoodenBox.h"
#include"FadeOut.h"
#include"Wood.h"
#include"KeyParticle.h"
#include "EfkInterfece.h"
