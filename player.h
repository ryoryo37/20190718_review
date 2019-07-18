//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// マクロ定義
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman003.png")	// サンプル用画像
#define TEXTURE_PLAYER_SIZE_X	(100)	// テクスチャサイズ
#define TEXTURE_PLAYER_SIZE_Y	(200)	// 

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント

#define PLAYER_POS_X		(SCREEN_WIDTH / 2)

#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量


struct Player
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				countAnim;					// アニメーションカウント
	int				patternAnim;				// アニメーションパターンナンバー


};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


#endif