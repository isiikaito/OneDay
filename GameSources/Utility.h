#pragma once
#include<GameObject.h>
namespace Utility
{
	/**
	 * @brief �R�����x�N�g���̐��`��Ԃ��s���֐�
	 * @param start ���`��Ԃ̊J�n�ʒu
	 * @param end ���`��Ԃ̏I���ʒu
	 * @param t ��Ԃ̊���
	 * @return ��Ԍ�̈ʒu
	 */
	inline Vec3 Lerp(const Vec3& start, const Vec3& end, float t)
	{
		t = t < 0.0f ? 0.0f : t;
		t = t > 1.0f ? 1.0f : t;
		return start + (end - start) * t;
	}

	/**
	 * @brief �����̐��`��Ԃ��s���֐�
	 * @param start ���`��Ԃ̊J�n�ʒu
	 * @param end ���`��Ԃ̏I���ʒu
	 * @param t ��Ԃ̊���
	 * @return ��Ԍ�̈ʒu
	 */
	inline float Lerp(float start, float end, float t)
	{
		return start + (end - start) * t;
	}
}
