//=========================================================
//
// 当たり判定
//	名和遼汰朗
//
//=========================================================
#include "main.h"
#include "checkhit.h"

//===========================================
// バウンティングボックスによる当たり判定
// 回転は考慮外
//===========================================
bool CheckhitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	//	半サイズにする
	size1 /= 2.0f;	
	size2 /= 2.0f;

	// 当たり判定
	if (pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y)
	{
		return true;
	}

	return false;

}
//=============================================
// バウンティングサークルによる当たり判定
// サイズは半径
//=============================================
bool CheckhitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{

	float Length;	// 当たり判定の有効距離

	// xとyの2乗の距離
	Length = (pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y);

	if ((size1 + size2) * (size1 + size2) > Length)
	{
		return true;

	}
	return false;

}
