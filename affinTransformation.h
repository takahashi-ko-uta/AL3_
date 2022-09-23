#pragma once
#include "WorldTransform.h"

namespace affinTransformation
{
void Scale(WorldTransform& worldTransform_);     //スケーリング
void Rotate(WorldTransform& worldTransform_);    //回転
void Translate(WorldTransform& worldTransform_); //移動
void Transfer(WorldTransform& worldTransform_); //上の全て		
Vector3 VecMat(Vector3 vec3, WorldTransform& worldTransform_);//ベクトルと行列の掛け算
}