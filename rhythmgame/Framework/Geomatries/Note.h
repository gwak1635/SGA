#pragma once
class Note : public TextureRect
{
public:
    Note(Vector3 position, Vector3 size, float rotation, int p_lane);
    int GetLane() { return lane; }

    void SetLoading(bool loading) { this->isloading = loading; }
    int GetLoading() { return isloading; }

private:

    // 이동 제어용 트리거
    int lane = 0;
    bool isloading = true;
};

