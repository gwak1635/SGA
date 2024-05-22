#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	Vector2 ClipSize = endPos - startPos;

	Vector2 frameSize;
	frameSize.x = ClipSize.x / frameCount;
	frameSize.y = ClipSize.y;


	//이미지 크기 400
	// 잘라야 할 크기 100

	//UV용(0~1에서 나옴)
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;

	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		keyFrames.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips) {
		SAFE_DELETE(clip.second);
	}
}

void Animator::Update()
{
	if (deltaTime >= playRate)
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			currentFrame = currentClip -> keyFrames[currentFrameIndex];

		}
		else
		{
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount -1;

			currentFrame = currentClip -> keyFrames[currentFrameIndex];

		}
		deltaTime = 0.0f;
	}
	else
	{
		deltaTime += Time::Delta();
	}
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip != nullptr)
		if (currentClip->clipName == clipName) return;

	if (CheckExist(clipName))
	{
		currentClip - animClips.find(clipName)->second;

		deltaTime = 0.0f;

		if (currentClip->bReversed)
		{
			currentFrameIndex = currentClip->frameCount - 1;
		}
		else
		{
			currentFrameIndex = 0;
		}

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
