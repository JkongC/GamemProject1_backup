#define LIFE_INF -1

enum Type {
	button = 0, player, enemy, npc
};

//��Ӧ�ñ�ֱ�Ӵ�������NewObject
typedef struct obj {
	int ID;
	clock_t life;  //����ʱ��
	enum Type type;  //��Ƕ������ͣ����������Ⱦ�͸����߼�
	bool show;  //�Ƿ���ʾ
	POINT pos;  //��ǰ����
	AnimationList* animation;  //�����б�
	int ani_sets;  //���������ж����׶�����
	int current_ani_set_idx;  //Ŀǰʹ�õ�����һ�׶���
	clock_t ani_counter;  //���ڸ��¶����ļ�ʱ��
	int ani_frameidx;  //Ŀǰ������֡����
} Object;

//��Ӧ�ñ�ֱ�Ӵ�������NewObject
typedef struct movobj {
	Object;
	clock_t time_counter;  //�����ٶȣ����������ļ�ʱ��
	float velocity_X;
	float velocity_Y;
	float acceleration;
} MovableObject;




//��������������ѡ��̳�Object��MovableObject
typedef struct ply {
	MovableObject;
} Player;




int DistributeID(ListWithID* obj_list);

ObjTemplate RegisterObject(Registry* registry, enum Type type, int life, int ani_sets,
	Animation* ani_1, ...);  //ע����󣬿��Դ�����׶�����ani_sets��ʾ�������������ض���ģ���ID

void FreeObjects(ListWithID* obj_list);

void FreeObjectRegistry(Registry* registry);



void* NewObject(ObjTemplate src, int origin_x, int origin_y);  //�½�����

void* SearchObject(ListWithID* obj_list, const int ID);  //��ID��������

void RemoveObjectByID(ListWithID* obj_list, const int ID);  //��IDɾ������

void RemoveObject(ListWithID* obj_list, void* object);  //��ָ��ɾ������

void RenderObject(void* object);  //��ָ����Ⱦ��������

int RenderObjectFromNode(Node* node);  //�ý����Ⱦ��������

void UpdateObject(void* object, clock_t delta);  //��ָ����µ�������

int UpdateObjectFromNode(Node* node, clock_t delta);  //�ý����µ�������



void RenderAllObjects();  //��Ⱦ��ǰ�������ж���

void TickAllObjects(clock_t delta);  //tick�����£���ǰ�������ж���

void RemoveAllObjects();  //�Ƴ���ǰ�������ж���



//����������͵��߼�
void Player_render(Player* player);

void Player_tick(Player* player, clock_t delta);