//=============================================================================
//
//エネミー処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bullet.h"
#include "checkhit.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy(int no,int cntPattern);
void SetVertexEnemy(int no);
void CheckhitEnemyToBullet();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Enemy					enemy[ENEMY_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_ENEMY,					// ファイルの名前
			&enemy->pD3DTexture);				// 読み込むメモリのポインタ

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].pos = D3DXVECTOR3(ENEMY_POS_X + 300.0f * i, 500.0f, 0.0f);
		enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		enemy[i].countAnim = 0;
		enemy[i].patternAnim = 0;

		enemy[i].use = true;

		// 頂点情報の作成
		MakeVertexEnemy(i);




	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		if (enemy[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			enemy[i].pD3DTexture->Release();
			enemy[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	Bullet *bullet = GetBullet(0);


	if (enemy->use==true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			// アニメーション
			enemy[i].countAnim++;

			if ((enemy[i].countAnim%TIME_ANIMATION_ENEMY) == 0)
			{
				enemy[i].patternAnim = (enemy[i].patternAnim + 1) % ANIM_PATTERN_ENEMY;

				SetTextureEnemy(i, enemy[i].patternAnim);

			}
			SetVertexEnemy(i);
		}


 			CheckhitEnemyToBullet();

	}




}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, enemy[0].pD3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemy[i].vertex, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexEnemy(no);
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		// rhwの設定
		enemy[i].vertex[0].rhw =
			enemy[i].vertex[1].rhw =
			enemy[i].vertex[2].rhw =
			enemy[i].vertex[3].rhw = 1.0f;

		// 反射光の設定
		enemy[i].vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		SetTextureEnemy(no, enemy[i].patternAnim);
	}
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(int no,int cntPattern)
{

	// テクスチャ座標の設定
	int x = cntPattern % ENEMY_TEXTURE_DIVIDE_X;
	int y = cntPattern / ENEMY_TEXTURE_DIVIDE_Y;
	float sizeX = 1.0f / ENEMY_TEXTURE_DIVIDE_X;
	float sizeY = 1.0f / ENEMY_TEXTURE_DIVIDE_Y;
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		enemy[i].vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemy[i].vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemy[i].vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemy[i].vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
}


//頂点座標

void SetVertexEnemy(int no)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		// 頂点座標の設定
		enemy[i].vertex[0].vtx = D3DXVECTOR3(enemy[i].pos.x, enemy[i].pos.y, enemy[i].pos.z);
		enemy[i].vertex[1].vtx = D3DXVECTOR3(enemy[i].pos.x + TEXTURE_ENEMY_SIZE_X, enemy[i].pos.y, enemy[i].pos.z);
		enemy[i].vertex[2].vtx = D3DXVECTOR3(enemy[i].pos.x, enemy[i].pos.y + TEXTURE_ENEMY_SIZE_Y, enemy[i].pos.z);
		enemy[i].vertex[3].vtx = D3DXVECTOR3(enemy[i].pos.x + TEXTURE_ENEMY_SIZE_X, enemy[i].pos.y + TEXTURE_ENEMY_SIZE_Y, enemy[i].pos.z);

	}

}

void CheckhitEnemyToBullet()
{
	Bullet *bullet = GetBullet(0);
	Enemy *ene = &enemy[0];

		if (CheckhitBC(bullet->pos, enemy->pos,  TEXTURE_BULLET_SIZE_X /2,TEXTURE_ENEMY_SIZE_X /2))
		{
			enemy->use = false;
			DeleteBullet(0);

		}
}