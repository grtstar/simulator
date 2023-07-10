#pragma once

enum
{
    PLAY_QUEUE,     // 等待前一个语音播放完成后播放
    PLAY_INTERUPT,  // 播放时,打断前一个未播放完的语音
    PLAY_TOGETHER   // 和前一个未播放完成的语音一起播放
};

#define V_BUTTON_BEEP          'Beep'

#define V_POWER_ON      'PwOn'
#define V_POWEROFF      'PwOf'
#define V_START_CLEAN   'StCl'
#define V_PAUSE_CLEAN   'PaCl'
#define V_STOP_CLEAN    'SpCl'
#define V_ZONE_CLEAN    'Zone'
#define V_SPOT_CLEAN    'Spot'
#define V_ROOM_CLEAN    'Room'
#define V_FINISH_CLEAN  'FiCl'
#define V_QUICK_MAPPING 'QMap'
#define V_QMAP_FAIL     'QMNG'
#define V_QMAP_SUCC     'QMOK'
#define V_GO_CHARGE     'GoCh'
#define V_CHARGEING     'Chrg'
#define V_CHARGE_FULL   'ChFu'
#define V_BATTERAY_LOW  'BaLo'

#define V_RELOCATE_START   'LoSt'
#define V_RELOCATE_SUCC    'LoOK'
#define V_RELOCATE_FAIL    'LoNG'

#define V_WIFI_CONFIG       'WiCf'
#define V_WIFI_CONNECTED    'WiOK'
#define V_WIFI_RECV_PWD     'WiPw'
#define V_WIFI_FAIL         'WiNG'
#define V_SERVER_CONNECTED  'SrOK'

#define V_COMMUNICATE_ERROR     'CoEr'
#define V_BUMPER_ERROR          'BpEr'
#define V_LIDAR_ERROR           'LiEr'
#define V_LIDAR1D_ERROR         'L1Er'
#define V_EDGE_ERROR            'EgEr'
#define V_CLIFF_ERROR           'ClEr'
#define V_LIDAR_BUMPER_ERROR    'LBEr'

#define V_SIDEBRUSH_ERROR       'SBEr'
#define V_MAINBRUSH_ERROR       'MBEr'
#define V_GUNTONG_ERROR         'GTEr'
#define V_LWHEEL_ERROR          'LWEr'
#define V_RWHEEL_ERROR          'RWEr'
#define V_DUSTBOX_ERROR         'DuEr'
#define V_MOP_ERROR             'MoEr'
#define V_FAN_ERROR             'FnEr'
#define V_HANGUP_ERROR          'HgUp'

#define V_START_UPDATE          'StUp'
#define V_UPDATE_FAIL           'UpNG'
#define V_UPDATE_SUCC           'UpOK'

#define V_SEEK_ROBOT            'SeeK'

#define V_FTEST_ENTER           'FTEt'
#define V_FTEST_DINGDONG        'FTDn'
#define V_FTEST_OK              'FTOK'     // 成功
#define V_FTEST_NG              'FTNG'     // 失败
#define V_FTEST_CT              'FTCT'     // 继续
#define V_FTEST_NEXT            'TFNX'     // 单项完成
#define V_FTEST_START           'FTSt'     // 1.  进入产测模式
#define V_FTEST_WIFI            'FTWF'     // 2. WiFi 测试
#define V_FTEST_FAN             'FTFN'     // 3.风机检测
#define V_FTEST_WLAD            'FTWD'     // 4. 轮组前进
#define V_FTEST_WLRE            'FTWR'     // 5. 轮组后退
#define V_FTEST_ZSAD            'FTZD'     // 6.中扫正转
#define V_FTEST_ZSRE            'FTZR'     // 7. 中扫反转
#define V_FTEST_GTSL            'FTGS'     // 8.滚筒正转速度
#define V_FTEST_BATTERY_VOLTAGE 'FTBV'     // 9.电池电压电流检测
#define V_FTEST_BATTERY_TEMPERTURE 'FTBT'  // 10电池温度测试
#define V_FTEST_IMU             'FTIU'     // 11陀螺仪检测
#define V_FTEST_CARPET          'FTCP'     // 12.超声波检测
#define V_FTEST_BUMPER          'FTBR'     // 13. 碰撞测试
#define V_FTEST_SCAND1          'FTSC'     // 14.线激光检测
#define V_FTEST_WHEEL_BSLAD     'FTWS'     // 15. 轮组和边刷过载
#define V_FTEST_ZSLOAD          'FTZd'     // 16. 中扫过载
#define V_FTEST_GTLOAD          'FTGD'     // 17. 滚筒过载
#define V_FTEST_REIGN           'FTID'     // 18. 在位检测测试
#define V_FTEST_WAITFULL        'FTWf'     // 19 水位检测
#define V_FTEST_WPARPUMP        'FTWA'     // 20. 气泵、水泵电流检测
#define V_FTEST_CHARGRIAM       'FTCI'     // 21. 充电检测
#define V_FTEST_CLIFFTSET       'FTCt'     // 22. 红外跌落测试
#define V_FTEST_EDGECORR        'FTEC'     // 23.贴边测距校准
#define V_FTEST_CLIFF           'FTCL'     // 24.红外断崖校准
#define V_FTEST_LIDARCORR       'FTLC'     // 25.雷达校准
#define V_FTEST_TSETOVER        'FTOV'     // 26. 结束产测模式
#define V_FTEST_SITEPARTS       'FTSP'     // 27.进入底盘测试
#define V_FTEST_CALIBRATION     'FTCA'     // 28. 进入校准模式