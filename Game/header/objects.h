#define LIFE_INF -1

enum Type {
	button = 0, player, enemy, npc
};

//不应该被直接创建，用NewObject
typedef struct obj {
	int ID;
	clock_t life;  //存在时间
	enum Type type;  //标记对象类型，这决定了渲染和更新逻辑
	bool show;  //是否显示
	POINT pos;  //当前坐标
	AnimationList* animation;  //动画列表
	int ani_sets;  //动画数（有多少套动画）
	int current_ani_set_idx;  //目前使用的是哪一套动画
	clock_t ani_counter;  //用于更新动画的计时器
	int ani_frameidx;  //目前动画的帧索引
} Object;

//不应该被直接创建，用NewObject
typedef struct movobj {
	Object;
	clock_t time_counter;  //用于速度（或其他）的计时器
	float velocity_X;
	float velocity_Y;
	float acceleration;
} MovableObject;




//各类具体物件，可选择继承Object或MovableObject
typedef struct ply {
	MovableObject;
} Player;




int DistributeID(ListWithID* obj_list);

ObjTemplate RegisterObject(Registry* registry, enum Type type, int life, int ani_sets,
	Animation* ani_1, ...);  //注册对象，可以传入多套动画，ani_sets表示动画套数。返回对象模板的ID

void FreeObjects(ListWithID* obj_list);

void FreeObjectRegistry(Registry* registry);



void* NewObject(ObjTemplate src, int origin_x, int origin_y);  //新建对象

void* SearchObject(ListWithID* obj_list, const int ID);  //用ID搜索对象

void RemoveObjectByID(ListWithID* obj_list, const int ID);  //用ID删除对象

void RemoveObject(ListWithID* obj_list, void* object);  //用指针删除对象

void RenderObject(void* object);  //用指针渲染单个对象

int RenderObjectFromNode(Node* node);  //用结点渲染单个对象

void UpdateObject(void* object, clock_t delta);  //用指针更新单个对象

int UpdateObjectFromNode(Node* node, clock_t delta);  //用结点更新单个对象



void RenderAllObjects();  //渲染当前场景所有对象

void TickAllObjects(clock_t delta);  //tick（更新）当前场景所有对象

void RemoveAllObjects();  //移除当前场景所有对象



//具体对象类型的逻辑
void Player_render(Player* player);

void Player_tick(Player* player, clock_t delta);