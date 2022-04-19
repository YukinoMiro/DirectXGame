#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete sprite_; 

	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();

	///ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	///ビュープロジェクションの初期化
	viewProjection_.Initialize();

	///サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("se_sad03.wav");

	///音声の再生
	audio_->PlayWave(soundDataHandle_);

	///音声再生
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	///音量調整
	audio_->SetVolume(soundDataHandle_, 0.1f);

	//X,Y,Z方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};

	//X,Y,Z軸周りの回転角を設定
	worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};

	//X,Y,Z軸周りの平行移動を設定
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};

	//ワールドトランスフォームの初期設定
	worldTransform_.Initialize();

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

	std::string strDebug = std::string("translation : (" +
    std::to_string(worldTransform_.translation_.x) + "," +
    std::to_string(worldTransform_.translation_.y) + "," +
	std::to_string(worldTransform_.translation_.z) + ")");

	debugText_->Print(strDebug, 50, 50, 1.0f);

	std::string strDebug2 = std::string("rotation    : (" + 
	std::to_string(worldTransform_.rotation_.x) + " ," +
	std::to_string(worldTransform_.rotation_.y) + " ," +
	std::to_string(worldTransform_.rotation_.z) + " )");

	debugText_->Print(strDebug2, 50, 70, 1.0f);

	std::string strDebug3 = std::string("scale       : (" + 
	std::to_string(worldTransform_.scale_.x) + " ," +
	std::to_string(worldTransform_.scale_.y) + " ," +
	std::to_string(worldTransform_.scale_.z) + " )");

	debugText_->Print(strDebug3, 50, 90, 1.0f);
}

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
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	//sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

