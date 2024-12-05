#pragma once

typedef struct ani {
	int interval; //֡�л�ʱ���������룩
	int counter; //��ʱ������ʾ���ϴ��л�֡��Ŀǰ��ʱ�䣨���룩
	int frame_amounts; //����֡����
	int frame_index; //��ǰ���ŵ�֡����
	int rc_head_index; //ͼ������Դ�ļ��еĵ�һ����������resource.h�п��Կ�����
	POINT pos; //�����ĵ�ǰ����
	IMAGEC* frames[];
} Animation;

typedef struct anilst {
	int capacity; //������
	int size; //�б���Ԫ����
	Animation* list[];
} AnimationList;