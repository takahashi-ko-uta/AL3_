#pragma once
#include "WorldTransform.h"

namespace affinTransformation
{
void Scale(WorldTransform& worldTransform_);     //スケーリング
void Rotate(WorldTransform& worldTransform_);    //回転
void Translate(WorldTransform& worldTransform_); //移動
void Transfer(WorldTransform& worldTransform_); //上の全て

		
}


