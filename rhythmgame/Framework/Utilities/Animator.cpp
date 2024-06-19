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
	// 애니메이션 경과 시간이 playRate보다 커졌을경우
	// 애니매이션을 진행 시킨다.
	if (deltaTime >= playRate)
	{
		// 역재생이 아니라면
		if (currentClip->bReversed == false)
		{
			// 프레임 인덱스 증가
			// 그릴 그림이 다음 그림으로 변경
			currentFrameIndex++;

			// 다음 그림 번호가 프레임의 개수와 똑같다는것은
			// 그림이 마지막까지 재생됐다는 이야기이기 때문에
			// 다시 번호를 0으로 초기화 해준다.
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			// 현재 실행할 그림을 위에서 지정한 번호의 그림으로
			// 설정한다.
			currentFrame =
				currentClip->keyFrames[currentFrameIndex];
		}
		else // 역재생일 경우
		{
			// 프레임 인덱스 감소
			// 역재생할 애니메이션도 순서는 일반적인 순서와
			// 똑같에 그림을 넣다보니 최대 숫자에서 1씩
			// 깍는 방식으로 다음 애니메이션을 지정한다.
			currentFrameIndex--;

			if (currentFrameIndex == -1)
			{
				// 배열의 최대치로 번호 설정
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

// 애니메이터에게 클립 자체를 넘겨주는 함수
// 애니메이터가 실행할 수 있는 클립 집어넣기
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName,
		animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	// 실행중인 클립이 있지만 새로 실행할 클립과 같을 경우
	if (currentClip != nullptr)
		if(currentClip->clipName == clipName)
			return;

	// 클립이 존재한다면
	// 실행중인 애니메이션과 새로 실행할 애니메이션이
	// 다를경우 교체하기위해 실행됨
	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		
		// 실행중이던 델타타임 초기화
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
