#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	: TextureRect(position,size,rotation)
{
	SetShader(ShaderPath + L"VertexTexture.hlsl");

	animator = new Animator();

	{
		Texture2D* srcTex = new Texture2D(TexturePath + L"SampleSheet.png");

		AnimationClip* RunD = new AnimationClip(
			L"RunD",//�ִϸ��̼� �̸�
			srcTex, //�ִϸ��̼ǿ� �� Texture 2D
			4,//�� ĭ�� ��
			Values::ZeroVec2, //�ʱ� ��ġ
			{ srcTex->GetWidth() * 0.5f,
			srcTex->GetHeight() * 0.125f });//������ ��ġ(�ڸ� ��ġ)

		AnimationClip* RunL = new AnimationClip(
			L"RunL",//�ִϸ��̼� �̸�
			srcTex, //�ִϸ��̼ǿ� �� Texture 2D
			4,//�� ĭ�� ��
			{ 0,srcTex->GetHeight() * 0.125f * 2 },//�ʱ� ��ġ
			{ srcTex->GetWidth() * 0.5f,
			(srcTex->GetHeight() * 0.125f *3)});//������ ��ġ(�ڸ� ��ġ)

		animator->AddAnimClip(RunD);
		animator->AddAnimClip(RunL);

		SAFE_DELETE(srcTex);
	}

	animator->SetCurrentAnimClip(L"RunL");
	animator->SetCurrentAnimClip(L"RunD");

	//Sampler
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &sampler[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &sampler[1]);
	}

	//Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blend[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blend[1]);
	}
}

AnimationRect::~AnimationRect()
{
	SAFE_DELETE(animator);
}

void AnimationRect::Update()
{
	animator->Update();


	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD,0, &subRe);
	{
		//���� �Ʒ�
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		//������ ��
		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		//������ �Ʒ�
		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		//���� ��
		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}

	memcpy(subRe.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());

	DC->Unmap(vb->GetResource(), 0);

	__super::Update();//�θ� Ŭ������ ��������
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &sampler[1]);
	DC->OMSetBlendState(blend[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::SetAnimator(Animator* animator)
{
	SAFE_DELETE(this->animator);
	this->animator = animator;
}