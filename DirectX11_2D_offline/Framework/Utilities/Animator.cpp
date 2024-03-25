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
