# 基本



## 图形方面

​	基本上是仿照原Easyx图形库函数写的，很多只是套了一层皮，在原函数后面添加一个C以作区分。以下是有必要特别说明的：

### 结构体

---

#### IMAGEC

---

```C
typedef struct IMAGEX {
    void* image;
} IMAGEC;
```

​	IMAGEC结构体是对Easyx的IMAGE类型的封装。由于C无法直接调用Easyx，故此处使用void指针存储所封装的IMAGE变量的地址。



#### ExMessageC

---

```C
typedef struct ExMessageX {
	void* ExMessage;
	unsigned short message;
	BYTE vkcode;
} ExMessageC;
```

​	ExMessageC结构体是对Easyx的ExMessage结构体类型的封装。与IMAGEC相似，它存储着对应的ExMessage变量的地址。message和vkcode对应的即是ExMessage结构体中的message和vkcode。其他的成员变量有待后续加入。





### 对Easyx在C的适配函数

---

​	在easyxC.h中可以看到全部声明，easyxC.cpp中是相应的实现。其中很多函数的参数由原版的IMAGE变量改为了IMAGEC变量以适配C。下面是需要特别说明的函数。



#### loadimageCR

---

```C
void loadimageCR(IMAGEC** pDstImg, LPCTSTR pResType, LPCTSTR pResName);
```

​	"R"表示这是loadimageC的加载rc资源文件的版本。需要注意的是这里传入的是IMAGEC的二级指针。它将指定的图片资源加载进提供的IMAGEC里。



#### putimageCS

---

```C
void putimageCS(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGEC* pSrcImg, int srcX, int srcY);
```

​	"S"表示这是putimageC的裁剪版本。与putimageC相比，多了dstWidth，dstHeight，srcX，srcY参数。其中：

- dstWidth: 目标矩形的宽度（即要画的区域宽度）
- dstHeight: 目标矩形的高度（即要画的区域高度）
- srcX: 源图像的起始宽度（即裁剪区域的左上角的X坐标）
- srcY: 源图像的起始高度（即裁剪区域的左上角的Y坐标）



#### imagec_getwidth和imagec_getheight

---

```C
int imagec_getwidth(IMAGEC* pImg);
int imagec_getheight(IMAGEC* pImg);
```

​	用于获取所提供的图像变量的宽高。



#### deleteimageC

---

```C
void deleteimageC(IMAGEC* pImg);
```

​	用于释放所提供IMAGEC结构体所对应的IMAGE对象的内存。由于IMAGE是在easyxC.cpp的C++实现里new出来的，因此需要通过这种方式释放。但一般不需要考虑，因为在后面提到的clearimageC函数内已经包含了此函数。



#### clearimageC

---

```C
void clearimageC();
```

​	由于在C++实现内，维护着一个存储现有IMAGEC的vector，因此游戏结束运行时可以通过此函数释放所有IMAGEC对象的内存。此函数的调用最好放在main.cpp的释放资源函数内。





### 功能变量/函数

---

​	这些变量/函数是用于处理游戏逻辑的。



#### 头文件 types.h

---

 	请注意，以下两个结构体使用柔性数组（结构体最后一个成员为不定长的数组），因此这两个结构体在创建时必须使用内存分配函数，且注意sizeof函数不会计入柔性数组的大小。创建方式如：

```C
Animations = (AnimationList*)malloc(sizeof(AnimationList) + size * sizeof(Animation*));
```

​	其中size为想要为柔性数组指定的大小。

​	对于AnimationList，由于其在主函数的LoadResources函数中进行，必须注意以上问题。对于Animation，由于其创建和移除已经被封装，可以不用太在意。（原则上不要自己创建Animation对象，而是先声明，然后传入相关函数中初始化）



##### 结构体Animation

---

```C
typedef struct ani {
	int interval; //帧切换时间间隔（毫秒）
	int counter; //计时器，表示从上次切换帧到目前的时间（毫秒）
	int frame_amounts; //动画帧总数
	int frame_index; //当前播放的帧索引
	int rc_head_index; //图集在资源文件中的第一个索引（在resource.h中可以看到）
	POINT pos; //动画的当前坐标
	IMAGEC* frames[];
} Animation;
```

​	用于存储单个动画对象。

​	关于`rc_head_index`：项目中的各种资源文件被记录到了Game.rc文件中，在其中可以看到PNG目录，其中有形如`IDB_PNG1`的文件名，对应着实际的资源文件。而在resource.h文件中，则可以看到他们对应的数字索引。因此，`rc_head_index`即为所需Animation中一系列图片的第一个文件的数字索引。如果只有一个文件，那么就是那一个文件的数字索引。

​	此结构体不要单独创建，通过`CreateAnimationTemplate`或`NewAnimationFrom`函数创建，且创建时严格检查动画帧（图片）的数量。



##### 结构体AnimationList

---

```C
typedef struct anilst {
	int capacity; //总容量
	int size; //列表内元素数
	Animation* list[];
} AnimationList;
```

​	存储的Animation的列表。



#### 源文件 main.c

---



##### 变量Templates

---

```C
AnimationList* Templates;
```

​	存储游戏过程中可能会用到的Animation模板。游戏启动时应通过CreateAnimationTemplate函数往里添加模板。后续需要创建动画对象时可以通过NewAnimationFrom函数从相应的模板创建新的Animation。



##### 变量Animations

---

```C
AnimationList* Animations;
```

​	存储游戏过程中由模板创建出来的Animation。可以通过RenderList函数绘出其中的所有Animation。



##### 时间相关变量

---

```C
clock_t start;
clock_t end;
clock_t delta;
```

​	帧开始和结束时获取当前时间戳，对应start和end。delta为两者之差。delta作为更新动画帧的时间参考，加入Animation的counter变量。delta还作为控制fps的依据。





#### 头文件 util.h

---



##### PushToList

---

```c
int PushToList(AnimationList** ani_list, Animation* ani);
```

​	将指定Animation加入指定AnimationList中。它是被封装的功能函数，可以不用。



##### RemoveFromList

---

```C
int RemoveFromList(AnimationList** ani_list, Animation* ani);
```

​	将指定Animation从指定AnimationList中移除。它是被封装的功能函数，可以不用。



##### FreeList

---

```C
void FreeList(AnimationList* ani_list);
```

​	释放指定AnimationList的内存。要在主文件中的FreeResources函数中调用。





#### 头文件 drawing.h

---



##### CreateAnimationTemplate

---

```C
int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int rc_head_index);
```

​	依照指定的数据，创建相应的动画模板，将其传入`new_ani`变量，并加入`templates`模板列表中。注意二级指针。



##### NewAnimationFrom

---

```C
int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);
```

​	按照指定的模板`src`，新建一个Animation，传入所给的`dst`中，然后加入ani_list列表中。通过`newX`和`newY`指定新Animation的初始坐标。注意二级指针。



##### RemoveAnimation

---

```C
int RemoveAnimation(AnimationList** ani_list, Animation* todel);
```

​	从指定的ani_list列表中，删除指定的Animation对象`todel`。注意二级指针。



##### Render

---

```C
void Render(Animation* animation);
```

​	绘出制定的Animation。另外，Animation对象动画帧的更新操作也在此函数内。



##### RenderList

---

```C
void RenderList(AnimationList* ani_list);
```

​	绘出指定的AnimationList中的所有Animation。实现上，此函数是对Render的循环调用。



##### UpdateList

---

```C
void UpdateList(AnimationList* ani_list, clock_t delta);
```

​	对指定的AnimationList中的所有Animation对象，将时间delta加入它们的counter计时器中，以供Render函数判断是否要更新动画帧。



