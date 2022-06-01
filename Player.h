#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"



///<summary>
///���L����
///</summary>

class Player {
  public:

	///< summary>
	///������
	///</summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void InitiaLize(Model* model,uint32_t textreHandle);

	///< summary>
	///�X�V
	///</summary>
	void Update();

	///< summary>
	///�`��
	///</summary>
	void Draw(ViewProjection viewProjection_);

	private:
		//���[���h�ϊ��f�[�^
	    WorldTransform worldTransform_; 
		//���f��
	    Model* model_ = nullptr;
		//�e�N�X�`���n���h��
	    uint32_t textureHandle_ = 0u;
	    Input* input_ = nullptr;
	    DebugText* debugText_ = nullptr;


};
