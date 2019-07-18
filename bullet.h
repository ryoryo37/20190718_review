//=============================================================================
//
//	バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// マクロ定義
#define TEXTURE_GAME_BULLET	_T	("data/TEXTURE/bullet000.png")	
#define TEXTURE_BULLET_SIZE_X	(30)				// テクスチャサイズ
#define TEXTURE_BULLET_SIZE_Y	(30)				// 同上

#define BULLET_TEXTURE_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X)
#define BULLET_TEXTURE_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y)


//#define BULLET_INITIALPOS_X		(-100)
#define BULLET_MAX				(256)
#define BULLET_SPEED			(10.0f)

struct Bullet
{

	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				vertex[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;					// 移動量
	D3DXVECTOR3				rot;					// 回転量

	bool					use;

};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
void DeleteBullet(int no);
Bullet *GetBullet(int no);


#endif
