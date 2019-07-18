//=============================================================================
//
//	�o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// �}�N����`
#define TEXTURE_GAME_BULLET	_T	("data/TEXTURE/bullet000.png")	
#define TEXTURE_BULLET_SIZE_X	(30)				// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(30)				// ����

#define BULLET_TEXTURE_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define BULLET_TEXTURE_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY)


//#define BULLET_INITIALPOS_X		(-100)
#define BULLET_MAX				(256)
#define BULLET_SPEED			(10.0f)

struct Bullet
{

	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				vertex[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;					// �ړ���
	D3DXVECTOR3				rot;					// ��]��

	bool					use;

};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
void DeleteBullet(int no);
Bullet *GetBullet(int no);


#endif
