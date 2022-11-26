#pragma once
#include<GameObject.h>
namespace Utility
{
	/**
	 * @brief ３次元ベクトルの線形補間を行う関数
	 * @param start 線形補間の開始位置
	 * @param end 線形補間の終了位置
	 * @param t 補間の割合
	 * @return 補間後の位置
	 */
	inline Vec3 Lerp(const Vec3& start, const Vec3& end, float t)
	{
		t = t < 0.0f ? 0.0f : t;
		t = t > 1.0f ? 1.0f : t;
		return start + (end - start) * t;
	}

	/**
	 * @brief 実数の線形補間を行う関数
	 * @param start 線形補間の開始位置
	 * @param end 線形補間の終了位置
	 * @param t 補間の割合
	 * @return 補間後の位置
	 */
	inline float Lerp(float start, float end, float t)
	{
		return start + (end - start) * t;
	}
}
