#include "eapi.h"
#include "elib/fnshare.cpp"
#include"myhelp.h"
//结构体

// 接口常量  下的枚举常量成员数组
static LIB_DATA_TYPE_ELEMENT ApiConst[] =
{
	/*000*/ {SDT_INT, 0, "控制面板", "CONTROL_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*001*/ {SDT_INT, 0, "系统属性", "SYSTEM_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*002*/ {SDT_INT, 0, "显示属性", "DISPLAY_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*003*/ {SDT_INT, 0, "辅助功能选项", "ADD_OPTIONS_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*004*/ {SDT_INT, 0, "添加打印机向导", "ADD_PRINTER_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000004},
	/*005*/ {SDT_INT, 0, "添加或删除程序", "ADD_AND_DEL_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000005},
	/*006*/ {SDT_INT, 0, "日期和时间属性", "DATETIME_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000006},
	/*007*/ {SDT_INT, 0, "字体文件夹", "FONTSFOLDER_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000007},
	/*008*/ {SDT_INT, 0, "游戏控制器", "GAME_SET_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000008},
	/*009*/ {SDT_INT, 0, "鼠标属性", "MOUSE_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000009},
	/*010*/ {SDT_INT, 0, "键盘属性", "KEYBORAD_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000A},
	/*011*/ {SDT_INT, 0, "声音和音频属性", "MEDIA_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000B},
	/*012*/ {SDT_INT, 0, "ODBC数据源管理器", "ODBC_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000C},
	/*013*/ {SDT_INT, 0, "电源选项属性", "POWER_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000D},
	/*014*/ {SDT_INT, 0, "区域和语言选项", "LANGUAGE_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000E},
	/*015*/ {SDT_INT, 0, "互联网属性", "INTERNET_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x0000000F},
	/*016*/ {SDT_INT, 0, "用户帐号", "USERACCOUNT_WINDOWS", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000010},
	/*017*/ {SDT_INT, 0, "系统信息对话框", "SYSTEM_INFO_DLG", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000011},
	/*018*/ {SDT_INT, 0, "左键单击", "LeftClick", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*019*/ {SDT_INT, 0, "左键双击", "LeftDblClick", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*020*/ {SDT_INT, 0, "右键单击", "RightClick", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*021*/ {SDT_INT, 0, "右键双击", "RightDblClick", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*022*/ {SDT_INT, 0, "总物理内存", "PhysMemory", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*023*/ {SDT_INT, 0, "可用物理内存", "AvailPhysMemory", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*024*/ {SDT_INT, 0, "总虚拟内存", "VitualMemory", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*025*/ {SDT_INT, 0, "可用虚拟内存", "AvailVitualMemory", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*026*/ {SDT_INT, 0, "总页面文件", "PageFile", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000004},
	/*027*/ {SDT_INT, 0, "可用页面文件", "AvailPageFile", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000005},
	/*028*/ {SDT_INT, 0, "居中", "Center", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*029*/ {SDT_INT, 0, "平铺", "Tile", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*030*/ {SDT_INT, 0, "拉伸", "Stretch", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*031*/ {SDT_INT, 0, "所有驱动器", "AllDrives", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*032*/ {SDT_INT, 0, "硬盘驱动器", "HD", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*033*/ {SDT_INT, 0, "光盘驱动器", "CD-ROM", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*034*/ {SDT_INT, 0, "可移动驱动器", "Removable", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*035*/ {SDT_INT, 0, "系统临时文件", "Temp", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*036*/ {SDT_INT, 0, "IE临时文件", "IE Temp", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*037*/ {SDT_INT, 0, "回收站", "Recycle", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*038*/ {SDT_INT, 0, "存根文件", "Cookies", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*039*/ {SDT_INT, 0, "浏览器历史地址记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*040*/ {SDT_INT, 0, "表单自动完成历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*041*/ {SDT_INT, 0, "自动密码历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*042*/ {SDT_INT, 0, "收藏夹", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*043*/ {SDT_INT, 0, "自动拨号历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000004},
	/*044*/ {SDT_INT, 0, "运行中的自动匹配历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000005},
	/*045*/ {SDT_INT, 0, "打开文档历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000006},
	/*046*/ {SDT_INT, 0, "网络连接历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000007},
	/*047*/ {SDT_INT, 0, "远程登录历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000008},
	/*048*/ {SDT_INT, 0, "浏览网址历史记录", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000009},
	/*049*/ {SDT_INT, 0, "数字锁定键盘灯", "Num Lock", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*050*/ {SDT_INT, 0, "大小写锁定键盘灯", "Caps Lock", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*051*/ {SDT_INT, 0, "滚动锁定键盘灯", "Scroll Lock", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*052*/ {SDT_INT, 0, "像素", "UNIT_PT", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*053*/ {SDT_INT, 0, "英寸", "UNIT_INCH", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*054*/ {SDT_INT, 0, "毫米", "UNIT_MM", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*055*/ {SDT_INT, 0, "厘米", "UNIT_CM", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*056*/ {SDT_INT, 0, "到文件", "ToFile", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*057*/ {SDT_INT, 0, "到剪贴板", "ToClipboard", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*058*/ {SDT_INT, 0, "到字节集", "ToBin", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*059*/ {SDT_INT, 0, "磁盘0", "Primary Controller - Master drive", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*060*/ {SDT_INT, 0, "磁盘1", "Primary Controller - Slave drive", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*061*/ {SDT_INT, 0, "磁盘2", "Secondary Controller - Master drive", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*062*/ {SDT_INT, 0, "磁盘3", "Secondary Controller - Slave drive", NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000003},
	/*063*/ {SDT_INT, 0, "开始菜单", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*064*/ {SDT_INT, 0, "开始菜单程序", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*065*/ {SDT_INT, 0, "桌面", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*066*/ {SDT_INT, 0, "到注册表", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*067*/ {SDT_INT, 0, "到启动组", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*068*/ {SDT_INT, 0, "计算机", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*069*/ {SDT_INT, 0, "工作组", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*070*/ {SDT_INT, 0, "广播", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*071*/ {SDT_INT, 0, "所有共享资源", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*072*/ {SDT_INT, 0, "共享目录或文件", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*073*/ {SDT_INT, 0, "共享打印机", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},
	/*074*/ {SDT_INT, 0, "网络驱动器", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000004},
	/*075*/ {SDT_INT, 0, "标准打印设置对话框", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000000},
	/*076*/ {SDT_INT, 0, "打印对话框", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000001},
	/*077*/ {SDT_INT, 0, "打印属性对话框", NULL, NULL, LES_HAS_DEFAULT_VALUE, (INT)0x00000002},

};

static LIB_DATA_TYPE_ELEMENT Rect[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_INT, NULL,_T("左边"), _T("Left"), _T("left"), NULL, },
	{ SDT_INT, NULL,_T("顶边"), _T("Top"), _T("top"), NULL,  },
	{ SDT_INT, NULL,_T("右边"), _T("Right"), _T("right"), NULL,  },
	{ SDT_INT, NULL,_T("底边"), _T("Bottom"), _T("bottom"), NULL,  }
};
static LIB_DATA_TYPE_ELEMENT CpuInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("制造商"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("名称"), _T("ProcessorName"), NULL, NULL,  },
	{ SDT_INT, NULL,_T("时钟频率"), _T("ClockFrequency"), _T("单位：MHz"), NULL,  },
	{ SDT_TEXT, NULL,_T("描述"), _T("Description"),  NULL, NULL,  },
	{ SDT_INT, NULL,_T("一级缓存大小"), _T("L1 Size"), _T("单位：KB"), NULL,  },
	{ SDT_INT, NULL,_T("二级缓存大小"), _T("L2 Size"), _T("单位：KB"), NULL,  },
	{ SDT_TEXT, NULL,_T("序列号"), _T("SerialNumber"), NULL, NULL,  },
	{ SDT_INT, NULL,_T("数据宽度"), _T("bit"), _T("单位：位"), NULL,},
	{ SDT_INT, NULL,_T("三级缓存大小"), _T("L3 Size"), _T("单位：KB"), NULL,  },
	{ SDT_INT, NULL,_T("核心数"), _T("NumberOfCores"), _T("单位：KB"), NULL,  },
	{ SDT_INT, NULL,_T("线程数"), _T("ThreadCount"), _T("单位：KB"), NULL,  },
};
static LIB_DATA_TYPE_ELEMENT SysInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("操作系统"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("版本"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_INT, NULL,_T("编译版本"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_TEXT, NULL,_T("最后服务包"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_TEXT, NULL,_T("当前用户"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_TEXT, NULL,_T("系统安装目录"), _T("ProcessorName"), NULL, NULL,  },
		   { SDT_TEXT, NULL,_T("系统目录"), _T("ProcessorName"), NULL, NULL,  },
			 { SDT_INT, NULL,_T("代码"), _T("ProcessorName"), NULL, NULL,  },
				 { SDT_TEXT, NULL,_T("本地语言"), _T("ProcessorName"), NULL, NULL,  },
					 { SDT_INT, NULL,_T("国家代码"), _T("ProcessorName"), NULL, NULL,  },
						 { SDT_TEXT, NULL,_T("国家"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_TEXT, NULL,_T("货币符号"), _T("ProcessorName"), NULL, NULL,  },
	  { SDT_TEXT, NULL,_T("日期格式"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_TEXT, NULL,_T("时间格式"), _T("ProcessorName"), NULL, NULL,  },
			{ SDT_TEXT, NULL,_T("时区"), _T("ProcessorName"), NULL, NULL,  },
			{ SDT_TEXT, NULL,_T("国家ISO"), _T("ProcessorName"), NULL, NULL,  },
			{ SDT_BOOL, NULL,_T("是否为x64架构"), _T("ProcessorName"), NULL, NULL,  },
};
static LIB_DATA_TYPE_ELEMENT FileInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("文件版本"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("文件描述"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_TEXT, NULL,_T("内部名称"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_TEXT, NULL,_T("公司名称"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_TEXT, NULL,_T("合法版权"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_TEXT, NULL,_T("合法商标"), _T("ProcessorName"), NULL, NULL,  },
		   { SDT_TEXT, NULL,_T("源文件名"), _T("ProcessorName"), NULL, NULL,  },
			 { SDT_TEXT, NULL,_T("产品名称"), _T("ProcessorName"), NULL, NULL,  },
				 { SDT_TEXT, NULL,_T("产品版本"), _T("ProcessorName"), NULL, NULL,  },
					 { SDT_TEXT, NULL,_T("语言"), _T("ProcessorName"), NULL, NULL,  },
						 { SDT_TEXT, NULL,_T("备注"), _T("ProcessorName"), NULL, NULL,  },
						 { SDT_TEXT, NULL,_T("开发者构建"), _T("ProcessorName"), _T(" 个人编译版本说明"), NULL,},
								 { SDT_TEXT, NULL,_T("特殊构建"), _T("ProcessorName"),  _T(" 特殊编译版本说明"), NULL,  },

};
static LIB_DATA_TYPE_ELEMENT BiosInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("名称"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("制造商"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_TEXT, NULL,_T("版权信息"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_TEXT, NULL,_T("日期"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_TEXT, NULL,_T("序列号"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_TEXT, NULL,_T("OEM信息"), _T("ProcessorName"), NULL, NULL,  },
};
static LIB_DATA_TYPE_ELEMENT HDInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("型号"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("版本号"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_TEXT, NULL,_T("序列号"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_INT, NULL,_T("容量"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_INT, NULL,_T("缓存大小"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_INT, NULL,_T("每磁道扇区数"), _T("ProcessorName"), NULL, NULL,  },
			 { SDT_INT, NULL,_T("磁头数"), _T("NumHeaders"), NULL, NULL,  },
				 { SDT_INT, NULL,_T("柱面数"), _T("ProcessorName"), NULL, NULL,  },
};
static LIB_DATA_TYPE_ELEMENT NetCardInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("网卡名称"), _T("Vendor"), NULL, NULL, },
	{ SDT_INT, NULL,_T("序号"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_TEXT, NULL,_T("物理地址"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_TEXT, NULL,_T("IP地址"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_TEXT, NULL,_T("子网掩码"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_TEXT, NULL,_T("默认网关"), _T("ProcessorName"), NULL, NULL,  },
			 { SDT_TEXT, NULL,_T("Wins服务器地址"), _T("NumHeaders"), NULL, NULL,  },
				 { SDT_TEXT, NULL,_T("DHCP服务器地址"), _T("ProcessorName"), NULL, NULL,  },
};

static LIB_DATA_TYPE_ELEMENT ProcInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_INT, NULL,_T("进程标识符"), _T("Vendor"), NULL, NULL, },
	{ SDT_TEXT, NULL,_T("进程名称"), _T("ProcessorName"), NULL, NULL,  },
   { SDT_INT, NULL,_T("进程模块标识符"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_INT, NULL,_T("父进程标识符"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_INT, NULL,_T("线程优先权"), _T("ProcessorName"), NULL, NULL,  },
		 { SDT_INT, NULL,_T("线程数"), _T("ProcessorName"), NULL, NULL,  },
};
static LIB_DATA_TYPE_ELEMENT DisPlayInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
{ SDT_INT, NULL,_T("宽度"), _T("Vendor"), NULL, NULL, },
   { SDT_INT, NULL,_T("高度"), _T("ProcessorName"), NULL, NULL,  },
	 { SDT_INT, NULL,_T("颜色位数"), _T("ProcessorName"), NULL, NULL,  },
	   { SDT_INT, NULL,_T("刷新频率"), _T("ProcessorName"), NULL, NULL,  },
};
static LIB_DATA_TYPE_ELEMENT PrintInf[] =
{
	/*{ 成员类型 ,数组成员 , 中文名称 ,英文名称 ,成员解释 ,枚举类型 ,默认值}*/
	{ SDT_TEXT, NULL,_T("打印机名称"), _T("Vendor"), NULL, NULL, },
{ SDT_INT, NULL,_T("纸张方向"), _T("Vendor"), _T("指定打印纸的放置方向。可以为以下常量值之一： 1、#纵向； 2、#横向。如省略本参数，默认为“#纵向”。"), NULL,},
   { SDT_INT, NULL,_T("纸张类型"), _T("ProcessorName"), _T("指定所使用的打印纸类型。可以为以下常量值之一：-1、自定义纸张（必须在后面参数中指定自定义纸张的大小）； 0、#默认纸； 1、#A3纸(297x420毫米)； 2、#A4纸(210x297毫米)； 3、#A5纸(148x210毫米)； 4、#B4纸(250x354毫米)； 5、#B5纸(182x257毫米)； 6、#四开(215x275毫米)； 7、#十六开(146x215毫米)； 8、#三十二开(97x151毫米)； 9、#信纸(216x279毫米)； 10、#法律用纸(216x355毫米)； 11、#行政用纸(184x266毫米)； 12、#声明(140x216毫米)； 13、#小报(279x432毫米)； 14、#笔记(216x279毫米)； 15、#帐本(432x279毫米)； 16、#对开纸(216x330毫米)。"), NULL,},
	 { SDT_INT, NULL,_T("纸张宽度"), _T("ProcessorName"), _T("指定自定义纸张的宽度，单位为0.1毫米。只有当前面的“纸张”参数给定值为-1时，本参数才有作用且必须提供具体值。"), NULL,},
	   { SDT_INT, NULL,_T("纸张高度"), _T("ProcessorName"), _T("指定自定义纸张的高度，单位为0.1毫米。只有当前面的“纸张”参数给定值为-1时，本参数才有作用且必须提供具体值。"), NULL,},
{ SDT_INT, NULL,_T("打印份数"), _T("ProcessorName"), NULL, NULL,},

};
static LIB_DATA_TYPE_INFO DataTypes[] =
{
	/* { 中文名称, 英文名称, 数据描述, 索引数量, 命令索引, 对象状态, 图标索引, 事件数量, 事件指针, 属性数量, 属性指针, 界面指针, 元素数量, 元素指针 } */
	{ _WT("接口常量"), _WT("ApiConst"), _WT(""),NULL, NULL, _DT_OS(__OS_WIN) | LDT_ENUM,0, NULL, NULL,NULL, NULL,NULL,sizeof(ApiConst) / sizeof(LIB_DATA_TYPE_ELEMENT), ApiConst},
	{ _WT("矩形数据"), _WT("RECT"), _WT(""),0 , NULL, NULL, 0,0 , NULL,0 , NULL, NULL,sizeof(Rect) / sizeof(LIB_DATA_TYPE_ELEMENT), Rect },
	{ _WT("CPU信息"), _WT("CpuInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(CpuInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , CpuInf },
	  { _WT("系统信息"), _WT("CpuInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(SysInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , SysInf },
  { _WT("文件版本信息"), _WT("CpuInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(FileInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , FileInf },
	{ _WT("BIOS信息"), _WT("CpuInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(BiosInf) / sizeof(LIB_DATA_TYPE_ELEMENT) ,BiosInf },
	  { _WT("硬盘信息"), _WT("CpuInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(HDInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , HDInf },
		{ _WT("网卡信息"), _WT("NetCardInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(NetCardInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , NetCardInf },
  { _WT("进程信息"), _WT("ProcInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(ProcInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , ProcInf },
	{ _WT("显示模式信息"), _WT("DisPlayInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(DisPlayInf) / sizeof(LIB_DATA_TYPE_ELEMENT) ,DisPlayInf },
 { _WT("打印信息"), _WT("PrintInf"), _WT(""),0 , NULL, NULL,0 , 0, NULL,0 , NULL, NULL, sizeof(PrintInf) / sizeof(LIB_DATA_TYPE_ELEMENT) , PrintInf },


};
/*help*/
void* E_NULLARRAY()
{
	LPBYTE p = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2);
	*(LPINT)p = 1;  // 数组维数。
	*(LPINT)(p + sizeof(INT)) = 0;
	return p;
}
#if (_MSC_VER > 1600)
#pragma region  系统处理
#endif
#define DTP_PRINT   MAKELONG (11, 0)
#define DTP_RECT   MAKELONG (2, 0)
#define DTP_VIDEO   MAKELONG (10, 0)
#define DTP_NETWORK   MAKELONG (8, 0)
#define DTP_CPU   MAKELONG (3, 0)
#define DTP_HD   MAKELONG (7, 0) // 支持库里第一种数据类型
#define DTP_PROC   MAKELONG (9, 0)
#define DTP_SYS   MAKELONG (4, 0)
#define DTP_BIOS   MAKELONG (6, 0)
#define DTP_FILE   MAKELONG (5, 0)
//void  CallKrnlnFunc(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
//{
//	HMODULE hMoudle = LoadLibraryA("krnln.fne");
//	if (hMoudle)
//	{
//		typedef PLIB_INFO(WINAPI* FcGetNewInf)();
//		FcGetNewInf GetNewInf_ = (FcGetNewInf)GetProcAddress(hMoudle, "GetNewInf");
//		if (!GetNewInf)
//		{
//			MessageBoxA(0, "无法载入", 0, 0);
//		}
//		PLIB_INFO libInfo = GetNewInf_();
//		PCMD_INFO cmd = libInfo->m_pBeginCmdInfo;
//		int num = libInfo->m_nCmdCount;
//		for (int i = 0; i < num; i++)
//		{
//			bool bSuc = strcmp(cmd->m_szName, "输出调试文本");
//			if (!bSuc)
//			{
//				MessageBoxA(0, std::to_string((int)*libInfo->m_pCmdsFunc).c_str(), 0, 0);
//				(*libInfo->m_pCmdsFunc)(pRetData, iArgCount, pArgInf);
//			}
//		}
//		//Efuc = (void(__cdecl*)(PMDATA_INF, INT, PMDATA_INF))0x16B014C;
//		MessageBoxA(0, "TEST1", 0, 0);
//
//	}
//
//}

/*help*/
//void MyTrace(const char* text) {
//	PMDATA_INF TEXT = new MDATA_INF, ret = new MDATA_INF;;
//	TEXT->m_dtDataType = SDT_TEXT;
//	TEXT->m_pText = (char*)text;
//	CallKrnlnFunc(ret, 1, TEXT);
//	delete TEXT; delete ret;
//}

/*************************取键盘呢指示灯状态****************************/
static ARG_INFO GetKeyboardLockStateArg[] =
{
		{
		/*name*/	_WT("指示灯类别"),
		/*explain*/	_WT("可以被省略。键盘指示灯类别，为以下常量值之一：0、#接口常量.数字锁定键盘灯； 1、#接口常量.大小写锁定键盘灯； 2、#接口常量.滚动锁定键盘灯"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
			}
};
EXTERN_C void eapi_fnGetKeyboardLockState(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf) {

	int type = 0;
	if (pArgInf->m_dtDataType) {

		type = pArgInf->m_int;
	}
	pRetData->m_bool = GetKeyboardLockState(type);
}
/*************************模拟按键****************************/
static ARG_INFO SimulateKeyArg[] =
{
	  { _WT("虚拟键值1"), _WT(""),0 , 0,  _SDT_ALL, NULL, NULL },
	   { _WT("虚拟键值2"), _WT(""),0 , 0,  _SDT_ALL, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	   { _WT("虚拟键值3"), _WT(""),0 , 0,  _SDT_ALL, NULL, AS_DEFAULT_VALUE_IS_EMPTY }

};
EXTERN_C void eapi_fnSimulateKey(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf) {
	BYTE a = 0, b = 0, c = 0;
	//取键值
	if (pArgInf[0].m_dtDataType) {

		a = MyVkKeyScanExA(pArgInf[0]);
	}
	if (pArgInf[1].m_dtDataType) {

		b = MyVkKeyScanExA(pArgInf[1]);
	}
	if (pArgInf[2].m_dtDataType) {

		c = MyVkKeyScanExA(pArgInf[2]);
	}
	SimulateKey(a, b, c);
}
/*************************模拟鼠标点击****************************/
static ARG_INFO SimulateMouseArg[] =
{
	  { _WT("X坐标"), _WT(""),0 , 0, SDT_INT, NULL, NULL },
	   { _WT("Y坐标"), _WT(""),0 , 0,  SDT_INT, NULL, NULL },
	   { _WT("点击类型"), _WT("可以被省略。模拟鼠标点击的类型，可以为以下常量值之一：0、#接口常量.左键单击；1、#接口常量.左键双击；2、#接口常量.右键单击；3、#接口常量.右键双击。"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY }
};
EXTERN_C void eapi_fnSimulateMouse(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int type = 0;
	if (pArgInf[2].m_dtDataType)
		type = pArgInf[2].m_int;
	SimulateMouse(pArgInf[0].m_int, pArgInf[1].m_int, type);
}
/*************************取硬盘信息****************************/
static ARG_INFO GetHDInfoArg[] =
{
	  { _WT("硬盘信息"), _WT("待取得的硬盘信息"),0 , 0, DTP_HD, NULL, AS_RECEIVE_VAR },
	   { _WT("硬盘序号"), _WT("可以被省略。待取得的硬盘信息的硬盘序号。可以为以下常量之一：0、#接口常量.磁盘0；1、#接口常量.磁盘1；2、#接口常量.磁盘2；3、#接口常量.磁盘3。"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetHDInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	PHDINFO pHDInfo = *(PHDINFO*)pArgInf[0].m_pCompoundData;
	INT type = 0;
	if (pArgInf[1].m_dtDataType)
	{
		type = pArgInf[1].m_int;
	}
	pRetData->m_bool = GetHDInfo(pHDInfo, type);
}
/*************************取驱动器数量****************************/
static ARG_INFO GetDrivesNumArg[] =
{
	  { _WT("驱动器类型"), _WT("可以被省略。驱动器的类型，可以为以下常量值之一：0、#接口常量.所有驱动器；1、#接口常量.硬盘驱动器；2、#接口常量.光盘驱动器；3、#接口常量.可移动驱动器；4、#接口常量.网络驱动器。"),0 , 0, SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetDrivesNum(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT type = 0, ret = 0;
	if (pArgInf->m_dtDataType && pArgInf->m_int > 0 && pArgInf->m_int < 5)
	{
		type = pArgInf->m_int;
	}
	switch (type)
	{
	case 0:
		ret = GetDrivesNum(0);
		break;
	case 1:
		ret = GetDrivesNum(3);
		break;
	case 2:
		ret = GetDrivesNum(5);
		break;
	case 3:
		ret = GetDrivesNum(2);
		break;
	case 4:
		ret = GetDrivesNum(4);
		break;
	default:
		break;
	}

	pRetData->m_int = ret;
}

/*************************取驱动器列表****************************/

EXTERN_C void eapi_fnGetDrivesList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT type = 0, ret = 0;
	if (pArgInf->m_dtDataType && pArgInf->m_int > 0 && pArgInf->m_int < 5)
	{
		type = pArgInf->m_int;
	}

	vector<string> DriveList = GetDrivesList(type);
	if (DriveList.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * DriveList.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = DriveList.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = DriveList.begin(); temp != DriveList.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*************************弹出光驱****************************/

EXTERN_C void eapi_fnPopupCdrom(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	MCIERROR Error = ControlCdrom(1);
	SetLastError(Error);
	pRetData->m_bool = Error == 0;
}
/*************************关闭光驱****************************/
EXTERN_C void eapi_fnCloseCdrom(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	MCIERROR Error = ControlCdrom(0);
	SetLastError(Error);
	pRetData->m_bool = Error == 0;
}
/*************************取光驱盘符****************************/
EXTERN_C void eapi_fnGetCdrom(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_pText = GetCdrom();
}
/*************************光驱中是否有盘****************************/
EXTERN_C void eapi_fnIsDiskInside(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = IsDiskInside();
}
/*************************取系统进程列表****************************/
EXTERN_C void eapi_fnGetProcessList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<PROCINF> data = GetProcessList();
	if (data.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}
	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(LPPROCINF) * data.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = data.size();
	LPPROCINF* dretarry = (LPPROCINF*)(retarry + sizeof(INT) * 2);
	for (auto temp = data.begin(); temp != data.end(); temp++)
	{
		PROCINF copy = *temp;
		LPPROCINF tempproc = (LPPROCINF)eapi_MMalloc(sizeof(LPPROCINF));;
		memcpy(tempproc, &copy, sizeof(PROCINF));
		*dretarry = tempproc;
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}

/*************************终止进程****************************/
static ARG_INFO KillProcessArg[] =
{
	  { _WT("进程标识"), _WT("要终止进程的进程ID、进程名称或窗口标题。"),0 , 0, _SDT_ALL, NULL, NULL },
};
EXTERN_C void eapi_fnKillProcess(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	BOOL ret = FALSE;
	if (pArgInf->m_dtDataType == SDT_TEXT)
	{
		ret = KillProcess(pArgInf->m_pText);
	}
	else if (true)
	{
		ret = KillProcess(pArgInf->m_int);
	}

	pRetData->m_bool = ret;
}
/*************************取正在使用DLL列表****************************/
static ARG_INFO GetDllListArg[] =
{
	  { _WT("进程标识符"), _WT("要终止进程的进程ID、进程名称或窗口标题。置-1则取所有正在使用DLL列表。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetDllList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT ID = -1;
	if (pArgInf->m_dtDataType == SDT_INT)
	{
		ID = pArgInf->m_int;

	}
	vector<string> DLLList = GetDllList(ID);
	if (DLLList.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * DLLList.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = DLLList.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = DLLList.begin(); temp != DLLList.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*************************取没有响应程序列表****************************/

EXTERN_C void eapi_fnGetHungProgramList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<string> prolist = GetHungProgramList();
	if (prolist.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}
	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * prolist.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = prolist.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);
	for (auto temp = prolist.begin(); temp != prolist.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}

/*************************取系统信息****************************/
static ARG_INFO GetSystemInfoArg[] =
{
	  { _WT("系统信息"), _WT("待取得的系统信息。"),0 , 0, DTP_SYS, NULL, AS_RECEIVE_VAR },
};
EXTERN_C void eapi_fnGetSystemInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	PESYSINFO pHDInfo = *(PESYSINFO*)pArgInf[0].m_pCompoundData;
	INT type = 0;
	GetSysInfo(pHDInfo);
}

/*************************取BIOS信息****************************/
static ARG_INFO GetBiosInfoArg[] =
{
	  { _WT("BIOS信息"), _WT("待取得的系统信息。"),0 , 0, DTP_BIOS, NULL, AS_RECEIVE_VAR },
};
EXTERN_C void eapi_fnGetBiosInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	PEBIOSINFO pHDInfo = *(PEBIOSINFO*)pArgInf[0].m_pCompoundData;
	INT type = 0;
	GetBiosInfo(pHDInfo);
}
/*************************取文件信息****************************/
static ARG_INFO GetFileVersionInfoArg[] =
{ { _WT("文件名"), _WT("要取得版本信息的文件名。"),0 , 0,  SDT_TEXT, NULL, NULL },
	  { _WT("文件版本信息"), _WT("待取得的文件版本信息。"),0 , 0, DTP_FILE, NULL, AS_RECEIVE_VAR },
};
EXTERN_C void eapi_fnGetFileVersionInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	PEFileINfo pHDInfo = *(PEFileINfo*)pArgInf[1].m_pCompoundData;
	pRetData->m_bool = MyGetFileVersionInfo(pArgInf[0].m_pText, pHDInfo);
}
/*************************取cpu信息****************************/
static ARG_INFO GetCpuInfoArg[] =
{
	  { _WT("CPU信息"), _WT("待取得的CPU信息。"),0 , 0, DTP_CPU, NULL, AS_RECEIVE_VAR },
};
EXTERN_C void eapi_fnGetCpuInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	PCPUINFO pCpuInfo = *(PCPUINFO*)pArgInf[0].m_pCompoundData;
	pRetData->m_bool = GetCpuInfo(pCpuInfo);
}
/*************************取CPU占用率****************************/

EXTERN_C void eapi_fnGetCpuUsges(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = GetCpuUsges();
}
/*************************取内存容量信息****************************/
static ARG_INFO GetMemoryInfoArg[] =
{
	  { _WT("内存类型"), _WT("可以被省略。要取得的内存类型，可以为以下常量值之一：0、#接口常量.总物理内存；1、#接口常量.可用物理内存；2、#接口常量.总虚拟内存；3、#接口常量.可用虚拟内存；4、#接口常量.总页面文件；5、#接口常量.可用页面文件。"),0 , 0, SDT_INT, NULL,NULL },
};
EXTERN_C void eapi_fnGetMemoryInfo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT Type = 0;
	if (pArgInf->m_dtDataType == SDT_INT && pArgInf->m_int > 0 && pArgInf->m_int < 6)
	{
		Type = pArgInf->m_int;

	}
	pRetData->m_int = GetMemoryInfo(Type);
}
/*************************取声卡名称****************************/

EXTERN_C void eapi_fnGetAudioCard(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetAudioCard();
}
/*************************打开屏幕****************************/

EXTERN_C void eapi_fnOpenMonitor(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
}
/*************************打开屏幕****************************/

EXTERN_C void eapi_fnCloseMonitor(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

/*************************添加右键菜单****************************/
static ARG_INFO AddRightMenuArg[] =
{
	  { _WT("作用的区域或扩展名"), _WT("右键菜单在什么位置出现，例如指定:.txt,那么右键.txt文件时才会出现添加的菜单，“ * ”：所有地方 ；“D”：桌面右键；“URL”：文件夹右键；“SAVER”：文件右键；“.*”：指定后缀名右键，按照.*的格式写，不存在则创建（如.txt）,默认所有地方生效"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
 { _WT("右键菜单标题"), _WT("右键后显示的标题，同时为类名，删除时指定此参数即可"),0 , 0, SDT_TEXT, NULL,NULL },
	 { _WT("点击后执行的命令行"), _WT("点击右键菜单触发的命令，如在.txt文件添加\"用易运行\"并绑定命令 run e.exe 文件名 点击后就会指定运行命令行"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
{ _WT("快捷按键"), _WT("指定右键后载弹种按下某键可以快捷调用此菜单，直接填A-Z中的一个就好"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
{ _WT("图标路径"), _WT("指定图标路径,.ico图标路径/.exe程序路径，会自动读取图标"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
{ _WT("仅shift显示"), _WT("是否在只按住SHIFT的情况下显示（只在一级菜单中有效），默认为假"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY },

};
EXTERN_C void eapi_fnAddRightMenu(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string RangeOrExtName = "*", title, commandline, shortkey, icon;
	BOOL shiftdisplay = FALSE;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText)
	{
		RangeOrExtName = pArgInf[0].m_pText;

	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_pText)
	{
		title = pArgInf[1].m_pText;

	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_pText)
	{
		commandline = pArgInf[2].m_pText;

	}
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_pText)
	{
		shortkey = pArgInf[3].m_pText;

	}
	if (pArgInf[4].m_dtDataType && pArgInf[4].m_pText)
	{
		icon = pArgInf[4].m_pText;

	}
	if (pArgInf[5].m_dtDataType)
	{
		shiftdisplay = pArgInf[5].m_bool;
	}
	pRetData->m_bool = AddRightMenu(RangeOrExtName, title, commandline, shortkey, icon, shiftdisplay);
}
/*************************删除右键菜单****************************/
static ARG_INFO DeleteRightMenuArg[] =
{
	  { _WT("作用的区域或扩展名"), _WT("右键菜单在什么位置出现，例如指定:.txt,那么右键.txt文件时才会出现添加的菜单，“ * ”：所有地方 ；“D”：桌面右键；“URL”：文件夹右键；“SAVER”：文件右键；“.*”：指定后缀名右键，按照.*的格式写，不存在则创建（如.txt）,默认所有地方生效"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
 { _WT("右键菜单标题"), _WT("右键后显示的标题，同时为类名，删除时指定此参数即可"),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void eapi_fnDeleteRightMenu(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string RangeOrExtName = "*", title;
	BOOL shiftdisplay = FALSE;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText)
	{
		RangeOrExtName = pArgInf[0].m_pText;

	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_pText)
	{
		title = pArgInf[1].m_pText;

	}
	pRetData->m_bool = DeleteRightMenu(RangeOrExtName, title);
}
/*************************设置自动运行****************************/
static ARG_INFO SetAutoRunArg[] =
{
	  { _WT("程序类名"), _WT("程序类名、置于启动组或者注册表中的名称"),0 , 0, SDT_TEXT, NULL,NULL },
 { _WT("程序路径"), _WT("要设置为自动运行的程序文件名（包含绝对路径）。"),0 , 0, SDT_TEXT, NULL,NULL },
{ _WT("位置"), _WT("可以被省略。为以下常量值之一：0、#接口常量.到注册表；1、#接口常量.到启动组。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },

};
EXTERN_C void eapi_fnSetAutoRun(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string Name, Path;
	BOOL isres = TRUE;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText)
	{
		Name = pArgInf[0].m_pText;

	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_pText)
	{
		Path = pArgInf[1].m_pText;

	}
	if (pArgInf[2].m_dtDataType)
	{
		isres = pArgInf[2].m_int == 0 ? TRUE : FALSE;
	}
	pRetData->m_bool = SetAutoRun(Name, Path, isres);
}
/*************************设置自动运行****************************/
static ARG_INFO DeleteTempFileArg[] =
{
	  { _WT("临时文件类型"), _WT("可以被省略。临时文件类型，可以为以下常量值之一：0、#接口常量.系统临时文件；1、#接口常量.IE临时文件；2、#接口常量.回收站；3、#接口常量.存根文件。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnDeleteTempFile(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	signed int type = 0;;
	if (pArgInf->m_dtDataType || pArgInf->m_int >= 0 || pArgInf->m_int <= 3) {

		type = pArgInf->m_int;
	}
	pRetData->m_bool = DeleteTempFile(type);
}
/*************************删除历史记录****************************/
static ARG_INFO ClearHistoryArg[] =
{
	  { _WT("历史记录类型"), _WT("可以被省略。历史记录类型，可以为以下常量值之一：0、#接口常量.浏览器历史地址记录；1、#接口常量.表单自动完成历史记录；2、#接口常量.自动密码历史记录；3、#接口常量.收藏夹；4、#接口常量.自动拨号历史记录；5、#接口常量.运行中的自动匹配历史记录；6、#接口常量.打开文档历史记录；7、#接口常量.网络连接历史记录；8、#接口常量.远程登录历史记录；9、#接口常量.浏览网址历史记录。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnClearHistory(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	signed int type = 0;;
	if (pArgInf->m_dtDataType || pArgInf->m_int >= 0 || pArgInf->m_int <= 9) {

		type = pArgInf->m_int;
	}
	pRetData->m_bool = ClearHistory(type);
}
/*************************取字体列表****************************/

EXTERN_C void eapi_fnGetFontList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<string> FontList = GetFontListA();
	if (FontList.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * FontList.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = FontList.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = FontList.begin(); temp != FontList.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*************************安装字体****************************/
static ARG_INFO AddFontArg[] =
{
	  { _WT("字体文件名或字体资源"), _WT("字体资源文件的文件名。可以是.FON，.FNT，.TTF或.FOT文件。或者字体资源"),0 , 0, _SDT_ALL, NULL,NULL },
};
EXTERN_C void eapi_fnAddFont(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && pArgInf->m_pText) {

		pRetData->m_int = AddFont(pArgInf->m_pText);
	}
	else if (pArgInf->m_dtDataType == SDT_BIN)
	{
		pRetData->m_int = (intptr_t)AddFont(pArgInf->m_pBin);
	}
	else
	{
		pRetData->m_int = 0;
	}
}
/*************************删除字体****************************/
static ARG_INFO RemoveFontArg[] =
{
	  { _WT("字体名或字体句柄"), _WT("字体资源文件的文件名。可以是.FON，.FNT，.TTF或.FOT文件。或者字体资源"),0 , 0, _SDT_ALL, NULL,NULL },
};
EXTERN_C void eapi_fnRemoveFont(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && pArgInf->m_pText) {

		pRetData->m_bool = RemoveFont(pArgInf->m_pText);
	}
	else if (pArgInf->m_dtDataType == SDT_INT)
	{
		pRetData->m_bool = RemoveFont((void*)pArgInf->m_int);
	}
	else
	{
		pRetData->m_bool = 0;
	}
}


/*************************取图片宽度****************************/
static ARG_INFO GetImageWidthArg[] =
{
	  { _WT("图片资源或图片路径"), _WT("图片路径或资源"),0 , 0, _SDT_ALL, NULL,NULL },
};
EXTERN_C void eapi_fnGetImageWidth(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && pArgInf->m_pText) {

		pRetData->m_int = GetImageSize(pArgInf->m_pText).cx;
	}
	else if (pArgInf->m_dtDataType == SDT_BIN)
	{

		pRetData->m_int = GetImageSize(pArgInf->m_pBin).cx;
	}
	else
	{
		pRetData->m_int = 0;
	}
}
/*************************取图片高度****************************/

EXTERN_C void eapi_fnGetImageHeight(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && pArgInf->m_pText) {

		pRetData->m_int = GetImageSize(pArgInf->m_pText).cy;
	}
	else if (pArgInf->m_dtDataType == SDT_BIN)
	{

		pRetData->m_int = GetImageSize(pArgInf->m_pBin).cy;
	}
	else
	{
		pRetData->m_int = 0;
	}
}

/*************************提取资源文件****************************/
static ARG_INFO GetIconFromResourceArg[] =
{
	  { _WT("资源文件名"), _WT("要提取图标的资源文件名。扩展名为EXE、DLL、ICL、ICO。"),0 , 0, SDT_TEXT, NULL, NULL },
 { _WT("是否提取到剪辑板"), _WT("0为假其余为真，兼容之前易库,默认为假"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
	 { _WT("保存文件名"), _WT("如需要提取到文件则填写提取的图标要保存的文件名。扩展名为ICO、BMP。，默认为空"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
{ _WT("图标序号"), _WT("当资源文件中包含多个图标时，表示要提取图标的序号。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetIconFromResource(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string FileNmae, SaveFileName;
	BOOL ToClipBar = FALSE;
	DWORD Index = 1;
	if (pArgInf->m_pText) {

		FileNmae = pArgInf->m_pText;
	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int != 0)
	{

		ToClipBar = TRUE;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_pText)
	{

		SaveFileName = pArgInf[2].m_pText;
	}
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_int >= 0)
	{
		Index = pArgInf[3].m_int;
	}
	pRetData->m_int = GetIconFromResource(FileNmae, ToClipBar, SaveFileName, Index);
}
/*************************取IE版本号****************************/

EXTERN_C void eapi_fnGetIEVersion(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetIEVersion();
}
/*************************取IE版本号****************************/


static ARG_INFO AddButtonToIEArg[] =
{
	  { _WT("按钮文字"), _WT("标题"),0 , 0, SDT_TEXT, NULL, NULL },
  { _WT("图标文件名"), _WT("图标路径"),0 , 0, SDT_TEXT, NULL, NULL },
	  { _WT("执行动作"), _WT("在IE中按下按钮后执行一个可执行文件或打开网页，就是命令行。"),0 , 0, SDT_TEXT, NULL, NULL },
  { _WT("按钮热点图标"), _WT("按钮处于热点状态显示的图标，默认不变更"),0 , 0, SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	{ _WT("按钮是否被显示"), _WT("是否在工具栏显示，默认为真"),0 , 0, SDT_BOOL, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnAddButtonToIE(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string ButtonTitle, Icon, Comline, HotButton;
	BOOL IsVisible = TRUE;

	if (pArgInf->m_pText) {

		ButtonTitle = pArgInf->m_pText;
	}
	if (pArgInf[1].m_pText)
	{
		Icon = pArgInf[1].m_pText;
		HotButton = pArgInf[1].m_pText;
	}
	if (pArgInf[2].m_pText)
	{
		Comline = pArgInf[2].m_pText;
	}
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_bool == FALSE)
	{
		IsVisible = FALSE;
	}
	pRetData->m_bool = AddButtonToIE(ButtonTitle, Icon, Comline, HotButton, IsVisible);
}
/*************************取图片宽度****************************/
static ARG_INFO DeleteButtonFromIEArg[] =
{
	  { _WT("按钮文字"), _WT(""),0 , 0, _SDT_ALL, NULL,NULL },
};
EXTERN_C void eapi_fnDeleteButtonFromIE(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && pArgInf->m_pText) {

		pRetData->m_bool = DeleteButtonFromIE(pArgInf->m_pText);
	}

}
/*************************创建程序组****************************/
static ARG_INFO CreateProgramGroupArg[] =
{
	{ _WT("文件夹名称"), _WT("要创建的程序组名称。"),0 , 0, SDT_TEXT, NULL,NULL },
	  { _WT("特殊目录位置"), _WT("程序组的起始位置。可以为以下常量值之一：0、#接口常量.开始菜单；1、#接口常量.开始菜单程序；2、#接口常量.桌面。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnCreateProgramGroup(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int pos = 11;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int) {

		if (pArgInf[1].m_int == 2)
		{
			int pos = 16;
		}
		else if (pArgInf[1].m_int == 2)
		{
			int pos = 2;
		}
	}
	pRetData->m_bool = CreateProgramGroup(pArgInf->m_pText, pos);
}
/*************************删除程序组****************************/
static ARG_INFO DeleteProgramGroupArg[] =
{
	{ _WT("文件夹名称"), _WT("要删除的程序组名称。"),0 , 0, SDT_TEXT, NULL,NULL },
	  { _WT("特殊目录位置"), _WT("程序组的起始位置。可以为以下常量值之一：0、#接口常量.开始菜单；1、#接口常量.开始菜单程序；2、#接口常量.桌面。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnDeleteProgramGroup(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int pos = 11;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int) {

		if (pArgInf[1].m_int == 2)
		{
			int pos = 16;
		}
		else if (pArgInf[1].m_int == 2)
		{
			int pos = 2;
		}
	}
	pRetData->m_bool = CreateProgramGroup(pArgInf->m_pText, pos);
}
/*************************删除程序项****************************/
static ARG_INFO DeleteProgramItemArg[] =
{
	{ _WT("程序组文件夹"), _WT("要创建的快捷方式的程序组文件夹名称，非路径。"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("程序项文件夹"), _WT("要创建的快捷方式名称"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("特殊目录位置"), _WT("程序组的起始位置。可以为以下常量值之一：0、#接口常量.开始菜单；1、#接口常量.开始菜单程序；2、#接口常量.桌面。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnDeleteProgramItem(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int pos = 11;
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_int) {

		if (pArgInf[2].m_int == 2)
		{
			int pos = 16;
		}
		else if (pArgInf[2].m_int == 2)
		{
			int pos = 2;
		}
	}
	pRetData->m_bool = DeleteProgramItem(pArgInf->m_pText, pArgInf[1].m_pText, pos);
}
/*************************创建程序组****************************/
static ARG_INFO CreateProgramItemArg[] =
{
	{ _WT("程序组文件夹"), _WT("要创建的快捷方式的程序组文件夹名称，非路径。"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("程序项文件夹"), _WT("要创建的快捷方式名称"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("快捷方式链接的程序路径"), _WT("绑定执行程序文件名的路径。"),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("特殊目录位置"), _WT("程序组的起始位置。可以为以下常量值之一：0、#接口常量.开始菜单；1、#接口常量.开始菜单程序；2、#接口常量.桌面。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnCreateProgramItem(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int pos = 11;
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_int) {

		if (pArgInf[3].m_int == 2)
		{
			int pos = 16;
		}
		else if (pArgInf[3].m_int == 2)
		{
			int pos = 2;
		}
	}
	pRetData->m_bool = CreateProgramItem(pArgInf->m_pText, pArgInf[1].m_pText, pArgInf[2].m_pText, pos);
}
/*************************取快捷方式目标****************************/
static ARG_INFO GetShortCutTargetArg[] =
{
	{ _WT("快捷方式文件名"), _WT(""),0 , 0, SDT_TEXT, NULL,NULL },
	{ _WT("目标"), _WT("快捷方式文件名绑定的程序路径"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR},
		{ _WT("参数"), _WT("默认参数"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR },
	{ _WT("启始位置"), _WT("快捷方式的上级目录"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR},
	{ _WT("图标"), _WT("返回的文本格式为：图标所属文件 + , + 图标序号（0为第一个），例如：“c:\\x.exe,1”。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR},
	{ _WT("运行方式"), _WT("。1：常规窗口；2：最小化；3：最大化"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR},
{ _WT("快捷键"), _WT("可以传入文本型或整数型型变量。如果为文本型，返回快捷键文本形式，如“Ctrl + Shift + Alt + A”。如果为整数型，返回一个表示该快捷键的数值（参见http://msdn.microsoft.com/en-us/library/bb774926"),0 , 0, _SDT_ALL, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR },
{ _WT("备注"), _WT("快捷方式的描述"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR},

};
EXTERN_C void eapi_fnGetShortCutTarget(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{


	wstring Name, Path, Arg, Dir, Icon, KeyStr, Remark; int RunMode = 0, Key = 0;
	if (pArgInf[0].m_dtDataType == SDT_TEXT && pArgInf[0].m_pText)
	{
		Name = A2W(pArgInf[0].m_pText);
	}
	else
	{
		return;
	}

	if (pArgInf[6].m_dtDataType == SDT_TEXT)
	{
		GetShortCutTarget(Name, &Path, &Arg, &Dir, &Icon, &RunMode, &KeyStr, &Remark);

	}
	else
	{
		GetShortCutTarget(Name, &Path, &Arg, &Dir, &Icon, &RunMode, &Key, &Remark);

	}
	pRetData->m_pText = W2Estr(Path);

	if (pArgInf[1].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 1;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText = W2Estr(Path);;
	}
	if (pArgInf[2].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 2;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText = W2Estr(Arg);;
	}
	if (pArgInf[3].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 3;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText = W2Estr(Dir);;
	}
	if (pArgInf[4].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 4;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText = W2Estr(Icon);;
	}
	if (pArgInf[5].m_dtDataType == SDT_INT)
	{
		PMDATA_INF pInf = pArgInf + 5;
		*pInf->m_pInt = RunMode;
	}

	if (pArgInf[6].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 6;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText = W2Estr(KeyStr);
	}
	else if (pArgInf[6].m_dtDataType == SDT_INT)
	{
		PMDATA_INF pInf = pArgInf + 6;
		*pInf->m_pInt = Key;
	}

	if (pArgInf[7].m_dtDataType == SDT_TEXT)
	{
		PMDATA_INF pInf = pArgInf + 7;
		eapi_MFree(*pInf->m_ppText);
		*pInf->m_ppText == W2Estr(Remark);
	}

}

/*/************************取消自动运行****************************/
static ARG_INFO CancelAutoRunArg[] =
{
	{ _WT("程序名"), _WT("设置自动运行时的程序名称。"),0 , 0, SDT_TEXT, NULL,NULL },
};
EXTERN_C void eapi_fnCancelAutoRun(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = CancelAutoRun(pArgInf->m_pText);
}

/*/************************取网卡信息列表****************************/
static ARG_INFO sprintfArg[] =
{
	{ _WT("格式化字符串"), _WT("设置自动运行时的程序名称。"),0 , 0, _SDT_ALL, NULL,NULL },
		{ _WT("格式化字符串"), _WT("设置自动运行时的程序名称。"),0 , 0, _SDT_ALL, NULL,NULL },
};
EXTERN_C void eapi_fnsprintf(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	if (pArgInf->m_dtDataType == SDT_TEXT && strlen(pArgInf->m_pText) > 0) {

		pRetData->m_dtDataType = SDT_TEXT;
		int previous = strlen(pArgInf->m_pText);
		char* Ret = new char[previous + 1];
		strcpy(Ret, pArgInf->m_pText);
		if (iArgCount > 1)
		{
			for (size_t i = 1; i <= iArgCount - 1; i++)
			{
				string temp;
				char* tempstr = 0;

				if (pArgInf[i].m_dtDataType == SDT_FLOAT) {

					temp = to_string(pArgInf[i].m_float);
					tempstr = new char[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_INT) {

					temp = to_string(pArgInf[i].m_int);
					tempstr = new char[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_DOUBLE) {

					temp = to_string(pArgInf[i].m_double);
					tempstr = new char[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_BOOL) {

					temp = to_string(pArgInf[i].m_bool);
					tempstr = new char[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_INT64) {

					temp = to_string(pArgInf[i].m_int64);
					tempstr = new char[previous + temp.size() + 1];
				}
				if (pArgInf[i].m_dtDataType == SDT_BYTE) {

					temp = to_string(pArgInf[i].m_byte);
					tempstr = new char[previous + temp.size() + 1];
				}
				if (pArgInf[i].m_dtDataType == SDT_BIN) {
					VECTORBYTE BIN = GetEbin(pArgInf[i].m_pBin);
					if (BIN.data && BIN.size > 0)
					{
						temp = string((char*)BIN.data, BIN.size);
						tempstr = new char[previous + temp.size() + 1];
					}
				}
				if (pArgInf[i].m_dtDataType == SDT_TEXT) {
					if (pArgInf[i].m_pText && strlen(pArgInf[i].m_pText) > 0)
					{
						temp = string(pArgInf[i].m_pText);
						tempstr = new char[previous + temp.size() + 1];
					}
				}
				if (tempstr)
				{
					if (Ret) {
						strcpy(tempstr, Ret);
						delete[]Ret;
					}
					sprintf(tempstr, temp.c_str());
					previous = strlen(tempstr);
					Ret = tempstr;
				}

			}
		}
		if (Ret)
		{
			pRetData->m_pText = eapi_CloneTextData(Ret);
			delete[]Ret;
			return;
		}

	}
	if (pArgInf->m_dtDataType == SDT_BIN) {
		pRetData->m_dtDataType = SDT_BIN;
		VECTORBYTE DATA = GetEbin(pArgInf->m_pBin);
		wstring Get = wstring((WCHAR*)DATA.data, DATA.size / sizeof(wchar_t));
		int previous = Get.size();
		WCHAR* Ret = new WCHAR[previous + 1];
		wcscpy(Ret, Get.c_str());
		if (iArgCount > 1)
		{
			for (size_t i = 1; i <= iArgCount - 1; i++)
			{
				wstring temp;
				WCHAR* tempstr = 0;

				if (pArgInf[i].m_dtDataType == SDT_FLOAT) {

					temp = to_wstring(pArgInf[i].m_float);
					tempstr = new WCHAR[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_INT) {

					temp = to_wstring(pArgInf[i].m_int);
					tempstr = new WCHAR[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_DOUBLE) {

					temp = to_wstring(pArgInf[i].m_double);
					tempstr = new WCHAR[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_BOOL) {

					temp = to_wstring(pArgInf[i].m_bool);
					tempstr = new WCHAR[previous + temp.size() + 1];

				}
				if (pArgInf[i].m_dtDataType == SDT_INT64) {

					temp = to_wstring(pArgInf[i].m_int64);
					tempstr = new WCHAR[previous + temp.size() + 1];
				}
				if (pArgInf[i].m_dtDataType == SDT_BYTE) {

					temp = to_wstring(pArgInf[i].m_byte);
					tempstr = new WCHAR[previous + temp.size() + 1];
				}
				if (pArgInf[i].m_dtDataType == SDT_BIN) {
					VECTORBYTE BIN = GetEbin(pArgInf[i].m_pBin);
					if (BIN.data && BIN.size > 0)
					{
						temp = wstring((WCHAR*)BIN.data, BIN.size / sizeof(wchar_t));
						tempstr = new WCHAR[previous + temp.size() + 1];
					}
				}
				if (pArgInf[i].m_dtDataType == SDT_TEXT) {
					if (pArgInf[i].m_pText && strlen(pArgInf[i].m_pText) > 0)
					{
						temp = A2W(string(pArgInf[i].m_pText));
						tempstr = new WCHAR[previous + temp.size() + 1];
					}
				}
				if (tempstr)
				{
					if (Ret) {
						wcscpy(tempstr, Ret);
						delete[]Ret;
					}
					swprintf(tempstr, temp.c_str());
					previous = wcslen(tempstr);
					Ret = tempstr;
				}

			}
		}
		if (Ret)
		{

			pRetData->m_pBin = eapi_CloneBinData((LPBYTE)Ret, previous * sizeof(wchar_t));
			delete[]Ret;
			return;
		}

	}
	else
	{
		pRetData->m_dtDataType = SDT_TEXT;
		pRetData->m_pText = 0;
	}
}

/*************************取网卡信息列表****************************/
EXTERN_C void eapi_fnGetApapterList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<_NETWORKINFO> data = GetApapterList();
	if (data.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}
	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(PNETWORKINFO) * data.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = data.size();
	PNETWORKINFO* dretarry = (PNETWORKINFO*)(retarry + sizeof(INT) * 2);
	for (auto temp = data.begin(); temp != data.end(); temp++)
	{
		_NETWORKINFO copy = *temp;
		PNETWORKINFO tempproc = (PNETWORKINFO)eapi_MMalloc(sizeof(PNETWORKINFO));;
		memcpy(tempproc, &copy, sizeof(_NETWORKINFO));
		*dretarry = tempproc;
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*/************************取本机网卡名****************************/
static ARG_INFO GetLocalAdapterNameArg[] =
{
	{ _WT("网卡序号"), _WT("可以被省略。当本机有多块网卡时，指定要对其操作的网卡序号（从1开始）。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnGetLocalAdapterName(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int NetIndex = 1;
	if (pArgInf->m_dtDataType && pArgInf->m_int > 1)
	{
		NetIndex = pArgInf->m_int;
	}
	pRetData->m_pText = GetLocalAdapterName(NetIndex);
}
/*/************************取本机物理网卡地址****************************/
EXTERN_C void eapi_fnGetLocalMac(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int NetIndex = 1;
	if (pArgInf->m_dtDataType && pArgInf->m_int > 1)
	{
		NetIndex = pArgInf->m_int;
	}
	pRetData->m_pText = GetLocalMac(NetIndex);
}

/*/************************取远程网卡物理地址****************************/
static ARG_INFO GetRemoteMacArg[] =
{
	{ _WT("IP地址"), _WT(""),0 , 0, SDT_TEXT, NULL,0},
};
EXTERN_C void eapi_fnGetRemoteMac(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetRemoteMac(pArgInf->m_pText);
}
/*/************************取远程机器名****************************/
static ARG_INFO GetRemoteNameArg[] =
{
	{ _WT("IP地址"), _WT(""),0 , 0, SDT_TEXT, NULL,0},
};
EXTERN_C void eapi_fnGetRemoteName(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = GetRemoteName(pArgInf->m_pText);
}
/*/************************取IP地址****************************/
static ARG_INFO GetIpFromHostNameArg[] =
{
	{ _WT("机器名"), _WT(""),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnGetIpFromHostName(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	char* MachineName = 0;
	if (pArgInf->m_dtDataType && strlen(pArgInf->m_pText) > 0)
	{
		MachineName = pArgInf->m_pText;
	}
	pRetData->m_pText = GetIpFromHostName(pArgInf->m_pText);
}
/*/************************撰写邮件****************************/
static ARG_INFO RunEmailAddrArg[] =
{
	{ _WT("Email地址"), _WT("目标Email地址"),0 , 0, SDT_TEXT, NULL,NULL},
};
EXTERN_C void eapi_fnRunEmailAddr(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string Target = "mailto:";
	if (pArgInf->m_pText)
	{
		Target += pArgInf->m_pText;
	}
	ShellExecuteA(0, "open", Target.c_str(), 0, 0, 1);
}



/**************************取网络类型列表*******************************/
EXTERN_C void eapi_fnGetNetList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	vector<string> List = GetNetList();
	if (List.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * List.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = List.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);
	for (auto temp = List.begin(); temp != List.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/**************************取网络工作组列表*******************************/

static ARG_INFO GetGroupListArg[] =
{
	  { _WT("网络类型"), _WT("网络类型名，为空则取所有工作组。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetGroupList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string type;
	if (pArgInf->m_dtDataType == SDT_TEXT)
	{
		type = pArgInf->m_int;

	}
	vector<string> List = GetGroupList(type);
	if (List.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * List.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = List.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = List.begin(); temp != List.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/**************************取网络计算机列表*******************************/
static ARG_INFO GetComputerListArg[] =
{
	  { _WT("工作组名称"), _WT("工作组名称，为空则取所有计算机。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY },
};
EXTERN_C void eapi_fnGetComputerList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string type;
	if (pArgInf->m_dtDataType == SDT_TEXT)
	{
		type = pArgInf->m_int;

	}
	vector<string> List = GetComputerList(type);
	if (List.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * List.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = List.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = List.begin(); temp != List.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}

/**************************是否联网*******************************/

EXTERN_C void eapi_fnIsConnectToInternet(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_bool = IsConnectToInternet();
}
/**************************端口检测*******************************/

static ARG_INFO CheckPortArg[] =
{
	{ _WT("端口"), _WT("检测的端口。"),0 , 0, SDT_SHORT, NULL,NULL},
	{ _WT("ip地址"), _WT("置空则检测本机端口。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnCheckPort(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	char* IP = 0;
	if (pArgInf[1].m_dtDataType && strlen(pArgInf[1].m_pText) > 0)
	{
		IP = pArgInf[1].m_pText;
	}
	pRetData->m_bool = CheckPort(pArgInf->m_short, IP);
}
/**************************打开特殊系统窗口*******************************/

static ARG_INFO OpenSysWindowArg[] =
{
	{ _WT("窗口类型"), _WT("系统窗口类型，为以下常量值之一：0、#接口常量.控制面板；1、#接口常量.系统属性；2、#接口常量.显示属性；3、#接口常量.辅助功能选项；4、#接口常量.添加打印机向导；5、#接口常量.添加或删除程序；6、#接口常量.日期和时间属性；7、#接口常量.字体文件夹；8、#接口常量.游戏控制器；9、#接口常量.鼠标属性；10、#接口常量.键盘属性；11、#接口常量.声音和音频属性；12、#接口常量.ODBC数据源管理器；13、#接口常量.电源选项属性；14、#接口常量.区域和语言选项；15、#接口常量.互联网属性；16、#接口常量.用户帐号；17、#接口常量.系统信息对话框。"),0 , 0, SDT_INT, NULL,NULL},
	{ _WT("属性页序号"), _WT("有多个属性页时，表示要打开属性页的序号（从0开始）。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnOpenSysWindow(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT Index = 0, Type = 0;
	if (pArgInf[0].m_int > 0 && pArgInf[0].m_int <= 17)
	{
		Type = pArgInf[0].m_int;
	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int > 0)
	{
		Index = pArgInf[1].m_int;
	}
	OpenSysWindow(Type, Index);
}
/**************************打开指定网址*******************************/

static ARG_INFO OpenURLArg[] =
{
	{ _WT("网址url或文件路径"), _WT(""),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnOpenURL(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	OpenURL(pArgInf->m_pText);
}
/**************************隐藏显示桌面图标*******************************/
inline void Desktop_ShowHide(bool IsHide)
{
	HWND hWnd = FindWindowW(L"Progman", L"Program Manager");
	if (hWnd)
	{
		ShowWindow(hWnd, IsHide ? SW_HIDE : SW_SHOW);
		UpdateWindow(hWnd);
	}
}

EXTERN_C void eapi_fnHideDesktopIcon(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	Desktop_ShowHide(true);
}
EXTERN_C void eapi_fnShowDesktopIcon(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	Desktop_ShowHide(false);
}

/**************************是否登入网络*******************************/

EXTERN_C void eapi_fnIsLoginNet(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = (GetSystemMetrics(SM_NETWORK) & 1) == 1;
}
/**************************隐藏任务栏*******************************/
inline void  TaskBar_Show_Hide(bool IsHide)
{
	HWND hWnd = FindWindowW(L"Shell_TrayWnd", 0);
	if (hWnd)
	{
		ShowWindow(hWnd, IsHide ? SW_HIDE : SW_SHOW);
		UpdateWindow(hWnd);
	}
}

EXTERN_C void eapi_fnHideTaskBar(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	TaskBar_Show_Hide(true);
}
EXTERN_C void eapi_fnShowTaskBar(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	TaskBar_Show_Hide(false);
}
/**************************隐藏系统时钟*******************************/
inline void Clock_Show_Hide(bool IsHide)
{
	HWND hTray = FindWindowW(L"Shell_TrayWnd", 0);
	HWND hTimeDlg = GetDlgItem(hTray, 303);
	HWND hWnd = GetDlgItem(hTimeDlg, 303);
	if (hWnd)
	{
		ShowWindow(hWnd, IsHide ? SW_HIDE : SW_SHOW);
		UpdateWindow(hWnd);
	}
}
EXTERN_C void eapi_fnHideClock(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	Clock_Show_Hide(true);
}
EXTERN_C void eapi_fnShowClock(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	Clock_Show_Hide(false);
}
/**************************隐藏开始按钮*******************************/
inline void StartButton(bool  IsHide)
{
	HWND  hTray = FindWindowW(L"Shell_TrayWnd", 0);
	HWND hTimeDlg = GetDlgItem(hTray, 304);

	if (hTimeDlg)
	{
		ShowWindow(hTimeDlg, IsHide ? SW_HIDE : SW_SHOW);
		UpdateWindow(hTimeDlg);
	}
}

EXTERN_C void eapi_fnHideStartButton(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	StartButton(true);
}
EXTERN_C void eapi_fnShowStartButton(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	StartButton(false);
}

/**************************设置桌面墙纸*******************************/
static ARG_INFO SetDeskWallPaperArg[] =
{
	{ _WT("文件名"), _WT("墙纸文件名（bmp格式）。将文件名置为空可以取消墙纸。"),0 , 0, SDT_TEXT, NULL,NULL},
	{ _WT("样式"), _WT("墙纸样式，可以为以下常量值之一：0、#接口常量.居中；1、#接口常量.平铺；2、#接口常量.拉伸。。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnSetDeskWallPaper(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string Filename; int type = 0;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText && strlen(pArgInf[0].m_pText) > 0)
	{
		Filename = pArgInf[0].m_pText;
	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int > 0 && pArgInf[1].m_int <= 2)
	{
		type = pArgInf[1].m_int;
	}
	pRetData->m_bool = SetDeskWallPaper(Filename, type);
}
/**************************设置窗口透明度*******************************/
static ARG_INFO SetDiaphaneityArg[] =
{
	{ _WT("窗口句柄"), _WT("要设置透明度的窗口句柄。"),0 , 0, SDT_INT, NULL,NULL},
	{ _WT("透明度"), _WT("墙纸样式，可以为以下常量值之一：0、#接口常量.居中；1、#接口常量.平铺；2、#接口常量.拉伸。。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("透明色"), _WT("(#颜色)指定某颜色为完全透明(完全透明处不属于该窗口) 可空为不指定."),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("鼠标穿透"), _WT("设置鼠标穿透，默认为假"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY},

};
EXTERN_C void eapi_fnSetDiaphaneity(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int type = 0;
	if (!pArgInf[0].m_int)
	{
		pRetData->m_bool = 0;
		return;
	}
	HWND hWnd = (HWND)pArgInf[0].m_int;
	INT alpha = 255, key = 0, through = 0;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int >= 0 && pArgInf[1].m_int <= 255)
	{
		alpha = pArgInf[1].m_int;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_int)
	{
		key = pArgInf[2].m_int;
	}
	if (pArgInf[3].m_dtDataType && pArgInf[3].m_bool)
	{
		through = pArgInf[3].m_bool;
	}
	pRetData->m_bool = SetDiaphaneity(hWnd, alpha, key, through);
}

/**************************取显示模式列表*******************************/
EXTERN_C void eapi_fnGetVideoList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<VIDEOMODE> data = GetVideoList();
	if (data.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}
	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(PVIDEOMODE) * data.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = data.size();
	PVIDEOMODE* dretarry = (PVIDEOMODE*)(retarry + sizeof(INT) * 2);
	for (auto temp = data.begin(); temp != data.end(); temp++)
	{
		VIDEOMODE copy = *temp;
		PVIDEOMODE tempproc = (PVIDEOMODE)eapi_MMalloc(sizeof(PVIDEOMODE));;
		memcpy(tempproc, &copy, sizeof(VIDEOMODE));
		*dretarry = tempproc;
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}


/**************************取当前显示模式*******************************/
EXTERN_C void eapi_fnGetCurVideo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	VIDEOMODE data = GetCurVideo();
	pRetData->m_pCompoundData = eapi_MMalloc(sizeof(VIDEOMODE));
	memcpy(pRetData->m_pCompoundData, &data, sizeof(VIDEOMODE));
}


/*************************设置屏幕分辨率*******************************/

static ARG_INFO SetResolveRatioArg[] =
{
	{ _WT("宽度"), _WT("屏幕显示区域的宽度，单位为像素点。"),0 , 0, SDT_INT, NULL,NULL},
	{ _WT("高度"), _WT("屏幕显示区域的高度，单位为像素点。"),0 , 0, SDT_INT, NULL,NULL},
{ _WT("位数"), _WT("每像素的位数。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("刷新频率"), _WT("屏幕的刷新频率。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},

};
EXTERN_C void eapi_fnSetResolveRatio(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int bit = 25, fre = 75;
	if (pArgInf[2].m_dtDataType)
	{
		bit = pArgInf[2].m_int;
	}
	if (pArgInf[3].m_dtDataType)
	{
		fre = pArgInf[3].m_int;
	}

	pRetData->m_bool = SetResolveRatio(pArgInf[0].m_int, pArgInf[1].m_int, bit, fre);
}

/*************************屏幕单位转换*****************************/

static ARG_INFO ChangeUnitArg[] =
{
	{ _WT("源单位值"), _WT("屏幕显示区域的宽度，单位为像素点。"),0 , 0, SDT_DOUBLE, NULL,NULL},
	{ _WT("源单位"), _WT("单位类型，为以下常量值之一：0、#接口常量.像素；1、#接口常量.英寸；2、#接口常量.毫米；3、#接口常量.厘米。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("目的单位"), _WT("单位类型，为以下常量值之一：0、#接口常量.像素；1、#接口常量.英寸；2、#接口常量.毫米；3、#接口常量.厘米。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnChangeUnit(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int lp = 0, wp = 2;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_dtDataType >= 0 && pArgInf[1].m_dtDataType <= 3)
	{
		lp = pArgInf[1].m_int;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_dtDataType >= 0 && pArgInf[2].m_dtDataType <= 3)
	{
		wp = pArgInf[2].m_int;
	}

	pRetData->m_bool = ChangeUnit(pArgInf[0].m_int, lp, wp);
}

/*************************取当前鼠标处颜色值*****************************/

static ARG_INFO GetPointRGBArg[] =
{
	{ _WT("R"), _WT("要取得的R值"),0 , 0, SDT_INT, NULL,AS_RECEIVE_VAR},
	{ _WT("G"), _WT("要取得的G值"),0 , 0, SDT_INT, NULL,AS_RECEIVE_VAR},
	{ _WT("B"), _WT("要取得的B值"),0 , 0, SDT_INT, NULL,AS_RECEIVE_VAR},
};
EXTERN_C void eapi_fnGetPointRGB(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	BYTE r, g, b;
	bool ret = GetPointRGB(&r, &g, &b);
	if (pArgInf[0].m_dtDataType == SDT_INT)
	{
		PMDATA_INF pInf = pArgInf;
		*pInf->m_pInt = r;
	}
	if (pArgInf[1].m_dtDataType == SDT_INT)
	{
		PMDATA_INF pInf = pArgInf + 1;
		*pInf->m_pInt = g;
	}
	if (pArgInf[2].m_dtDataType == SDT_INT)
	{
		PMDATA_INF pInf = pArgInf + 2;
		*pInf->m_pInt = b;
	}

	pRetData->m_bool = ret;
}

/*************************捕获鼠标*****************************/
static ARG_INFO SetCaptureArg[] =
{

	{ _WT("窗口句柄"), _WT("要接收所有鼠标输入的窗口的句柄。"),0 , 0, SDT_INT, NULL,NULL},
};
EXTERN_C void eapi_fnSetCapture(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_int = (INT)SetCapture((HWND)pArgInf->m_pInt);;
}
/*************************释放鼠标*****************************/
EXTERN_C void eapi_fnReleaseCapture(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_bool = ReleaseCapture();
}

/*************************截取屏幕区域*****************************/
static ARG_INFO GetScreenBitmapArg[] =
{
{ _WT("屏幕区域"), _WT("要截取的屏幕区域，为空则截取整个屏幕。"),0 , 0,  DTP_RECT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("截取到"), _WT("要截取屏幕区域到何处，可以为以下常量值之一：0、#接口常量.到文件； 1、#接口常量.到剪贴板； 2、#接口常量.到字节集。"),0 , 0,  SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
{ _WT("屏幕区域"), _WT(""),0 , 0,  SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnGetScreenBitmap(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	RECT DATA;
	HWND Desk;
	INT Type = 0;
	HBITMAP hBMP;
	if (pArgInf->m_dtDataType)
	{
		DATA = *(RECT*)*pArgInf->m_ppCompoundData;
	}
	else
	{
		Desk = GetDesktopWindow();
		GetWindowRect(Desk, &DATA);
	}
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int > 0 && pArgInf[1].m_int <= 2)
	{
		Type = pArgInf[1].m_int;
	}
	if (Type == 0)
	{
		pRetData->m_dtDataType = SDT_BOOL;
		pRetData->m_bool = CopyScreenToBitmap(&DATA, 0, pArgInf[2].m_pText);
		return;
	}
	else if (Type == 1)
	{
		pRetData->m_dtDataType = SDT_BOOL;
		pRetData->m_bool = CopyScreenToBitmap(&DATA, 1, pArgInf[2].m_pText);
		return;
	}
	else if (Type != 2)
	{
		return;
	}
	hBMP = CopyScreenToBitmap(&DATA);
	pRetData->m_dtDataType = SDT_BIN;
	if (hBMP)
	{
		HGLOBAL hMem = (void*)eapi_NotifySys(2034, (DWORD)hBMP, 0);
		if (hMem)
		{
			void* pMem = GlobalLock(hMem);
			size_t size = GlobalSize(hMem);
			pRetData->m_pBin = eapi_CloneBinData((LPBYTE)pMem, size);
			GlobalUnlock(hMem);
			GlobalFree(hMem);
			DeleteObject(hBMP);
			return;
		}
		DeleteObject(hBMP);
	}
	pRetData->m_pBin = 0;
}

/*************************取所有窗口列表****************************/

EXTERN_C void eapi_fnGetAllWindowsList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	vector<HWND> list = GetAllWindowsList();
	if (list.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}
	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(int) * list.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = list.size();
	INT* dretarry = (INT*)(retarry + sizeof(INT) * 2);
	for (auto temp = list.begin(); temp != list.end(); temp++)
	{
		*dretarry = (INT)*temp;
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*************************取窗口标题*****************************/

EXTERN_C void eapi_fnGetWindowText(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	char* title = NULL; HWND hWnd = (HWND)pArgInf->m_pInt;
	if (IsWindow(hWnd))
	{
		LRESULT size = SendMessageA(hWnd, 0xEu, 0, 0);
		if (size > 0)
		{
			title = new char[size + 1];
			if (title)
			{
				SendMessageA(hWnd, 0xDu, size + 1, (LPARAM)title);
				pRetData->m_pText = eapi_CloneTextData(title);
				delete[]title;
			}

		}
	}
	return;
}
/*************************取窗口类名*****************************/

EXTERN_C void eapi_fnGetClassName(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	char classname[MAX_PATH + 1] = { 0 }; HWND hWnd = (HWND)pArgInf->m_pInt;
	if (IsWindow(hWnd))
	{

		GetClassNameA(hWnd, classname, MAX_PATH);
	}
	pRetData->m_pText = eapi_CloneTextData(classname);
}
/*************************取鼠标所在窗口句柄*****************************/

EXTERN_C void eapi_fnGetHwndFromPoint(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	tagPOINT Point;
	GetCursorPos(&Point);
	pRetData->m_int = (int)GetSmallestWindowFromPoint(Point);
}


/*************************映射网络驱动器*****************************/
static ARG_INFO NetAddConnectionArg[] =
{

	{ _WT("网络资源路径"), _WT("要映射到本地的网络资源路径。"),0 , 0, SDT_TEXT, NULL,NULL},
	{ _WT("驱动器"), _WT("映射到本地的驱动器名。"),0 , 0, SDT_TEXT, NULL,NULL},
};
EXTERN_C void eapi_fnNetAddConnection(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_pText && pArgInf[1].m_pText)
	{
		pRetData->m_bool = NetAddConnection(pArgInf->m_pText, pArgInf[1].m_pText);;
	}
	else
	{
		pRetData->m_bool = FALSE;
	}

}
/*************************发送局域网消息*****************************/
static ARG_INFO NetSendMessageArg[] =
{

	{ _WT("发送目标"), _WT("将要接收消息的目标机器，可以为机器名、IP地址、工作组名（具体由目标类型决定）"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
	{ _WT("消息"), _WT("将要发送的消息文本"),0 , 0, SDT_TEXT, NULL,NULL},
	{ _WT("保留参数"), _WT(""),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnNetSendMessage(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	string tagat, msg;
	if (pArgInf->m_dtDataType && pArgInf->m_pText && strlen(pArgInf->m_pText))
	{
		tagat = pArgInf->m_pText;
	}
	if (pArgInf[1].m_pText && strlen(pArgInf[1].m_pText))
	{
		msg = pArgInf[1].m_pText;
	}

	pRetData->m_bool = NetSendMessage(tagat, msg);

}
/*************************取网络共享资源列表*****************************/
static ARG_INFO GetShareResourceListArg[] =
{

	{ _WT("计算机"), _WT("计算机名称，为空则取所有计算机的共享资源。"),0 , 0, SDT_TEXT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
	{ _WT("共享资源类型"), _WT("共享资源类型，可以为以下常量值之一：0、#接口常量.所有共享资源；1、#接口常量.共享目录或文件；2、#接口常量.共享打印机。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnGetShareResourceList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	INT type = 0; string computer;
	if (pArgInf->m_dtDataType && pArgInf->m_pText && strlen(pArgInf->m_pText))
	{
		computer = pArgInf->m_pText;
	}
	if (pArgInf[1].m_dtDataType == SDT_INT && pArgInf[1].m_int > 0 && pArgInf[1].m_int <= 2)
	{
		type = pArgInf[1].m_int;

	}
	vector<string> List = GetShareResourceList(computer, type);
	if (List.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * List.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = List.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = List.begin(); temp != List.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}
/*************************取消网络驱动器映射*****************************/
static ARG_INFO CancelNetConnectionArg[] =
{

	{ _WT("驱动器"), _WT("映射到本地的驱动器名。"),0 , 0, SDT_TEXT, NULL,NULL},
};
EXTERN_C void eapi_fnCancelNetConnection(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_pText)
	{
		pRetData->m_bool = CancelNetConnection(pArgInf->m_pText);;
	}

}
/*************************取打印机列表*****************************/
EXTERN_C void eapi_fnGetPrinterList(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	vector<string> List = GetPrinterList();
	if (List.size() < 1)
	{
		pRetData->m_pAryData = E_NULLARRAY();
		return;
	}

	LPBYTE retarry = (LPBYTE)eapi_MMalloc(sizeof(INT) * 2 + sizeof(char*) * List.size());
	*(LPINT)retarry = 1;
	*(LPINT)(retarry + sizeof(INT)) = List.size();
	LPSTR* dretarry = (LPSTR*)(retarry + sizeof(INT) * 2);

	for (auto temp = List.begin(); temp != List.end(); temp++)
	{
		*dretarry = eapi_CloneTextData(const_cast<char*>((*temp).c_str()));
		dretarry++;
	}
	pRetData->m_pAryData = retarry;
}


/*************************取默认打印机*****************************/

EXTERN_C void eapi_fnGetDefaultPrinter(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = A2Estr(MyGetDefaultPrinter());;
}
/*************************置默认打印机*****************************/
static ARG_INFO SetDefaultPrinterArg[] =
{

	{ _WT("打印机名称"), _WT("要设置为默认打印机的名称。"),0 , 0, SDT_TEXT, NULL,NULL},
};

/*************************打开打印机对话框*****************************/
static ARG_INFO OpenPrintSetDlgArg[] =
{
	  { _WT("对话框类型"), _WT("要打开的对话框类型。可以为以下两个常量值之一：0、#接口常量.标准打印设置对话框；1.打印机MFC对话框，废弃，对于MFC静态编译会出现问题 2、#接口常量.打印属性对话框。默认值为0"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
	  { _WT("打印信息"), _WT("待取得的硬盘信息"),0 , 0, DTP_PRINT, NULL, AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnSetDefaultPrinter(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_pText)
	{
		pRetData->m_bool = MySetDefaultPrinter(pArgInf->m_pText);;
		return;
	}
	pRetData->m_bool = 0;
}
EXTERN_C void eapi_fnOpenPrintSetDlg(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	PMYPRINTINFO pPrintInfo = NULL;
	INT type = 0;
	if (pArgInf[0].m_dtDataType)
	{
		type = pArgInf[0].m_int;
	}
	if (pArgInf[1].m_dtDataType)
	{

		pPrintInfo = *(PMYPRINTINFO*)pArgInf[1].m_pCompoundData;

	}

	pRetData->m_int = OpenPrintSetDlg(type, pPrintInfo);
}
/*************************创建快捷方式**废弃*****************************/
//static ARG_INFO CreateLinkArg[] =
//{
//	{ _WT("快捷方式文件名"), _WT("如果文件名不包含后缀,将自动加上\".lnk\"后缀名."),0 , 0,  SDT_TEXT, NULL, NULL },
//	{ _WT("指向文件路径"), _WT("提供快捷方式所指向文件的全路径名"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
//		{ _WT("备注信息"), _WT("提供对应此快捷方式的描述文本信息"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
//	{ _WT("命令行文本"), _WT("提供启动快捷方式指向文件时附加的命令行文本"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
//		{ _WT("工作目录"), _WT("提供启动快捷方式指向文件时所需预置的工作目录"),0 , 0,  SDT_TEXT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
//		{ _WT("热键"), _WT("热键键值，具体参照微软接口"),0 , 0,  SDT_INT, NULL, AS_DEFAULT_VALUE_IS_EMPTY },
//	  };
//EXTERN_C void eapi_fnCreateLink(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
//{
//
//	string Name, path, remark, commline, dir;
//	DWORD hotKey=0;
//	if (pArgInf[0].m_dtDataType && pArgInf[0].m_pText)
//	{
//		Name = pArgInf[0].m_pText;
//	}
//	if (pArgInf[1].m_dtDataType && pArgInf[1].m_pText)
//	{
//		path = pArgInf[1].m_pText;
//	}
//	if (pArgInf[2].m_dtDataType && pArgInf[2].m_pText)
//	{
//		remark = pArgInf[2].m_pText;
//	}
//	if (pArgInf[3].m_dtDataType && pArgInf[3].m_pText)
//	{
//		commline = pArgInf[3].m_pText;
//	}
//	if (pArgInf[4].m_dtDataType && pArgInf[4].m_pText)
//	{
//		dir = pArgInf[4].m_pText;
//	}
//	if (pArgInf[5].m_dtDataType)
//	{
//		hotKey = pArgInf[5].m_int;
//	}
//	pRetData->m_bool = CreateLink(Name, path, remark, hotKey,commline, dir);
//}

/*************************取屏幕DPI*****************************/
static ARG_INFO GetMoniterDPIArg[] =
{

	{ _WT("窗口句柄"), _WT("欲取所在窗口的软件窗口句柄，为空则取主屏幕。"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnGetMoniterDPI(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = 0;
	if (pArgInf[0].m_dtDataType)
	{
		hWnd = (HWND)pArgInf[0].m_int;
	}
	pRetData->m_double = GetMoniterDPI(hWnd);
}

/*************************隐藏显示鼠标*****************************/

inline void HideCursor(bool isHide) {
	ShowCursor(isHide == 0);
}

EXTERN_C void eapi_fnHideCursor(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	HideCursor(1);
}
EXTERN_C void eapi_fnShowCursor(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	HideCursor(0);
}
/*************************取图片格式*****************************/
static ARG_INFO GetPictureFormatArg[] =
{
	{ _WT("图片路径或数据"), _WT("可以选择图片路径，或者内存图片字节集。"),0 , 0, _SDT_ALL, NULL,NULL},
};
EXTERN_C void eapi_fnGetPictureFormat(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = 0;
	if (pArgInf[0].m_dtDataType == SDT_TEXT && pArgInf->m_pText)
	{

		pRetData->m_pText = A2Estr(GetPictureFormat(pArgInf[0].m_pText));
		return;
	}
	if (pArgInf[0].m_dtDataType == SDT_BIN)
	{
		VECTORBYTE data = GetEbin(pArgInf->m_pBin);
		pRetData->m_pText = A2Estr(GetPictureFormat(vector<BYTE>(data.data, data.data + data.size)));
		return;
	}

}
/*************************取硬盘编号*****************************/
EXTERN_C void eapi_fnGetDiskNumber(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = A2Estr(GetDiskNumber());
}
/*************************蜂鸣*****************************/
static ARG_INFO MessageBeepArg[] =
{
	{ _WT(" 默认类型"), _WT(" 默认: 0,标准: 1,拒绝 :2,询问 3,感叹 48,特别 64"),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnMessageBeep(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	UINT type = 0;
	if (pArgInf[0].m_dtDataType && pArgInf[0].m_int >= -1 && pArgInf[0].m_int <= 64)
	{
		switch (pArgInf[0].m_int)
		{
		case 1: type = -1; break;
		case 2: type = 16; break;
		case 3: type = 32; break;
		case 4: type = 48; break;
		case 5: type = 64; break;
		default:
			break;
		}
	}
	MessageBeep(type);
}
/*************************窗口圆角化*****************************/
static ARG_INFO RoundedWindowArg[] =
{
	{ _WT("窗口句柄"), _WT("欲修改的窗口句柄"),0 , 0, SDT_INT, NULL,NULL},
		{ _WT("圆角宽度"), _WT(""),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
			{ _WT("圆角高度"), _WT(""),0 , 0, SDT_INT, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnRoundedWindow(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	DWORD H = 5, W = 5;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_int > 0)
	{
		H = pArgInf[1].m_int;
	}
	if (pArgInf[2].m_dtDataType && pArgInf[2].m_int > 0)
	{
		W = pArgInf[2].m_int;
	}
	HWND hWnd = (HWND)pArgInf[0].m_int;;
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	HRGN hRgn = CreateRoundRectRgn(0, 0, rc.right - rc.left + 1, rc.bottom - rc.top + 1, W, H);
	SetWindowRgn(hWnd, hRgn, true);
	DeleteObject(hRgn);
}
/*************************窗口置顶*****************************/
static ARG_INFO SetForegroundWindowArg[] =
{
	{ _WT("窗口句柄"), _WT("欲修改的窗口句柄"),0 , 0, SDT_INT, NULL,NULL},
		{ _WT("是否总在最前"), _WT("默认为假"),0 , 0, SDT_BOOL, NULL,AS_DEFAULT_VALUE_IS_EMPTY},
};
EXTERN_C void eapi_fnSetForegroundWindow(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	bool top = 0;;
	if (pArgInf[1].m_dtDataType && pArgInf[1].m_bool == 1)
	{
		top = 1;
	}

	HWND hWnd = (HWND)pArgInf[0].m_int, hWndInsertAfter = HWND_NOTOPMOST;
	if (top) {
		SetForegroundWindow(hWnd);
		hWndInsertAfter = HWND_TOPMOST;
	}
	pRetData->m_bool = SetWindowPos(hWnd, hWndInsertAfter, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);


}
EXTERN_C void eapi_fnUpPrivilegeValue(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_bool = UpPrivilegeValue();


}
#if (_MSC_VER > 1600)
#pragma endregion
#endif





//以下为库定义，无需特别关注
#ifndef __E_STATIC_LIB

//静态库需要
static const char* const CommandNames[] =
{ "eapi_fnGetKeyboardLockState",
	"eapi_fnSimulateKey",
	"eapi_fnSimulateMouse",
	"eapi_fnGetHDInfo",
	"eapi_fnGetDrivesNum",
	"eapi_fnGetDrivesList",
	"eapi_fnPopupCdrom",
	"eapi_fnCloseCdrom",
	"eapi_fnGetCdrom",
	"eapi_fnIsDiskInside",
	"eapi_fnGetProcessList",
	"eapi_fnKillProcess",
	"eapi_fnGetDllList",
	"eapi_fnGetHungProgramList",
	"eapi_fnGetSystemInfo",
	"eapi_fnGetBiosInfo",
	"eapi_fnGetFileVersionInfo",
	"eapi_fnGetCpuInfo",
	"eapi_fnGetCpuUsges",
	"eapi_fnGetMemoryInfo",
	"eapi_fnGetAudioCard",
	"eapi_fnOpenMonitor",
	"eapi_fnCloseMonitor",
	"eapi_fnAddRightMenu",
	"eapi_fnDeleteRightMenu",
	"eapi_fnSetAutoRun",
	"eapi_fnDeleteTempFile",
	"eapi_fnClearHistory",
	"eapi_fnGetFontList",
	"eapi_fnAddFont",
	"eapi_fnRemoveFont",
	"eapi_fnGetImageWidth",
	"eapi_fnGetImageHeight",
	"eapi_fnGetIconFromResource",
	"eapi_fnGetIEVersion",
	"eapi_fnAddButtonToIE",
	"eapi_fnDeleteButtonFromIE",
	"eapi_fnCreateProgramGroup",
	"eapi_fnDeleteProgramGroup",
	"eapi_fnCreateProgramItem",
	"eapi_fnDeleteProgramItem",
	"eapi_fnGetShortCutTarget",
	"eapi_fnGetApapterList",
	"eapi_fnGetLocalAdapterName",
	"eapi_fnGetLocalMac"
	,"eapi_fnGetRemoteMac",
	"eapi_fnGetRemoteName",
	"eapi_fnGetIpFromHostName",
	"eapi_fnRunEmailAddr",
	"eapi_fnGetNetList"
	,"eapi_fnGetGroupList",
	"eapi_fnGetComputerList",
	"eapi_fnIsConnectToInternet",
	"eapi_fnIsLoginNet",
	"eapi_fnCheckPort"
	,"eapi_fnOpenSysWindow",
	"eapi_fnOpenURL",
	"eapi_fnHideDesktopIcon",
	"eapi_fnShowDesktopIcon",
	"eapi_fnHideTaskBar",
	"eapi_fnShowTaskBar"
	,"eapi_fnHideClock",
	"eapi_fnShowClock",
	"eapi_fnHideStartButton",
	"eapi_fnShowStartButton",
	"eapi_fnSetDeskWallPaper",
	"eapi_fnSetDiaphaneity",
	"eapi_fnGetVideoList",
	"eapi_fnGetCurVideo",
	"eapi_fnSetResolveRatio",
	"eapi_fnChangeUnit",
	"eapi_fnGetPointRGB",
	"eapi_fnSetCapture",
	"eapi_fnReleaseCapture",
	"eapi_fnGetScreenBitmap",
	"eapi_fnGetAllWindowsList",
	"eapi_fnGetWindowText",
	"eapi_fnGetClassName",
	"eapi_fnGetHwndFromPoint",
	"eapi_fnNetAddConnection",
	"eapi_fnNetSendMessage",
	"eapi_fnGetShareResourceList"
	,"eapi_fnCancelNetConnection"
	,"eapi_fnCancelAutoRun",
	"eapi_fnsprintf",
	"eapi_fnGetPrinterList",
	"eapi_fnGetDefaultPrinter",
	"eapi_fnSetDefaultPrinter"
	,"eapi_fnOpenPrintSetDlg",
	"eapi_fnCreateLink",
	"eapi_fnGetMoniterDPI",
	"eapi_fnHideCursor",
	"eapi_fnShowCursor",
	"eapi_fnGetPictureFormat",
	"eapi_fnGetDiskNumber"
	,"eapi_fnMessageBeep",
	"eapi_fnRoundedWindow",
	"eapi_fnSetForegroundWindow",
	"eapi_fnSetForegroundWindow",
};

static CMD_INFO Commands[] = {
	{
		/*ccname*/	_WT("取键盘指示灯状态"),
		/*egname*/	_WT("GetKeyboardLockState"),
		/*explain*/	_WT("取得三个键盘提示灯当前状态。开返回真；关返回假。本命令为初级命令。"),
		/*category*/1,
		/*state*/	NULL,
		/*ret*/		SDT_BOOL,
		/*syscmd*/	NULL,
		/*level*/	LVL_SIMPLE,
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*ArgCount*/1,
		/*arg lp*/	GetKeyboardLockStateArg,
			},

		{ _WT("模拟按键"), _WT("SimulateKey"), _WT("模拟键盘的输入。"),1 , NULL, NULL , 0, LVL_SIMPLE,0 ,0 , 3, SimulateKeyArg },
		{ _WT("模拟鼠标点击"), _WT("SimulateMouse"), _WT("模拟鼠标点击。"),1 , NULL, NULL , 0, LVL_SIMPLE,0 ,0 , 3, SimulateMouseArg },
		{ _WT("取硬盘信息"), _WT("GetHDInfo"), _WT("取硬件出厂信息。Win95/98/Me中可能无效。特殊情况下也许只能获取部分硬盘信息，其它未被成功获取的部分，将被设置为空文本或0。本命令为初级命令。"),1 , NULL,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 2, GetHDInfoArg },
		{ _WT("取驱动器数量"), _WT("GetDrivesNum"), _WT("取当前指定类型的驱动器数量"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 , 1,GetDrivesNumArg },
		{ _WT("取驱动器列表"), _WT("GetDrivesList"), _WT("取当前指定类型的驱动器列表。成功返回驱动器列表数组；失败返回空。本命令为初级命令。"),1 , CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 1,GetDrivesNumArg },
		{ _WT("弹出光驱"), _WT("PopupCdrom"), _WT("弹出光驱门,成功仅代表命令执行成功。"),1 ,  NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("关闭光驱"), _WT("CloseCdrom"), _WT("关闭光驱门，成功仅代表命令执行成功。"),1 ,  NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("取光驱盘符"), _WT("GetCdrom"), _WT("取光驱盘符。失败返回空。"),1 ,  NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("光驱中是否有盘"), _WT("IsDiskInside"), _WT("光驱中是否有盘。有盘返回真；否则返回假。"),1 ,  NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("取系统进程列表"), _WT("IsDiskInside"), _WT("取所有正在运行的程序列表。成功返回程序列表数组；失败返回空。本命令为初级命令。"),1 , CT_RETRUN_ARY_TYPE_DATA, DTP_PROC , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("终止进程"), _WT("SimulateKey"), _WT("模拟键盘的输入。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 1,KillProcessArg },
		{ _WT("取正在使用DLL列表"), _WT("GetDllList"), _WT("取所有正在使用的DLL列表。成功返回DLL列表数组；失败返回空。"),1 ,CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 1,GetDllListArg },
		{ _WT("取没有响应程序列表"), _WT("GetHungProgramList"), _WT("取没有响应程序列表。成功返回程序标题数组，失败返回空。本命令为初级命令。"),1 ,CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("取系统信息"), _WT("GetSystemInfo"), _WT("取系统信息。"),1 ,NULL, NULL , 0, LVL_SIMPLE,0 ,0 , 1,GetSystemInfoArg },
		{ _WT("取BIOS信息"), _WT("GetBiosInfo"), _WT("取BIOS信息。"),1 ,NULL, NULL , 0, LVL_SIMPLE,0 ,0 , 1,GetBiosInfoArg },
		{ _WT("取文件版本信息"), _WT("GetFileVersionInfo"), _WT("取文件信息版本。"),1 ,NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 2,GetFileVersionInfoArg },
		{ _WT("取CPU信息"), _WT("GetCpuInfo"), _WT("取CPU信息。"),1 ,NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 1,GetCpuInfoArg },
		{ _WT("取CPU占用率"), _WT("GetCpuUsges"), _WT("取当前CPU占用率。成功返回CPU占用率；失败返回-1。Win98系统下使用本方法取得的数值可能会有误。本命令为初级命令。"),1 , NULL, SDT_DOUBLE , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("取内存容量信息"), _WT("GetMemoryInfo"), _WT("取内存容量信息，单位为M（兆）。"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 , 1,GetMemoryInfoArg },
		{ _WT("取声卡名称"), _WT("GetAudioCard"), _WT("取系统声卡名称，失败返回空"),1 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0 ,0 },
		{ _WT("打开屏幕"), _WT("OpenMonitor"), _WT("打开屏幕"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,0 ,0 },
		{ _WT("关闭屏幕"), _WT("CloseMonitor"), _WT("关闭屏幕"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,0 ,0 },
		{ _WT("添加右键菜单"), _WT("AddRightMenu"), _WT("向指定作用区域文件右键后的菜单内添加选项"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(AddRightMenuArg) / sizeof(AddRightMenuArg[0]) ,AddRightMenuArg },
		{ _WT("删除右键菜单"), _WT("DeleteRightMenu"), _WT("删除指定标题或作用区域右键菜单"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(DeleteRightMenuArg) / sizeof(DeleteRightMenuArg[0]) ,DeleteRightMenuArg },
		{ _WT("设置自动运行"), _WT("SetAutoRun"), _WT("设置程序在开机时自动运行。本命令为初级命令"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(SetAutoRunArg) / sizeof(SetAutoRunArg[0]) ,SetAutoRunArg },
		{ _WT("删除临时文件"), _WT("DeleteTempFile"), _WT("删除指定位置的临时文件。成功返回真；失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1 ,DeleteTempFileArg },
		{ _WT("清除历史记录"), _WT("ClearHistory"), _WT("清除指定类型的历史记录。成功返回真；失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1 ,ClearHistoryArg },
		{ _WT("取系统字体列表"), _WT("GetFontList"), _WT("取系统所有字体的列表。成功返回字体数组；失败返回空。"),1 , CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0,0 },
		{ _WT("安装字体"), _WT("AddFont"), _WT("在Windows系统中添加一种字体资源。添加完毕后，该字体即可由任何Windows应用程序调用。成功返回1,失败返回0，如加载内存资源则返回安装临时字体的句柄，字体资源进程之间不可共享，可通过删除字体提前删除资源；"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 ,1 ,AddFontArg },
		{ _WT("删除字体"), _WT("RemoveFont"), _WT("在从Windows系统中删除一种字体资源。提供临时字体的句柄，则会立即卸载临时字体，如删除系统的字体目前正由其他应用程序使用，则并不将其立即删除。成功返回真；失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1 ,RemoveFontArg },
		{ _WT("取图片宽度"), _WT("GetImageWidth"), _WT("取得指定图片的宽度。成功返回图片宽度；失败返回0。本命令为初级命令。"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 ,1 ,GetImageWidthArg },
		{ _WT("取图片高度"), _WT("GetImageHeight"), _WT("取得指定图片的宽度。成功返回图片宽度；失败返回0。本命令为初级命令。"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 ,1 ,GetImageWidthArg },
		{ _WT("提取资源文件图标"), _WT("GetIconFromResource"), _WT("从指定的资源文件中提取图标，并保存为ICO、BMP文件或复制到剪贴板。成功返回图标数量；失败返回0。"),1 , NULL, SDT_INT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetIconFromResourceArg) / sizeof(GetIconFromResourceArg[0]) ,GetIconFromResourceArg },
		{ _WT("取IE版本号"), _WT("GetIEVersion"), _WT("取得IE的版本号。成功返回版本号；"),1 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0 ,0 },
		{ _WT("添加IE工具条按钮"), _WT("AddButtonToIE"), _WT("向IE工具栏添加自己的按钮。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,sizeof(AddButtonToIEArg) / sizeof(AddButtonToIEArg[0]) ,AddButtonToIEArg},
		{ _WT("删除IE工具条按钮"), _WT("DeleteButtonFromIE"), _WT("向IE工具栏添加自己的按钮。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1 ,DeleteButtonFromIEArg},
		{ _WT("创建程序组"), _WT("CreateProgramGroup"), _WT("在指定的位置的特殊位置创建特殊位置文件夹。成功返回真，失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,2 ,CreateProgramGroupArg},
		{ _WT("删除程序组"), _WT("DeleteProgramGroupGroup"), _WT("删除指定的特殊位置建立过的程序组。成功返回真，失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,2, DeleteProgramGroupArg},
		{ _WT("创建程序项"), _WT("CreateProgramItem"), _WT("在指定的特殊位置位置程序组文件夹中创建快捷方式。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,4, CreateProgramItemArg},
		{ _WT("删除程序项"), _WT("DeleteProgramItem"), _WT("删除指定的特殊位置程序组文件夹中的文件夹快捷方式。成功返回真，失败返回假。"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,3, DeleteProgramItemArg},
		{ _WT("取快捷方式目标"), _WT("GetShortCutTarget"), _WT("获取指定快捷方式（.lnk）的目标和参数。成功返回目标，失败返回空。只有第一个参数为输入参数，后面的其它参数均为输出参数（可省略）。"),1 , NULL, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,sizeof(GetShortCutTargetArg) / sizeof(GetShortCutTargetArg[0]), GetShortCutTargetArg},
		{ _WT("取网卡信息列表"), _WT("GetApapterList"), _WT("取得本地计算机的网卡信息列表。失败返回空"),2 , CT_RETRUN_ARY_TYPE_DATA, DTP_NETWORK  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("取本机网卡名"), _WT("GetLocalAdapterName"), _WT("取得本地计算机的网卡信息列表。失败返回空"),2 , NULL, SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,GetLocalAdapterNameArg},
		{ _WT("取本机网卡物理地址"), _WT("GetLocalMac"), _WT("取得本地计算机指定序号的网卡物理地址。失败返回空。"),2 , NULL, SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,GetLocalAdapterNameArg},
		{ _WT("取远程网卡物理地址"), _WT("GetRemoteMac"), _WT("根据指定的IP地址取远程机器网卡的物理地址。。失败返回空。"),2 , NULL, SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,GetRemoteMacArg},
		{ _WT("取远程机器名"), _WT("GetRemoteName"), _WT("根据指定的IP地址取远程机器名称。失败返回空"),2 , NULL, SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,GetRemoteNameArg},
		{ _WT("取IP地址"), _WT("GetRemoteName"), _WT(""),2 , NULL, SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,GetRemoteNameArg},
		{ _WT("撰写邮件"), _WT("RunEmailAddr"), _WT("调用系统默认邮箱工具并置目标邮箱为参数"),2 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,1,RunEmailAddrArg},
		{ _WT("取网络类型列表"), _WT("GetNetList"), _WT("取所有的网络类型。成功返回程序列表数组；失败返回空"),2 ,CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("取网络工作组列表"), _WT("GetGroupList"), _WT("取局域网中指定网络类型的工作组列表。成功返回列表数组；失败返回空。"),2 ,CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 1,GetGroupListArg },
		{ _WT("取网络计算机列表"), _WT("GetComputerList"), _WT("取局域网中指定工作组的计算机列表。成功返回列表数组；失败返回空。"),2 ,CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT , 0, LVL_SIMPLE,0 ,0 , 1,GetComputerListArg },
		{ _WT("是否联网"), _WT("IsConnectToInternet"), _WT("取局域网中指定工作组的计算机列表。成功返回列表数组；失败返回空。"),2 ,CT_RETRUN_ARY_TYPE_DATA, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("是否存在网络"), _WT("IsLoginNet"), _WT("如果取是否联网推荐使用命令\"是否联网()\"检测机器是否存在网络，\"if a network is present\"，参见MSDN中对GetSystemMetrics()参数SM_NETWORK的说明）。"),2 ,CT_RETRUN_ARY_TYPE_DATA, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 , 0,0 },
		{ _WT("端口检测"), _WT("CheckPort"), _WT(""),2 , NULL, SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,2,CheckPortArg},
		{ _WT("打开特殊系统窗口"), _WT("OpenSysWindow"), _WT("打开特殊的系统窗口，如控制面板。"),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,2,OpenSysWindowArg},
		{ _WT("打开指定网址"), _WT("OpenURL"), _WT("用系统默认浏览器打开指定的网址。"),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,1,OpenURLArg},
		{ _WT("隐藏桌面图标"), _WT("HideDesktopIcon"), _WT(""),3, NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("显示桌面图标"), _WT("ShowDesktopIcon"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("隐藏任务栏"), _WT("HideTaskBar"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("显示任务栏"), _WT("ShowTaskBar"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("隐藏系统时钟"), _WT("HideClock"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("显示系统时钟"), _WT("ShowClock"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("隐藏开始按钮"), _WT("HideStartButton"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("显示开始按钮"), _WT("ShowStartButton"), _WT(""),3 , NULL, NULL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("设置桌面墙纸"), _WT("SetDeskWallPaper"), _WT("成功返回真；失败返回假。"),3 , NULL, SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,2,SetDeskWallPaperArg},
		{ _WT("设置窗口透明度"), _WT("SetDiaphaneity"), _WT("成功返回真；失败返回假。"),3 , NULL, SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,4,SetDiaphaneityArg},
		{ _WT("取显示模式列表"), _WT("GetVideoList"), _WT("取系统支持的显示模式列表(Win95/98/Me下无法取得刷新频率)。成功返回显示模式信息数组，失败返回空。"),3 , CT_RETRUN_ARY_TYPE_DATA, DTP_VIDEO  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("取当前显示模式"), _WT("GetCurVideo"), _WT("取系统当前的显示模式(Win95/98/Me下无法取得刷新频率)。"),3 , NULL, DTP_VIDEO  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("设置屏幕分辨率"), _WT("SetResolveRatio"), _WT(""),3 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,4,SetResolveRatioArg},
		{ _WT("屏幕单位转换"), _WT("ChangeUnit"), _WT(""),3 , NULL,SDT_DOUBLE  , 0, LVL_SIMPLE,0 ,0 ,3,ChangeUnitArg},
		{ _WT("取当前鼠标处颜色值"), _WT("GetPointRGB"), _WT("取当前鼠标所在位置的RGB值。"),3 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,3,GetPointRGBArg},
		{ _WT("捕获鼠标"), _WT("SetCapture"), _WT("将鼠标捕获设置到指定的窗口。在鼠标按钮按下的时候，这个窗口会为当前应用程序或整个系统接收所有鼠标输入。返回值为之前拥有鼠标捕获的窗口的句柄，如没有这样的窗口则返回空。"),3 , NULL,SDT_INT  , 0, LVL_SIMPLE,0 ,0 ,1,SetCaptureArg},
		{ _WT("释放鼠标"), _WT("ReleaseCapture"), _WT("为当前的应用程序释放鼠标捕获。成功返回真、失败返回假。"),3 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("截取屏幕区域"), _WT("GetScreenBitma"), _WT("将选定的屏幕区域拷贝到位图文件、剪贴板或字节集中。如拷贝到位图文件或剪贴板，则成功返回真；失败返回假。如拷贝到字节集，则成功返回位图字节集；失败返回空。"),3 , NULL,_SDT_ALL  , 0, LVL_SIMPLE,0 ,0 ,3,GetScreenBitmapArg},
		{ _WT("取所有窗口列表"), _WT("GetAllWindowsList"), _WT("取当前打开的所有窗口列表。成功返回窗口句柄数组，失败返回空。"),3 ,  CT_RETRUN_ARY_TYPE_DATA,SDT_INT  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("取窗口标题"), _WT("GetWindowText"), _WT("取指定窗口的标题。成功返回窗口标题，失败返回空。"),3 , NULL,SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,SetCaptureArg},
		{ _WT("取窗口类名"), _WT("GetClassName"), _WT("取指定窗口的类名。成功返回窗口类名，失败返回空。"),3 , NULL,SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,1,SetCaptureArg},
		{ _WT("取鼠标所在窗口句柄"), _WT("GetHwndFromPoint"), _WT("取鼠标所在窗口句柄。"),3 , NULL,SDT_INT  , 0, LVL_SIMPLE,0 ,0 ,0,0},
		{ _WT("映射网络驱动器"), _WT("NetAddConnection"), _WT("将指定的网络资源映射到本地驱动器。成功返回真；失败返回假。"),2 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,2,NetAddConnectionArg},
		{ _WT("发送局域网消息"), _WT("NetSendMessage"), _WT("发送消息到指定的机器（即Windows信使服务，只有启动了Messenger服务的机器才能收到该命令发送的消息）。成功返回真；失败返回假。"),2 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,3,NetSendMessageArg},
		{ _WT("取网络共享资源列表"), _WT("GetShareResourceList"), _WT("取局域网中指定计算机的共享资源列表。成功返回列表数组；失败返回空。"),2 ,CT_RETRUN_ARY_TYPE_DATA,SDT_TEXT  , 0, LVL_SIMPLE,0 ,0 ,2,GetShareResourceListArg},
		{ _WT("取消网络驱动器映射"), _WT("CancelNetConnection"), _WT("取消指定的网络驱动器映射。成功返回真；"),2 , NULL,SDT_BOOL  , 0, LVL_SIMPLE,0 ,0 ,1,CancelNetConnectionArg},
		{ _WT("取消自动运行"), _WT("CancelAutoRun"), _WT("取消程序的自动运行"),1 , NULL, SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1, CancelAutoRunArg},
		{ _WT("格式化字符串"), _WT("sprintf"), _WT("将一个格式化的字符串输出到一个目的字符串中。给定unicode会返回unicode，此命令与c中sprintf相同，请遵守格式化规则，不把ansi和unicode混用"),1 ,CT_ALLOW_APPEND_NEW_ARG, _SDT_ALL , 0, LVL_SIMPLE,0 ,0 ,2, sprintfArg},
		{ _WT("取打印机列表"), _WT("GetPrinterList"), _WT("枚举系统打印机列表。"),1 ,  CT_RETRUN_ARY_TYPE_DATA,SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0, 0},
		{ _WT("取默认打印机"), _WT("GetDefaultPrinter"), _WT("取系统默认打印机。成功返回默认打印机名称，失败返回空。"),1 , 0,SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0, 0 },
		{ _WT("设置默认打印机"), _WT("SetDefaultPrinter"), _WT("设置系统的默认打印机。"),1 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,1, SetDefaultPrinterArg },
		{ _WT("打开打印机对话框"), _WT("OpenPrintSetDlg"), _WT("打开打印机设置对话框。返回1：点击了确定按钮；2：点击了取消按钮。"),1 , 0,SDT_INT , 0, LVL_SIMPLE,0 ,0 ,2, OpenPrintSetDlgArg },
		//{ _WT("创建快捷方式"), _WT("CreateLink"), _WT("建立指定的快捷方式文件,返回是否成功."),1 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,6, CreateLinkArg },
		{ _WT("取屏幕DPI"), _WT("GetMoniterDPI"), _WT("返回指定窗口句柄所处显示器的当前DPI(缩放比例). hWnd: 提供所欲检查窗口句柄,为NULL表示使用桌面窗口(主显示器)."),3 , 0,SDT_DOUBLE , 0, LVL_SIMPLE,0 ,0 ,1, GetMoniterDPIArg },
		{ _WT("隐藏鼠标"), _WT("HideCursor"), _WT("隐藏鼠标光标.注意: 每显示一次,内部计数会加一,每隐藏一次,内部计数会减一,只有当内部计数值大于等于0时,鼠标光标才会被显示."),3 , 0,0 , 0, LVL_SIMPLE,0 ,0 ,0, 0 },
		{ _WT("显示鼠标"), _WT("ShowCursor"), _WT("显示鼠标光标.注意: 每显示一次,内部计数会加一,每隐藏一次,内部计数会减一,只有当内部计数值大于等于0时,鼠标光标才会被显示."),3 , 0,0 , 0, LVL_SIMPLE,0 ,0 ,0, 0 },
		{ _WT("取图片格式"), _WT("GetPictureFormat"), _WT("获取指定图片格式，失败返回空"),1 , 0,SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,1, GetPictureFormatArg },
		{ _WT("取硬盘编号"), _WT("GetDiskNumber"), _WT("获取硬盘的编号（出场带的）"),1 , 0,SDT_TEXT , 0, LVL_SIMPLE,0 ,0 ,0,0 },
		{ _WT("蜂鸣"), _WT("MessageBeep"), _WT("通过计算机媒体设备或者喇叭发出一个声音。"),1 , 0,0 , 0, LVL_SIMPLE,0 ,0 ,1,MessageBeepArg },
		{ _WT("圆角化窗口"), _WT("RoundedWindow"), _WT(" 圆角化置顶窗口"),3 , 0,0 , 0, LVL_SIMPLE,0 ,0 ,3,RoundedWindowArg },
		{ _WT("窗口置顶"), _WT("SetForegroundWindow"), _WT(" 置顶置顶窗口"),3 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,2,SetForegroundWindowArg },
		{ _WT("程序提权"), _WT("UpPrivilegeValue"), _WT("提升本程序的权限"),1 , 0,SDT_BOOL , 0, LVL_SIMPLE,0 ,0 ,0,0 },

};
//单独一个cpp文件，防止静态链接问题

PFN_EXECUTE_CMD ExecuteCommand[] =
{
	eapi_fnGetKeyboardLockState,
	eapi_fnSimulateKey,
	eapi_fnSimulateMouse,
	eapi_fnGetHDInfo,
	 eapi_fnGetDrivesNum,
	 eapi_fnGetDrivesList,
	 eapi_fnPopupCdrom,
	 eapi_fnCloseCdrom,
	 eapi_fnGetCdrom,
	 eapi_fnIsDiskInside,
	 eapi_fnGetProcessList,
	 eapi_fnKillProcess,
	 eapi_fnGetDllList,
	 eapi_fnGetHungProgramList,
	 eapi_fnGetSystemInfo,
	 eapi_fnGetBiosInfo,
	 eapi_fnGetFileVersionInfo,
	 eapi_fnGetCpuInfo,
	 eapi_fnGetCpuUsges,
	 eapi_fnGetMemoryInfo,
	 eapi_fnGetAudioCard,
	 eapi_fnOpenMonitor,
	 eapi_fnCloseMonitor,
	 eapi_fnAddRightMenu,
	 eapi_fnDeleteRightMenu,
	 eapi_fnSetAutoRun,
	 eapi_fnDeleteTempFile,
	 eapi_fnClearHistory,
	 eapi_fnGetFontList,
	 eapi_fnAddFont,
	 eapi_fnRemoveFont,
	 eapi_fnGetImageWidth,eapi_fnGetImageHeight,
	 eapi_fnGetIconFromResource,eapi_fnGetIEVersion,
	 eapi_fnAddButtonToIE,
	 eapi_fnDeleteButtonFromIE,eapi_fnCreateProgramGroup,
	 eapi_fnDeleteProgramGroup,eapi_fnCreateProgramItem,eapi_fnDeleteProgramItem,
	 eapi_fnGetShortCutTarget,eapi_fnGetApapterList,eapi_fnGetLocalAdapterName,eapi_fnGetLocalMac,
	 eapi_fnGetRemoteMac,eapi_fnGetRemoteName,eapi_fnGetIpFromHostName,eapi_fnRunEmailAddr,eapi_fnGetNetList,
	 eapi_fnGetGroupList,eapi_fnGetComputerList,eapi_fnIsConnectToInternet,eapi_fnIsLoginNet,eapi_fnCheckPort
	 ,eapi_fnOpenSysWindow, eapi_fnOpenURL, eapi_fnHideDesktopIcon, eapi_fnShowDesktopIcon, eapi_fnHideTaskBar, eapi_fnShowTaskBar
	,eapi_fnHideClock,eapi_fnShowClock,eapi_fnHideStartButton,eapi_fnShowStartButton,eapi_fnSetDeskWallPaper,
	eapi_fnSetDiaphaneity,eapi_fnGetVideoList,eapi_fnGetCurVideo,eapi_fnSetResolveRatio,eapi_fnChangeUnit,
	eapi_fnGetPointRGB,eapi_fnSetCapture,eapi_fnReleaseCapture,eapi_fnGetScreenBitmap,eapi_fnGetAllWindowsList,
	eapi_fnGetWindowText,	eapi_fnGetClassName,eapi_fnGetHwndFromPoint,eapi_fnNetAddConnection,eapi_fnNetSendMessage, eapi_fnGetShareResourceList
	,eapi_fnCancelNetConnection
	,eapi_fnCancelAutoRun,eapi_fnsprintf,eapi_fnGetPrinterList,eapi_fnGetDefaultPrinter,eapi_fnSetDefaultPrinter

	,eapi_fnOpenPrintSetDlg,/*eapi_fnCreateLink*/eapi_fnGetMoniterDPI,eapi_fnHideCursor,eapi_fnShowCursor,eapi_fnGetPictureFormat,eapi_fnGetDiskNumber
	,eapi_fnMessageBeep,eapi_fnRoundedWindow,eapi_fnSetForegroundWindow,eapi_fnSetForegroundWindow

	// 所有需要库中调用的函数

};
static LIB_INFO LibInfo =
{

	/* { 库格式号, GUID串号, 主版本号, 次版本号, 构建版本号, 系统主版本号, 系统次版本号, 核心库主版本号, 核心库次版本号,

	支持库名, 支持库语言, 支持库描述, 支持库状态,

	作者姓名, 邮政编码, 通信地址, 电话号码, 传真号码, 电子邮箱, 主页地址, 其它信息,

	类型数量, 类型指针, 类别数量, 命令类别, 命令总数, 命令指针, 命令入口,

	附加功能, 功能描述, 消息指针, 超级模板, 模板描述,

	常量数量, 常量指针, 外部文件} */
	LIB_FORMAT_VER,//库格式号
	_T(LIB_GUID_STR),//GUID串号
	LIB_MajorVersion,//主版本号
	LIB_MinorVersion,//次版本号
	LIB_BuildNumber,//构建版本号
	LIB_SysMajorVer,//系统主版本号
	LIB_SysMinorVer,//系统次版本号
	LIB_KrnlLibMajorVer,//核心库主版本号
	LIB_KrnlLibMinorVer,//核心库次版本号
	_T(LIB_NAME_STR),//支持库名
	__GBK_LANG_VER,//支持库语言
	_WT(LIB_DESCRIPTION_STR),//支持库描述
	_LIB_OS(__OS_WIN),//支持库状态
	_WT(LIB_Author),//作者姓名
	_WT(LIB_ZipCode),// 邮政编码
	_WT(LIB_Address),//通信地址
	_WT(LIB_Phone),//电话号码
	_WT(LIB_Fax),//传真号码
	_WT(LIB_Email),//电子邮箱
	_WT(LIB_HomePage),//主页地址
	_WT(LIB_Other),//其它信息
	sizeof(DataTypes) / sizeof(LIB_DATA_TYPE_INFO),//类型数量
	DataTypes,//类型指针
	LIB_TYPE_COUNT,//类别数量
	_WT(LIB_TYPE_STR),//命令类别
   sizeof(Commands) / sizeof(Commands[0]),//命令总数
	Commands,//命令指针
	ExecuteCommand,//命令入口
	NULL,//附加功能
	NULL,//功能描述
	eapi_ProcessNotifyLib,//消息指针
	NULL,//超级模板
	NULL,//模板描述
	0,//常量数量
	0,//常量指针
	NULL//外部文件
};
extern "C" PLIB_INFO  GetNewInf()

{

	return (&LibInfo);

};

#endif
EXTERN_C INT WINAPI eapi_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{

#ifndef __E_STATIC_LIB

	if (nMsg == NL_GET_CMD_FUNC_NAMES) // 返回所有命令实现函数的的函数名称数组(char*[]), 支持静态编译的动态库必须处理

		return (INT)CommandNames;

	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME) // 返回处理系统通知的函数名称(PFN_NOTIFY_LIB函数名称), 支持静态编译的动态库必须处理

		return (INT)LIBARAYNAME;

	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;

	// 返回静态库所依赖的其它静态库文件名列表(格式为\0分隔的文本,结尾两个\0), 支持静态编译的动态库必须处理

	// kernel32.lib user32.lib gdi32.lib 等常用的系统库不需要放在此列表中

	// 返回NULL或NR_ERR表示不指定依赖文件

#endif

	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);

}
