#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	: clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// �̹����� ������ �ִ� �ʺ�, ���� ��������
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// �ִϸ��̼��� �׷����ִ� �ؽ�ó�� ����
	Vector2 clipSize = endPos - startPos;

	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ؼ� ������ ��, uv���� ��ǥ�� �˾Ƴ��� �ִ�.
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		// �����ų �ִϸ��̼� �������� x,y��ǥ ���
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
	for (auto clip : animClips)
	{
		SAFE_DELETE(clip.second);
	}
}

void Animator::Update()
{
	// �ִϸ��̼� ��� �ð��� playRate���� Ŀ�������
	// �ִϸ��̼��� ���� ��Ų��.
	if (deltaTime >= playRate)
	{
		// ������� �ƴ϶��
		if (currentClip->bReversed == false)
		{
			// ������ �ε��� ����
			// �׸� �׸��� ���� �׸����� ����
			currentFrameIndex++;

			// ���� �׸� ��ȣ�� �������� ������ �Ȱ��ٴ°���
			// �׸��� ���������� ����ƴٴ� �̾߱��̱� ������
			// �ٽ� ��ȣ�� 0���� �ʱ�ȭ ���ش�.
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			// ���� ������ �׸��� ������ ������ ��ȣ�� �׸�����
			// �����Ѵ�.
			currentFrame =
				currentClip->keyFrames[currentFrameIndex];
		}
		else // ������� ���
		{
			// ������ �ε��� ����
			// ������� �ִϸ��̼ǵ� ������ �Ϲ����� ������
			// �Ȱ��� �׸��� �ִٺ��� �ִ� ���ڿ��� 1��
			// ��� ������� ���� �ִϸ��̼��� �����Ѵ�.
			currentFrameIndex--;

			if (currentFrameIndex == -1)
			{
				// �迭�� �ִ�ġ�� ��ȣ ����
				currentFrameIndex
					= currentClip->frameCount - 1;
			}

			currentFrame =
				currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else
		deltaTime += Time::Delta();
}

// �ִϸ����Ϳ��� Ŭ�� ��ü�� �Ѱ��ִ� �Լ�
// �ִϸ����Ͱ� ������ �� �ִ� Ŭ�� ����ֱ�
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName,
		animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	// �������� Ŭ���� ������ ���� ������ Ŭ���� ���� ���
	if (currentClip != nullptr)
		if(currentClip->clipName == clipName)
			return;

	// Ŭ���� �����Ѵٸ�
	// �������� �ִϸ��̼ǰ� ���� ������ �ִϸ��̼���
	// �ٸ���� ��ü�ϱ����� �����
	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		
		// �������̴� ��ŸŸ�� �ʱ�ȭ
		deltaTime = 0.0f;

		if (currentClip->bReversed == true)
		{
			currentFrameIndex =
				currentClip->frameCount - 1;
		}
		else
			currentFrameIndex = 0;

		currentFrame =
			currentClip->keyFrames[currentFrameIndex];
	}
}
