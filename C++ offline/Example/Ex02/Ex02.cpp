#include "Ex02.h"

void Ex02()
{
    {   // �⺻������ ��� ���ڸ� 1Byte ũ��� �޾ƿ�
        // �׷��� ���� �ѱ��̳� �Ϻ� Ư�����ڴ� ��,����� ����
        char astring[100];
        string cString = "";
    }

    // wstring�� ���ڸ� ����Ҷ� L�� �ٿ�����ϴ� ���ŷο��� ũ����
    // ��� ���ڸ� 2Byte ũ��� �޾ƿ��� ������
    // �ѱ��̳� Ư������ ���� ���ſ� ���ڸ� 
    // ���������� ����Ҽ� �ִ�.
    wstring wString = L"";

    string temp = "";

    cout << "���ڸ� �Է��� �ּ��� : ";
    wcin >> wString;

    wcout << wString;

    // wstring�� stringd�� ����ִ� ���ڿ���
    // �츮�� ����� ���ڿ��� ���ϱ� ���ؼ���
    // �ش� ��ɵ� �ȿ� ����ִ� compare�Լ��� �̿��� ����Ѵ�.
    if (wString.compare(L"���ʻ����") || wString.compare(L"�ȳ�"))
    {
        cout << " �ݰ����ϴ�" << endl;
    }

}
