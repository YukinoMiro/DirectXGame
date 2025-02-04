﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
<<<<<<< HEAD
}

void GameScene::Update() {}
=======
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();

	std::random_device seed_gen;

	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);

	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	///サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("se_sad03.wav");

	///音声の再生
	//audio_->PlayWave(soundDataHandle_);

	///音声再生
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	///音量調整
	audio_->SetVolume(soundDataHandle_, 0.1f);

	for (size_t i = 0; i < _countof(worldTransform_); i++) 
	{
		// X,Y,Z方向のスケーリングを設定
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};

		// X,Y,Z軸周りの回転角を設定
		worldTransform_[i].rotation_ = {rotDist(engine), rotDist(engine), rotDist(engine)};

		worldTransform_[i].translation_ = {posDist(engine), posDist(engine), posDist(engine)};
		
		//ワールドトランスフォームの初期設定
		worldTransform_[i].Initialize();
	}

	viewProjection_.eye = {0, 0, -50};

	viewProjection_.target = {0, 0, 0};

	viewProjection_.up = {cosf(XM_PI / 4.0f), sinf(XM_PI / 4.0f), 0.0f};

	//viewProjection_.fovAngleY = XMConvertToRadians(10.0f);

	//viewProjection_.aspectRatio = 1.0f;

	viewProjection_.nearZ = 52.0f;

	viewProjection_.farZ = 53.0f;

	///ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update()
{ 
	XMFLOAT2 position = sprite_->GetPosition(); 

	//position.x += 2.0f;
	//position.y += 1.0f;

	sprite_->SetPosition(position);

	if (input_->TriggerKey(DIK_SPACE)) 
	{
	    ///音声停止
		audio_->StopWave(voiceHandle_);
	}

	//debugText_->Print("kaizokuouni oreha naru.", 50, 50, 1.0f);

	//debugText_->SetPos(50, 70);
	//debugText_->Printf("translation:%d", worldTransform_.translation_.x);

	//value_++;

	XMFLOAT3 move = {0, 0, 0};

	const float KEyeSpeed = 0.2f;

	//if (input_ -> PushKey(DIK_W)) 
	//{
	//	move = {0, 0, KEyeSpeed};
	//} 
	//else if (input_->PushKey(DIK_S))
	//{
	//	move = {0, 0, -KEyeSpeed};
	//}

	viewProjection_.eye.x += move.x;
	viewProjection_.eye.y += move.y;
	viewProjection_.eye.z += move.z;



	debugText_->SetPos(50,50);
	debugText_->Printf("eye    : (%f,%f.%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	const float KTargetSpeed = 0.2f;

	//if (input_->PushKey(DIK_LEFT)) 
	//{
	//	move = {-KTargetSpeed, 0, 0};
	//} 
	//else if (input_->PushKey(DIK_RIGHT)) 
	//{
	//	move = {KTargetSpeed, 0, 0};
	//}

	//viewProjection_.target.x += move.x;
	//viewProjection_.target.y += move.y;
	//viewProjection_.target.z += move.z;

	debugText_->SetPos(50, 70);
	debugText_->Printf("target : (%f,%f.%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);

	const float KUpRotSpeed = 0.05f;

	//if (input_->PushKey(DIK_SPACE)) 
	//{
	//	viewAngle += KUpRotSpeed;

	//	viewAngle = fmodf(viewAngle, XM_2PI);
	//}

	viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

	viewProjection_.UpdateMatrix();

	debugText_->SetPos(50, 90);
	debugText_->Printf("up     : (%f,%f.%f)", viewProjection_.up.x, viewProjection_.up.y,viewProjection_.up.z);

	if (input_->PushKey(DIK_W)) 
	{
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	} 
	else if (input_->PushKey(DIK_S)) 
	{
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	}

	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree) : %f", XMConvertToDegrees(viewProjection_.fovAngleY));

	if (input_->PushKey(DIK_UP)) 
	{
		viewProjection_.nearZ += 0.1f;
	}
	else if (input_->PushKey(DIK_DOWN))
	{
		viewProjection_.nearZ -= 0.1f;
	}

	viewProjection_.UpdateMatrix();

	debugText_->SetPos(50, 130);
	debugText_->Printf("nearz : %f", viewProjection_.nearZ);
}
>>>>>>> e607fa625b633d6950f0e4098e2c1a4b5d49c2a7

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
<<<<<<< HEAD
=======
	
	for (size_t i = 0; i < _countof(worldTransform_); i++)
	{
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}
>>>>>>> e607fa625b633d6950f0e4098e2c1a4b5d49c2a7

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
