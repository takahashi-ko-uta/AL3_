#pragma once
#include "WorldTransform.h"

namespace affinTransformation
{
	void Scale(WorldTransform worldTransform_, float sx, float sy, float sz);	//スケーリング
	void Rotate(WorldTransform worldTransform_, float rx, float ry, float rz);		//回転
	void Translate(WorldTransform worldTransform_, float tx, float ty, float tz);	//移動
    void Transform(                                                             //上の全て
			WorldTransform worldTransform_,
		float sx, float sy, float sz,
		float rx, float ry, float rz,
		float tx, float ty, float tz);
}


