//=========================================================
//
// �����蔻��
//	���a�ɑ��N
//
//=========================================================
#include "main.h"
#include "checkhit.h"

//===========================================
// �o�E���e�B���O�{�b�N�X�ɂ�铖���蔻��
// ��]�͍l���O
//===========================================
bool CheckhitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	//	���T�C�Y�ɂ���
	size1 /= 2.0f;	
	size2 /= 2.0f;

	// �����蔻��
	if (pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y)
	{
		return true;
	}

	return false;

}
//=============================================
// �o�E���e�B���O�T�[�N���ɂ�铖���蔻��
// �T�C�Y�͔��a
//=============================================
bool CheckhitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{

	float Length;	// �����蔻��̗L������

	// x��y��2��̋���
	Length = (pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y);

	if ((size1 + size2) * (size1 + size2) > Length)
	{
		return true;

	}
	return false;

}
