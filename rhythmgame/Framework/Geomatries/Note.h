#pragma once
class Note : public TextureRect
{
public:
    Note(Vector3 position, Vector3 size, float rotation, int p_lane);
    int GetLane() { return lane; }

    

private:

    // �̵� ����� Ʈ����
    int lane = 0;
    
};

