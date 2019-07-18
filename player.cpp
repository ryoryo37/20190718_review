//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
void SetVertexPlayer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player	player;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.pos = D3DXVECTOR3(PLAYER_POS_X, 50.0f, 0.0f);
	player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	player.countAnim = 0;
	player.patternAnim = 0;

	// ���_���̍쐬
	MakeVertexPlayer();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&player.pD3DTexture );			// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

	if( player.pD3DTexture != NULL )	//
	{	// �e�N�X�`���̊J��
		player.pD3DTexture->Release();
		player.pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	// �A�j���[�V����
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
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, player.pD3DTexture );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexPlayer();

	// rhw�̐ݒ�
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTexturePlayer(player.patternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	player.vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	player.vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	player.vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	player.vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}


//���_���W

void SetVertexPlayer(void)
{

	// ���_���W�̐ݒ�
	player.vertexWk[0].vtx = D3DXVECTOR3(player.pos.x, player.pos.y, player.pos.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.pos.x + TEXTURE_PLAYER_SIZE_X, player.pos.y, player.pos.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.pos.x, player.pos.y + TEXTURE_PLAYER_SIZE_Y, player.pos.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.pos.x + TEXTURE_PLAYER_SIZE_X, player.pos.y + TEXTURE_PLAYER_SIZE_Y, player.pos.z);



}