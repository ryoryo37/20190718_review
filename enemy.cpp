//=============================================================================
//
//�G�l�~�[���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "bullet.h"
#include "checkhit.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy(int no,int cntPattern);
void SetVertexEnemy(int no);
void CheckhitEnemyToBullet();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Enemy					enemy[ENEMY_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY,					// �t�@�C���̖��O
			&enemy->pD3DTexture);				// �ǂݍ��ރ������̃|�C���^

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].pos = D3DXVECTOR3(ENEMY_POS_X + 300.0f * i, 500.0f, 0.0f);
		enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		enemy[i].countAnim = 0;
		enemy[i].patternAnim = 0;

		enemy[i].use = true;

		// ���_���̍쐬
		MakeVertexEnemy(i);




	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		if (enemy[i].pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			enemy[i].pD3DTexture->Release();
			enemy[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	Bullet *bullet = GetBullet(0);


	if (enemy->use==true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			// �A�j���[�V����
			enemy[i].countAnim++;

			if ((enemy[i].countAnim%TIME_ANIMATION_ENEMY) == 0)
			{
				enemy[i].patternAnim = (enemy[i].patternAnim + 1) % ANIM_PATTERN_ENEMY;

				SetTextureEnemy(i, enemy[i].patternAnim);

			}
			SetVertexEnemy(i);
		}


 			CheckhitEnemyToBullet();

	}




}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, enemy[0].pD3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemy[i].vertex, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexEnemy(no);
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		// rhw�̐ݒ�
		enemy[i].vertex[0].rhw =
			enemy[i].vertex[1].rhw =
			enemy[i].vertex[2].rhw =
			enemy[i].vertex[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		enemy[i].vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy[i].vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		SetTextureEnemy(no, enemy[i].patternAnim);
	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(int no,int cntPattern)
{

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % ENEMY_TEXTURE_DIVIDE_X;
	int y = cntPattern / ENEMY_TEXTURE_DIVIDE_Y;
	float sizeX = 1.0f / ENEMY_TEXTURE_DIVIDE_X;
	float sizeY = 1.0f / ENEMY_TEXTURE_DIVIDE_Y;
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		enemy[i].vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemy[i].vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemy[i].vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemy[i].vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
}


//���_���W

void SetVertexEnemy(int no)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		// ���_���W�̐ݒ�
		enemy[i].vertex[0].vtx = D3DXVECTOR3(enemy[i].pos.x, enemy[i].pos.y, enemy[i].pos.z);
		enemy[i].vertex[1].vtx = D3DXVECTOR3(enemy[i].pos.x + TEXTURE_ENEMY_SIZE_X, enemy[i].pos.y, enemy[i].pos.z);
		enemy[i].vertex[2].vtx = D3DXVECTOR3(enemy[i].pos.x, enemy[i].pos.y + TEXTURE_ENEMY_SIZE_Y, enemy[i].pos.z);
		enemy[i].vertex[3].vtx = D3DXVECTOR3(enemy[i].pos.x + TEXTURE_ENEMY_SIZE_X, enemy[i].pos.y + TEXTURE_ENEMY_SIZE_Y, enemy[i].pos.z);

	}

}

void CheckhitEnemyToBullet()
{
	Bullet *bullet = GetBullet(0);
	Enemy *ene = &enemy[0];

		if (CheckhitBC(bullet->pos, enemy->pos,  TEXTURE_BULLET_SIZE_X /2,TEXTURE_ENEMY_SIZE_X /2))
		{
			enemy->use = false;
			DeleteBullet(0);

		}
}