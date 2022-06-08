#include "Object.h"
#include "MathUtility.h"
#include <math.h>

#define PI 3.141592
namespace myApp 
{
void Scale(WorldTransform worldTransform_, float sx, float sy, float sz) {//�X�P�[�����O

	// X,Y,Z�����̃X�P�[�����O
	worldTransform_.scale_ = {sx, sy, sz};
	//�X�P�[�����O�s���錾
	Matrix4 matScale;
	//�X�P�[�����O�{�����s���錾
	matScale = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matScale;

	//�s��̓]��
	worldTransform_.TransferMatrix();
}
void Rot(WorldTransform worldTransform_, float rx, float ry, float rz) {//��]

	// X,Y,Z�����̉�]
	worldTransform_.rotation_ = {rx, ry, rz};
	//��]�s���錾
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	//��]�{�����s���錾
	matRot = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	matRotZ = MathUtility ::Matrix4Identity();
	matRotX = MathUtility ::Matrix4Identity();
	matRotY = MathUtility ::Matrix4Identity();
	// Z����]�̊e�v�f
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	// X����]�̊e�v�f
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	// Y����]�̊e�v�f
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	//�e���p��]�s���錾
	matRot *= matRotZ *= matRotX *= matRotY;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matRot;

	//�s��̓]��
	worldTransform_.TransferMatrix();
}
void Trans(WorldTransform worldTransform_, float tx, float ty, float tz) {//�ړ�

	// X,Y,Z�����̕��s�ړ�
	worldTransform_.translation_ = {tx, ty, tz};
	//���s�ړ��s���錾
	Matrix4 matTrans;
	//���s�ړ����s���錾
	matTrans = MathUtility ::Matrix4Identity();

	matTrans.m[3][0] += worldTransform_.translation_.x;
	matTrans.m[3][1] += worldTransform_.translation_.y;
	matTrans.m[3][2] += worldTransform_.translation_.z;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ *= matTrans;
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Transform(																//��̑S��
  WorldTransform worldTransform_, float sx, float sy, float sz, float rx, float ry, float rz,float tx, float ty, float tz) {
	// X,Y,Z�����̃X�P�[�����O
	worldTransform_.scale_ = {sx, sy, sz};
	// X,Y,Z�����̉�]
	worldTransform_.rotation_ = {rx, ry, rz};
	// X,Y,Z�����̕��s�ړ�
	worldTransform_.translation_ = {tx, ty, tz};

	//�X�P�[�����O�s���錾
	Matrix4 matScale;
	//��]�s���錾
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	//���s�ړ��s���錾
	Matrix4 matTrans;

	matScale = MathUtility ::Matrix4Identity();
	matRot = MathUtility ::Matrix4Identity();
	matRotX = MathUtility ::Matrix4Identity();
	matRotY = MathUtility ::Matrix4Identity();
	matRotZ = MathUtility ::Matrix4Identity();
	matTrans = MathUtility ::Matrix4Identity();

	//�{��
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	// Z����]�̊e�v�f
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	// X����]�̊e�v�f
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	// Y����]�̊e�v�f
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	//���s�ړ�
	matTrans.m[3][0] += worldTransform_.translation_.x;
	matTrans.m[3][1] += worldTransform_.translation_.y;
	matTrans.m[3][2] += worldTransform_.translation_.z;

	//�e���p��]�s���錾
	matRot *= matRotZ *= matRotX *= matRotY;

	worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	worldTransform_.matWorld_ = matScale *= matRot *= matTrans;

	//�s��̓]��
	worldTransform_.TransferMatrix();
}
}


