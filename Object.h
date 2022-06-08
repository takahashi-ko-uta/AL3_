#pragma once
#include "WorldTransform.h"

namespace myApp 
{
	void Scale(WorldTransform worldTransform_, float sx, float sy, float sz);	//�X�P�[�����O
	void Rot(WorldTransform worldTransform_, float rx, float ry, float rz);		//��]
	void Trans(WorldTransform worldTransform_, float tx, float ty, float tz);	//�ړ�
	void Transform(																//��̑S��
			WorldTransform worldTransform_,
		float sx, float sy, float sz,
		float rx, float ry, float rz,
		float tx, float ty, float tz);
}
