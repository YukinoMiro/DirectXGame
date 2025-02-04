﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	float viewAngle = 0.0f;

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
<<<<<<< HEAD
=======
	
	/// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	///サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;

	///3Dモデル
	Model* model_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_[100];

	///ビュープロジェクション
	ViewProjection viewProjection_;

	///音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	//値を表示したい変数
	int32_t value_ = 0;
>>>>>>> e607fa625b633d6950f0e4098e2c1a4b5d49c2a7
};
