//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetVertexBullet(int no);
void SetTextureBullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************


Bullet			bullet[BULLET_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
									TEXTURE_GAME_BULLET,		// ファイルの名前
										&bullet->pD3DTexture);	// 読み込むメモリのポインタ

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		bullet[i].use = false;


		// 頂点情報の作成
		MakeVertexBullet(i);

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
		if (bullet->pD3DTexture != NULL)
		{	// テクスチャの開放
			bullet->pD3DTexture->Release();
			bullet->pD3DTexture = NULL;
		}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == true)			// 使用している状態なら更新する
		{
			// バレットの移動処理
			bullet[i].pos.y += BULLET_SPEED;

			// 画面外まで進んだか
			if (bullet[i].pos.y < -TEXTURE_BULLET_SIZE_Y)	// 自分の大きさを考慮して画面外か判定している
			{
				bullet[i].use = false;
				bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			SetVertexBullet(i);
		}


	}



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bullet->pD3DTexture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bullet[i].vertex, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexBullet(no);
	for (int i = 0; i < BULLET_MAX; i++)
	{

		// rhwの設定
		bullet[i].vertex[0].rhw =
			bullet[i].vertex[1].rhw =
			bullet[i].vertex[2].rhw =
			bullet[i].vertex[3].rhw = 1.0f;

		// 反射光の設定
		bullet[i].vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		SetTextureBullet(no);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet(int no)
{

	for (int i = 0; i < BULLET_MAX; i++)
	{

		bullet[i].vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		bullet[i].vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		bullet[i].vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		bullet[i].vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}    


//頂点座標

void SetVertexBullet(int no)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{

		// 頂点座標の設定
		bullet[i].vertex[0].vtx.x = bullet[i].pos.x - TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[0].vtx.y = bullet[i].pos.y - TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[0].vtx.z = 0.0f;

		bullet[i].vertex[1].vtx.x = bullet[i].pos.x + TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[1].vtx.y = bullet[i].pos.y - TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[1].vtx.z = 0.0f;

		bullet[i].vertex[2].vtx.x = bullet[i].pos.x - TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[2].vtx.y = bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[2].vtx.z = 0.0f;

		bullet[i].vertex[3].vtx.x = bullet[i].pos.x + TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[3].vtx.y = bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[3].vtx.z = 0.0f;

		//		// 頂点座標の設定
		//bullet[i].vertex[0].vtx = D3DXVECTOR3(bullet[i].pos.x, bullet[i].pos.y, bullet[i].pos.z);
		//bullet[i].vertex[1].vtx = D3DXVECTOR3(bullet[i].pos.x + TEXTURE_BULLET_SIZE_X, bullet[i].pos.y, bullet[i].pos.z);
		//bullet[i].vertex[2].vtx = D3DXVECTOR3(bullet[i].pos.x, bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y, bullet[i].pos.z);
		//bullet[i].vertex[3].vtx = D3DXVECTOR3(bullet[i].pos.x + TEXTURE_BULLET_SIZE_X, bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y, bullet[i].pos.z);


	}
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos)
{

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false)
		{
			bullet[i].use = true;				// 使用状態へ変更する
			bullet[i].pos = pos;				// 座標をセット


			return;								// 1発セットしたので終了する
		}
	}
}


//=============================================================================
// 弾の削除
//=============================================================================
void DeleteBullet(int no)
{

	if (no >= 0 && no < BULLET_MAX)
	{
		bullet[no].use = false;
	}

}

//==============================================================================
// Get関数
//==============================================================================
Bullet *GetBullet(int no)
{
	return (&bullet[no]);

}