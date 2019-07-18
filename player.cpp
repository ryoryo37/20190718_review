//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
void SetVertexPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player	player;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.pos = D3DXVECTOR3(PLAYER_POS_X, 50.0f, 0.0f);
	player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	player.countAnim = 0;
	player.patternAnim = 0;

	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&player.pD3DTexture );			// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

	if( player.pD3DTexture != NULL )	//
	{	// テクスチャの開放
		player.pD3DTexture->Release();
		player.pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	// アニメーション
	player.countAnim++;

	if ((player.countAnim%TIME_ANIMATION) == 0)
	{
		player.patternAnim = (player.patternAnim + 1)% ANIM_PATTERN_NUM;

		SetTexturePlayer(player.patternAnim);

	}
	SetVertexPlayer();
	if (GetKeyboardPress(DIK_D))
	{
		player.pos.x += 5.0f;

	}

	if (GetKeyboardPress(DIK_A))
	{
		player.pos.x -= 5.0f;

	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetBullet(player.pos);

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture( 0, player.pD3DTexture );

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexPlayer();

	// rhwの設定
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	SetTexturePlayer(player.patternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	player.vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	player.vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	player.vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	player.vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}


//頂点座標

void SetVertexPlayer(void)
{

	// 頂点座標の設定
	player.vertexWk[0].vtx = D3DXVECTOR3(player.pos.x, player.pos.y, player.pos.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.pos.x + TEXTURE_PLAYER_SIZE_X, player.pos.y, player.pos.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.pos.x, player.pos.y + TEXTURE_PLAYER_SIZE_Y, player.pos.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.pos.x + TEXTURE_PLAYER_SIZE_X, player.pos.y + TEXTURE_PLAYER_SIZE_Y, player.pos.z);



}