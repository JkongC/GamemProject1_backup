//type
#define OBJ_NORMAL 1
#define OBJ_MOVABLE 2

#define LIFE_INF -1

//不应该被直接创建，用NewObject然后强转
typedef struct obj {
	int ID;
	int type;
	int life;
	bool show;
	POINT pos;
	AnimationList* animation;
	int ani_sets;
	int current_ani_set_idx;
	clock_t ani_counter;
	int ani_frameidx;
} Object;

//不应该被直接创建，用NewObject然后强转
typedef struct movobj {
	Object;
	int counter;
	float velocity_X;
	float velocity_Y;
	float acceleration;
} MovableObject;

/*
typedef struct apple {
	Object;
	int color;
} Apple;
*/

int DistributeID(ListWithID* obj_list);

ObjTemplate RegisterObject(Registry* registry, int type, int life, int ani_sets, Animation* ani, ...);

void FreeObjects(ListWithID* obj_list);

void FreeObjectRegistry(Registry* registry);



void* NewObject(ObjTemplate src, int origin_x, int origin_y);

void* SearchObject(ListWithID* obj_list, const int ID);

void RemoveObjectByID(ListWithID* obj_list, const int ID);

void RemoveObject(ListWithID* obj_list, void* object);

void RenderObject(void* object);

int RenderObjectFromNode(Node* node);

void UpdateObject(void* object, clock_t delta);

int UpdateObjectFromNode(Node* node, clock_t delta);



void RenderAllObjects();

void TickAllObjects(clock_t delta);