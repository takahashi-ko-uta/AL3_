#pragma once
#include "WorldTransform.h"

namespace affinTransformation
{
void Scale(WorldTransform& worldTransform_);     //�X�P�[�����O
void Rotate(WorldTransform& worldTransform_);    //��]
void Translate(WorldTransform& worldTransform_); //�ړ�
void Transfer(WorldTransform& worldTransform_); //��̑S��		
void Par(WorldTransform& worldTransform_, int min, int max); // for
}


