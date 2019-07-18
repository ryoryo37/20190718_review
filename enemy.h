//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// �}�N����`
#define TEXTURE_GAME_ENEMY	_T	("data/TEXTURE/runningman001.png")	
#define TEXTURE_ENEMY_SIZE_X	(100)				// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(200)				// ����

#define ENEMY_POS_X				(-300+SCREEN_WIDTH / 2)

#define ENEMY_TEXTURE_DIVIDE_X	(5)					// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENEMY_TEXTURE_DIVIDE_Y	(2)					// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_ENEMY	(ENEMY_TEXTURE_DIVIDE_X*ENEMY_TEXTURE_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY	(4)					// �A�j���[�V�����̐؂�ւ��J�E���g
#define ENEMY_MAX				(3)

struct Enemy
{

	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				vertex[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;					// �ړ���
	D3DXVECTOR3				rot;					// ��]��

	int						countAnim;				// �A�j���[�V�����J�E���g
	int						patternAnim;			// �A�j���[�V�����p�^�[���i���o�[

	bool					use;
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);


#endif
