#ifndef HORSEDATASTRUCT_H
#define HORSEDATASTRUCT_H
#define HORSENUMBER_1	 14
#define QIN_QPL_ROW_1	 7
#define QIN_QPL_COL_1	15
//#include <tchar.h>

typedef struct TagProtocolMsg
{
	int	MsgID;			//消息类型
	int nDataSize;		//后面发送的数据大小，后面无数据
	char Param[51];		//消息参数，多参数以\n分隔
	char Check[5];
}PROTOCOLMSG, *LPPROTOCOLMSG;
//马信息内存结构体描述
typedef struct TagHorseInfo
{
	int	HorseID;	 //马的唯一编号
	char HorseName[50]; 	//马名
}HORSEINFO, *LPHORSEINFO;

//赛程信息内存结构体描述
typedef struct TagPlanInfo
{
	char RaceDate[12];  //比赛日期
	int	RaceCount; //当日场数
}PLANINFO, *LPPLANINFO;

//赛事信息内存结构体描述
typedef struct TagRaceInfo
{
	int 	RaceID;	 //赛事ID
	int	RaceNO;	 //当日场次
	char RaceDate[12];	//比赛日期
	char RaceTime[10]; //比赛开始时间
	int 	CountTime; 	//比赛进行多少分钟
	int 	HorseCount; 	//参赛马数
}RACEINFO, *LPRACEINFO;

//WIN和PLA数据结构体描述
typedef struct TagWPDataInfo
{
	int  RaceID; //所属赛事ID
	int  HorseID; //马的唯一编号可关联马信息表
	int  HorseNO; //本场比赛中马的序号，比如第3号马
	float  WinValue; //数据值
	int AtTime; //所在时刻，正式开始比赛的时间,分钟单位
}WPDATAINFO, *LPWPDATAINFO;

//QIN和QPL数据结构体描述
typedef struct TagQDataInfo
{
	int  RaceID; //所属赛事ID
	int  HorseID; //马的唯一编号可关联马信息表
	int  HorseNO; //本场比赛中马的序号，比如第3号马
	float  QinValue; //数据值，由XNO与YNO组合得出
	int  YNO; //在Y轴上的第几号，跟它组合得出的数据
	int  AtTime; //所在时刻，正式开始比赛的时间,分钟单位
}QDATAINFO, *LPQDATAINFO;

//客户端命令状态
enum ClientCmdStatus {
	no_status = 1,
	//连接状态
	connect_status = 2,
	//连接状态
	disconnect_status = 3,
	//登陆状态
	login_status = 4,
	//请求马信息表状态
	request_horse_status = 5,
	//请求race_id状态
	request_race_id_status = 6,
	//提交赛长状态
	submit_race_time_status = 7,
	//提交实时数据状态
	submit_real_data_status = 8
};
struct DataOutput
{
	// image region 1
	int svmResult[HORSENUMBER_1];						// the index of the house name in the current sample
	int nameType[HORSENUMBER_1];						// 2: the horse name contains 2 char, 3: the name contains 3 char, 4: 4char

	float WIN[HORSENUMBER_1];
	float PLA[HORSENUMBER_1];

	// image region 2
	bool isQPL;							// true: QPL, false: QIN
	float QPL_QIN[QIN_QPL_ROW_1][QIN_QPL_COL_1];

	// image region 3
	int session;
	int raceTime;
};

#endif // HORSEDATASTRUCT_H
