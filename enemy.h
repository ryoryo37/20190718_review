//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// マクロ定義
#define TEXTURE_GAME_ENEMY	_T	("data/TEXTURE/runningman001.png")	
#define TEXTURE_ENEMY_SIZE_X	(100)				// テクスチャサイズ
#define TEXTURE_ENEMY_SIZE_Y	(200)				// 同上

#define ENEMY_POS_X				(-300+SCREEN_WIDTH / 2)

#define ENEMY_TEXTURE_DIVIDE_X	(5)					// アニメパターンのテクスチャ内分割数（X)
#define ENEMY_TEXTURE_DIVIDE_Y	(2)					// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_ENEMY	(ENEMY_TEXTURE_DIVIDE_X*ENEMY_TEXTURE_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY	(4)					// アニメーションの切り替わるカウント
#define ENEMY_MAX				(3)

struct Enemy
{

	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				vertex[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;					// 移動量
	D3DXVECTOR3				rot;					// 回転量

	int						countAnim;				// アニメーションカウント
	int						patternAnim;			// アニメーションパターンナンバー

	bool					use;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);


#endif
