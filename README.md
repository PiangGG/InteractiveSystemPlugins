# InteractiveSystemPlugins 这是一个简易的背包插件
<br>

![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/Icon128.png "Make From Piang")  
<br>

## 操作示例
<br>

### 在项目插件文件夹中加入本插件
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/AddFile.png "引入插件")  
虚幻引入插件的基本操作，不多赘述
<br>

### 编译之后在角色蓝图中加入插件
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/AddTo.png "角色添加插件") <br> 
给角色添加插件，在插件列表中搜索 **Pack**。<br>
<br>

### 创建蓝图可拾取的Item
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/CreateBPItem.png "创建可拾取的物体")  
创建角色可以拾取的物体<br>
创建蓝图类，继承自C++类 **Item** <br>
该物体用于放置在场景中或者生成在场景中<br>
<br>

### 编辑蓝图可拾取的Item
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/OpreatorItem.png "编辑属性")  
编辑属性，在蓝图属性栏中添加名字上图中以**Cube**为例<br>
添加插件中的 **DataTable** 到创建的Item蓝图中,（可自行创建多个**FPackItmeDataStruct**结构体的DataTable用于分类）。<br>
<br>

### 在对应DataTable中添加对应物体
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/PackableList.png "数据驱动")  
行命名对应添加蓝图属性 **Item命名** (代码通过这个属性查找,输入注意唯一)<br>
添加之后编辑对应属性:<br>
#### 结构体代码及对应属性解释
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/FPackItmeDataStructInCode.png "结构体解释图")  
<br>

### 可交互提示<br>
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/TrigerTest.png "靠近或对准")  
放置添加的蓝图Item到场景中，角色靠近，或在一定范围内屏幕中央，标注Item外轮廓为黄色<br>
如想更改外轮廓颜色，在插件材质目录中修改材质**M_Outline**里面的颜色<br>
#### 注意添加编辑场景中属性PostProcessVolume，使用该材质到PostProcessVolume中
建议:对应教程百度**UE4/5**，**outline**相关<br>

### 添加绑定按键

#### 绑定按键源代码
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/BindActionCode.png "源代码BindAction")

#### 引擎中绑定按键
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/BindActionCode.png "引擎中绑定按键")
本人习惯Tab键打开/关闭背包<br>
F交互蓝图Item(目前Item支持拾取)<br>
可根据个人习惯修改按键<br>

### 打开背包
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/OpenPack.png "使用绑定的按键切换背包状态")
如图已拾取的item已显示到背包中<br>
拖拽该空间到灰色区域，背包中物体从背包移除且添加到场景中<br>

#### 多个物体
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/RemoveFromPacks.png "移除多个物体从背包中")
如对应item为**单个物体**即表中bRepeat属性为**false**(未勾选'移除出背包时直接移除<br>
如对应item为**多个物体**即表中bRepeat属性为**true**(勾选)移除出背包时显示UI选择移除物体数量<br>
移除数量**大于等于**背包中数量,则全部移除(对应Item)<br>
移除数量**小于**背包中数量,则移除整数部分个数对应Item<br>

#### 移除之后场景中生成
![Image](https://github.com/PiangGG/InteractiveSystemPlugins/blob/Piang/Resources/AfterRemoveFromPacks.png "移除之后")

## 引入插件之后建议删除Resources文件夹下面的图片节省空间 

# 关注一下UP主吧！！！
[关注一下](https://space.bilibili.com/263564290 "UP主链接")
## 对应教程链接
[B站](https://www.bilibili.com/video/BV1A94y1d7kD "UP主链接")