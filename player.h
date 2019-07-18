//=============================================================================
//
// �v���C���[���� [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// �}�N����`
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman003.png")	// �T���v���p�摜
#define TEXTURE_PLAYER_SIZE_X	(100)	// �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(200)	// 

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_POS_X		(SCREEN_WIDTH / 2)

#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���


struct Player
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				countAnim;					// �A�j���[�V�����J�E���g
	int				patternAnim;				// �A�j���[�V�����p�^�[���i���o�[


};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


#endif