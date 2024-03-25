#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	: clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// 이미지가 가지고 있는 너비, 높이 가져오기
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// 애니메이션이 그려져있는 텍스처의 길이
	Vector2 clipSize = endPos - startPos;

	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀 프레임 즉, uv상의 좌표를 알아낼수 있다.
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		// 실행시킬 애니메이션 프레임의 x,y좌표 계산
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		keyFrames.push_back(keyFrame);
	}
}
