#include "Skydome.h"
#include <cassert>
#include "affinTransformation.h"

void Skydome::Initialze(Model* model) 
{
	// NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記録する
	model_ = model;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();

}


void Skydome::Update() 
{
	
	
#pragma region 調整
	worldTransform_.scale_.x = 50.0f;
	worldTransform_.scale_.y = 50.0f;
	worldTransform_.scale_.z = 50.0f;

	worldTransform_.rotation_.y = 180;
	affinTransformation::Transfer(worldTransform_);

	////行列更新
	worldTransform_.TransferMatrix();
#pragma endregion
}


void Skydome::Draw(ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection); 
}







