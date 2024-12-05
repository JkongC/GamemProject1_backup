#pragma once

typedef struct ani {
	int interval; //帧切换时间间隔（毫秒）
	int counter; //计时器，表示从上次切换帧到目前的时间（毫秒）
	int frame_amounts; //动画帧总数
	int frame_index; //当前播放的帧索引
	int rc_head_index; //图集在资源文件中的第一个索引（在resource.h中可以看到）
	POINT pos; //动画的当前坐标
	IMAGEC* frames[];
} Animation;

typedef struct anilst {
	int capacity; //总容量
	int size; //列表内元素数
	Animation* list[];
} AnimationList;