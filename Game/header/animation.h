#pragma once

typedef struct ani {
	int frame_amounts; //����֡����
	int interval;
	int width; //����֡��
	int height; //����֡��
	IMAGEC* atlas; //ͼ��
	POINT atlas_position; //��Ӧͼ���ڸ���ͼ��ͼƬ�е���ʼ�������꣨���Ͻǣ�
} Animation;

typedef struct anilst {
	int capacity; //������
	int size; //�б���Ԫ����
	Animation* list[];
} AnimationList;

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int atlas_position_x, int atlas_position_y, int rc_index, int width, int height, int scale);

int RemoveAnimation(AnimationList** ani_list, Animation* todel);

void RenderAnimation(Animation* animation, int frame_index, int pos_x, int pos_y);