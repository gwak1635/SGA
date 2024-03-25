#pragma once

// �������� �ִϸ��̼� �̹��� ���� ����
class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex,
		UINT frameCount, Vector2 startPos, Vector2 endPos,
		bool bReversed = false);
private:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // �ִϸ��̼� ���� ��ġ�� ����
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	bool bReversed = false;
};

// �ִϸ��̼� Ŭ�� ���൵��
class Animator
{
public:
	Animator();
	~Animator();

	void Update();
	
	// ���� �������� �̹��� ��ǥ�� ��ȯ
	Vector2 GetCurrentFrame() { return currentFrame; }
	// ���� �������� �̹��� uv�� ��ȯ
	Vector2 GetTexelFrameSize()
	{ return currentClip->texelFrameSize; }
	// ���� �������� �̹��� srv ��ȯ // srv = ������ �׸� ������
	ID3D11ShaderResourceView* GetCurrentSRV()
	{ return currentClip->srv; }

	// animClips�� Ŭ�� �߰�
	void AddAnimClip(AnimationClip* animClip);
	// ���� �����ų Ŭ�� ����
	void SetCurrentAnimClip(wstring clipName);

	// ���� �������� Ŭ�� �̸� ��ȯ
	wstring GetCurrentClipName()
	{ return currentClip->clipName; }
	// �������� �ִϸ��̼� �ӵ� ���� // �̹��� ��ȯ �ӵ�
	void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName)
	{ return animClips.find(clipName) != animClips.end(); }

	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;

	// �̹��� ��ȯ �ӵ�
	float playRate = 1.0f / 15.0f;
};