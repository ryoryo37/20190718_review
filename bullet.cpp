//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetVertexBullet(int no);
void SetTextureBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


Bullet			bullet[BULLET_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
									TEXTURE_GAME_BULLET,		// �t�@�C���̖��O
										&bullet->pD3DTexture);	// �ǂݍ��ރ������̃|�C���^

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		bullet[i].use = false;


		// ���_���̍쐬
		MakeVertexBullet(i);

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
		if (bullet->pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			bullet->pD3DTexture->Release();
			bullet->pD3DTexture = NULL;
		}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			bullet[i].pos.y += BULLET_SPEED;

			// ��ʊO�܂Ői�񂾂�
			if (bullet[i].pos.y < -TEXTURE_BULLET_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bullet[i].use = false;
				bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			SetVertexBullet(i);
		}


	}



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bullet->pD3DTexture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bullet[i].vertex, sizeof(VERTEX_2D));

		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexBullet(no);
	for (int i = 0; i < BULLET_MAX; i++)
	{

		// rhw�̐ݒ�
		bullet[i].vertex[0].rhw =
			bullet[i].vertex[1].rhw =
			bullet[i].vertex[2].rhw =
			bullet[i].vertex[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		bullet[i].vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet[i].vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		SetTextureBullet(no);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(int no)
{

	for (int i = 0; i < BULLET_MAX; i++)
	{

		bullet[i].vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		bullet[i].vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		bullet[i].vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		bullet[i].vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}    


//���_���W

void SetVertexBullet(int no)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{

		// ���_���W�̐ݒ�
		bullet[i].vertex[0].vtx.x = bullet[i].pos.x - TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[0].vtx.y = bullet[i].pos.y - TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[0].vtx.z = 0.0f;

		bullet[i].vertex[1].vtx.x = bullet[i].pos.x + TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[1].vtx.y = bullet[i].pos.y - TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[1].vtx.z = 0.0f;

		bullet[i].vertex[2].vtx.x = bullet[i].pos.x - TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[2].vtx.y = bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[2].vtx.z = 0.0f;

		bullet[i].vertex[3].vtx.x = bullet[i].pos.x + TEXTURE_BULLET_SIZE_X;
		bullet[i].vertex[3].vtx.y = bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y;
		bullet[i].vertex[3].vtx.z = 0.0f;

		//		// ���_���W�̐ݒ�
		//bullet[i].vertex[0].vtx = D3DXVECTOR3(bullet[i].pos.x, bullet[i].pos.y, bullet[i].pos.z);
		//bullet[i].vertex[1].vtx = D3DXVECTOR3(bullet[i].pos.x + TEXTURE_BULLET_SIZE_X, bullet[i].pos.y, bullet[i].pos.z);
		//bullet[i].vertex[2].vtx = D3DXVECTOR3(bullet[i].pos.x, bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y, bullet[i].pos.z);
		//bullet[i].vertex[3].vtx = D3DXVECTOR3(bullet[i].pos.x + TEXTURE_BULLET_SIZE_X, bullet[i].pos.y + TEXTURE_BULLET_SIZE_Y, bullet[i].pos.z);


	}
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos)
{

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false)
		{
			bullet[i].use = true;				// �g�p��Ԃ֕ύX����
			bullet[i].pos = pos;				// ���W���Z�b�g


			return;								// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteBullet(int no)
{

	if (no >= 0 && no < BULLET_MAX)
	{
		bullet[no].use = false;
	}

}

//==============================================================================
// Get�֐�
//==============================================================================
Bullet *GetBullet(int no)
{
	return (&bullet[no]);

}