#pragma once

// 실질적인 애니메이션 이미지 분할 모음
class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex,
		UINT frameCount, Vector2 startPos, Vector2 endPos,
		bool bReversed = false);
private:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // 애니매이션 시작 위치들 저장
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	bool bReversed = false;
};

// 애니메이션 클립 실행도구
class Animator
{
public:
	Animator();
	~Animator();

	void Update();
	
	// 현재 실행중인 이미지 좌표값 반환
	Vector2 GetCurrentFrame() { return currentFrame; }
	// 현재 실행중인 이미지 uv값 반환
	Vector2 GetTexelFrameSize()
	{ return currentClip->texelFrameSize; }
	// 현재 실행중인 이미지 srv 반환 // srv = 실질적 그림 데이터
	ID3D11ShaderResourceView* GetCurrentSRV()
	{ return currentClip->srv; }

	// animClips에 클립 추가
	void AddAnimClip(AnimationClip* animClip);
	// 지금 실행시킬 클립 지정
	void SetCurrentAnimClip(wstring clipName);

	// 현재 실행중인 클립 이름 반환
	wstring GetCurrentClipName()
	{ return currentClip->clipName; }
	// 실행중인 애니메이션 속도 조절 // 이미지 전환 속도
	void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName)
	{ return animClips.find(clipName) != animClips.end(); }

	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;

	// 이미지 전환 속도
	float playRate = 1.0f / 15.0f;
};