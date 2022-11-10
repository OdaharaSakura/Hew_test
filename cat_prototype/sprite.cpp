#include "renderer.h"
#include "main.h"

//�}�N��
#define NUM_VERTEX 4

static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;
//�\�����WX,Y,�T�C�Y��,�c,��]�p�x,�J���[,�p�^�[���ԍ�,
//�p�^�[���T�C�Y��,�c,���ɕ��ԃp�^�[����
void DrawSpriteColorRotate(float posx, float posy, int size_w,
	int size_h, float kakudo, D3DXCOLOR col,
	float PaternNo,
	float uv_w, float uv_h,
	int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//�ϐ���t���đ����Ă����ƊG�������I
	static float ofset = 0.0f;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, 0.0f);
	vertex[0].Diffuse = col;	// D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f + ofset, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, 0.0f);
	vertex[1].Diffuse = col;	// D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f + ofset, 0.0f);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, 0.0f);
	vertex[2].Diffuse = col;	// D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f + ofset, 1.0f);//�C�������I
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, 0.0f);
	vertex[3].Diffuse = col;	// D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f + ofset, 1.0f);//�C�������I
	//�����Ă����Ƃ���
	//ofset += 1.0f / 60.0f;
	//60�Ŋ����Ă�̂�1�b�ň�摜��������I

		//UV�A�j��
	//�������ɂ����Ⴄ
		//�ŏ��̈�񂾂��������̃[���A���̌�͒l���ۑ������I
		//static float PaternNo = 0;
		//float uv_w = 0.5f;//�L�����N�^�[�̉��T�C�Y
		//float uv_h = 0.5f;//�L�����N�^�[�̏c�T�C�Y�@�@�c�݂����Ȋ���
		//int NumPatern = 2;//�L�����N�^�[�̉��̖���
		////�p�^�[���ԍ������������₷���ƂŒx���o����̂�
		//PaternNo += 0.01f;
		////�p�^�[���ԍ���4�ȏ�ɂȂ�����
		//if (PaternNo >= 4)
		//{
		//	//�����Ȃ�=0;�ɂ����Ⴄ�ƌ덷����������I������
		//	//�܂������Z�ŏ������c���Ă����悤
		//	PaternNo -= 4.0f;
		//}
		//���₵����ɐ����l�ɑ�����邱�Ƃŏ����_��؂�̂āI
		int no = PaternNo;

		//����(LEFT-TOP)��UV���W���v�Z
		float uv_left = (no % NumPatern) * uv_w;//����U
		float uv_top = (no / NumPatern) * uv_h;//V���W

		////�e�N�X�`�����W������������
		vertex[0].TexCoord = D3DXVECTOR2(uv_left, uv_top);//LEFT-TOP
		vertex[1].TexCoord = D3DXVECTOR2(uv_left+uv_w, uv_top);//RIGHT-TOP
		vertex[2].TexCoord = D3DXVECTOR2(uv_left, uv_top + uv_h);//LEFT-BOTTOM
		vertex[3].TexCoord = D3DXVECTOR2(uv_left+uv_w, uv_top + uv_h);//RIGHT-BOTTOM

		//����œ����悤�ɂȂ�܂����I
		//�p���p������݂����ɂȂ邼�I����ŕ������[�V�����Ƃ��ł���H
		//���Ƃ͔w�i�𓮂����Ȃ��悤�Ɋ֐��ŕ�������Ȃǎ����Őݒ�I�I

		//�x�����W�A���֕ϊ�
		float	rad = D3DXToRadian(kakudo);
		float	x, y;

		for (int i = 0; i < 4; i++)
		{
			x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
			y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

			vertex[i].Position.x = x + posx;
			vertex[i].Position.y = y + posy;
		}
		GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//�������ݏI��
	    //�\���������|���S���̒��_�o�b�t�@��ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//�|���S���`��
		GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

	void InitSptite()
	{
		{//�O�p�`�p�̒��_����������
	// ���_�o�b�t�@����
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//���_1�����_���̃T�C�Y�ō��
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		}
	}
	
	void UnInitSptite()
	{
		if (g_VertexBufferTriangle)
		{
			g_VertexBufferTriangle->Release();//�g���I������̂ŉ������
			g_VertexBufferTriangle = NULL;
		}

	}