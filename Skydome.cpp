#include "Skydome.h"
#include <cassert>
#include "affinTransformation.h"

void Skydome::Initialze(Model* model) 
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

}


void Skydome::Update() 
{
	
	
#pragma region ����
	worldTransform_.scale_.x = 50.0f;
	worldTransform_.scale_.y = 50.0f;
	worldTransform_.scale_.z = 50.0f;

	worldTransform_.rotation_.y = 180;
	affinTransformation::Transfer(worldTransform_);

	////�s��X�V
	worldTransform_.TransferMatrix();
#pragma endregion
}


void Skydome::Draw(ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection); 
}







