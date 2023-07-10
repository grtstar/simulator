#include <string.h>

#include <lcm/lcm-cpp.hpp>
#include <lcm/lcm.h>
#include <map>

#include "mars_message/Bumper.hpp"
#include "mars_message/GridMap.hpp"
#include "mars_message/Imu.hpp"
#include "mars_message/IrCode.hpp"
#include "mars_message/LaserScan.hpp"
#include "mars_message/ObsAvoidance.hpp"
#include "mars_message/Odometry.hpp"
#include "mars_message/Pose.hpp"
#include "mars_message/Twist.hpp"
#include "mars_message/Vector3.hpp"
#include "mars_message/ClearComponent.hpp"
#include "mars_message/Coder.hpp"
#include "mars_message/DevicePower.hpp"
#include "mars_message/Debug.hpp"
#include "mars_message/PointCloud.hpp"
#include "mars_message/RobotStatus.hpp"
#include "mars_message/Event.hpp"

#include "utils/json.hpp"
#include "oal/time_tick.h"

using namespace mars_message;
using json = nlohmann::json;

const char* jsonBumper = R"(
{
    "timestampMs" : %ld,
    "mask" : %02X
}
)";

const char* jsonBumperEmpty = R"(
{
    "timestampMs" : 0,
    "mask" : 0
}
)";

const char* jsonGridMap = R"(
{
    "timestampMs" : %ld,
    "mapLoadTime" : %ld,
    "resolution" : %f,
    "width" : %d,
    "height" : %d,
    "orign" : {pose:{x:%lf, y:%lf, z:%lf}, orientation:{w:%lf, x:%lf, y:%lf z:%lf}},
    "pointCount" : %d,
    "data" : [%s]
}
)";

const char* jsonGridMapEmpty = R"(
{
    "timestampMs" : 0,
    "mapLoadTime" : 0,
    "resolution" : 0.0,
    "width" : 0,
    "height" : 0,
    "orign" : {pose:{x:0.0, y:0.0, z:0.0}, orientation:{w:0.0, x:0.0, y:0.0 z:0.0}},
    "pointCount" : 0,
    "data" : []
}
)";

const char* jsonLaserScan = R"(
{
    "timestampMs" : %ld,
    "angleMin" : %f,
    "angleMax" : %f,
    "angleIncrement" : %f,
    "timeIncrement" : %f,
    "scanTime" : %f,
    "rangeMin" : %f,
    "rangeMax" : %f,
    "count" : %d,
    "range" : [%s],
    "intensities" : [%s]
}
)";

const char* jsonLaserScanEmpty = R"(
{
    "timestampMs" : 0,
    "angleMin" : 0.0,
    "angleMax" : 0.0,
    "angleIncrement" : 0.0,
    "timeIncrement" : 0.0,
    "scanTime" : 0.0,
    "rangeMin" : 0.0,
    "rangeMax" : 0.0,
    "count" : 0,
    "range" : [],
    "intensities" : []
}
)";

const char* jsonPointCloud = R"(
{
    "timestampMs" : %ld,
    "scanTime" : %f,
    "count" : %d,
    "points" : [%s],
    "intensities" : [%s],
}
)";

const char* jsonPointCloudEmpty = R"(
{
    "timestampMs" : 0,
    "scanTime" : 0.0,
    "count" : 0,
    "points" : [],
    "intensities" : [],
}
)";


const char* jsonOdometry = R"(
{
    "timestampMs" : %ld,
    "pose : {
                "pose" : {"x":%lf, "y":%lf, "z":%lf},
                "orientation" : {"w":%lf, "x":%lf, "y":%lf, "z":%lf}
            },
    "linearVelocity" : {"x":%lf, "y":%lf, "z":%lf},
    "angularVelocity" : {"x":%lf, "y":%lf, "z":%lf}
}
)";

const char* jsonOdometryEmpty = R"(
{
    "timestampMs" : 0,
    "pose : {
                "pose" : {"x":0.0, "y":0.0, "z":0.0},
                "orientation" : {"w":0.0, "x":0.0, "y":0.0, "z":0.0}
            },
    "linearVelocity" : {"x":0.0, "y":0.0, "z":0.0},
    "angularVelocity" : {"x":0.0, "y":0.0, "z":0.0}
}
)";

const char* jsonImu = R"(
{
    "timestampMs" : %ld,
    "orientation" : {"w":%lf, "x":%lf, "y":%lf, "z":%lf},
    "orientationCovariance" : [%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf],
    "angularVelocity" : {"x":%lf, "y":%lf, "z":%lf},
    "angularVelocityCovariance" : [%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf],
    "linearAcceleraion" : {"x":%lf, "y":%lf, "z":%lf},
    "linearAcceleraionCovariance" : [%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf],
}
)";

const char* jsonImuEmpty = R"(
{
    "timestampMs" : 0,
    "orientation" : {"w":0.0, "x":0.0, "y":0.0, "z":0.0},
    "orientationCovariance" : [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "angularVelocity" : {"x":0.0, "y":0.0, "z":0.0},
    "angularVelocityCovariance" : [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "linearAcceleraion" : {"x":0.0, "y":0.0, "z":0.0},
    "linearAcceleraionCovariance" : [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
}
)";

const char* jsonIrCode = R"(
{
    "timestampMs" : %ld,
    "count" : %d,
    "code" : [%d]
}
)";

const char* jsonIrCodeEmpty = R"(
{
    "timestampMs" : 9,
    "count" : 0,
    "code" : []
}
)";

const char* jsonTwist = R"(
{
    "timestampMs" : %ld,
    "linearVelocity" : {"x":%lf, "y":%lf, "z":%lf},
    "angularVelocity" : {"x":%lf, "y":%lf, "z":%lf}
}
)";

const char* jsonTwistEmpty = R"(
{
    "timestampMs" : 0.0,
    "linearVelocity" : {"x":0.0, "y":0.0, "z":0.0},
    "angularVelocity" : {"x":0.0, "y":0.0, "z":0.0}
}
)";

const char* jsonPose = R"(
{
    "pose" : {"x":%lf, "y":%lf, "z":%lf},
    "orientation" : {"w":%lf, "x":%lf, "y":%lf, "z":%lf}
}
)";

const char* jsonPoseEmpty = R"(
{
    "pose" : {"x":0.0, "y":0.0, "z":0.0},
    "orientation" : {"w":0.0, "x":0.0, "y":0.0, "z":0.0}
}
)";


const char* jsonCoder = R"(
{
    "codeL" : %d,
    "codeR" : %d,
    "coderLPerSec" : %d,
    "coderRPerSec" : %d
}
)";

const char* jsonCoderEmpty = R"(
{
    "codeL" : 0,
    "codeR" : 0,
    "coderLPerSec" : 0,
    "coderRPerSec" : 0
}
)";

const char* jsonClearComponent = R"(
{
    "reply" : %d,
    "fanRpm" : %d,
    "gtRpm: : %d,
    "gtOffTime" : %d,
    "gtOnDegree" : %d,
    "gtCycle" : %d,
    "gtCleanDegree" : %d,
    "rbrushRpm" : %d,
    "mbrushRpm" : %d,
    "pumpOnTime" : %d,
    "pumpOffTime" : %d,
    "pump2OnTime" : %d,
    "pump2OffTime" : %d
}
)";

const char* jsonClearComponentEmpty = R"(
{
    "reply" : 0,
    "fanRpm" : -1,
    "gtRpm: : -1,
    "gtOffTime" : -1,
    "gtOnDegree" : -1,
    "gtCycle" : -1,
    "gtCleanDegree" : -1,
    "rbrushRpm" : -1,
    "mbrushRpm" : -1,
    "pumpOnTime" : -1,
    "pumpOffTime" : -1,
    "pump2OnTime" : -1,
    "pump2OffTime" : -1
}
)";

const char* jsonDevicePower = R"(
{
    "deviceName":"%s",
    "power":%d
}
)";

const char* jsonDevicePowerEmpty = R"(
{
    "deviceName":"",
    "power":0
}
)";


const char* jsonDebug = R"(
{
    "cmd":"%s"
}
)";

const char* jsonDebugEmpty = R"(
{
    "cmd":""
}
)";


const char* jsonKevt = R"(
{
    "event":"%s",
    "param":%d
}
)";

const char* jsonKevtEmpty = R"(
{
    "event":"CKEY",
    "param":0
}
)";


std::string AddPrefix(const char* str)
{
    std::string  s;
    for(int i=0; i<strlen(str); i++)
    {
        if(str[i] == '\"')
        {
            s += "\\\"";
        }
        else
        {
            s += str[i];
        }
    }
    return s;
}


struct MsgInfo
{
    const char* msgType;
    const char* msgJson;
    const char* msgJsonEmpty;
};

MsgInfo msgInfo[] = 
{
    {"Bumper", jsonBumper, jsonBumperEmpty},
    {"GridMap", jsonGridMap, jsonGridMapEmpty},
    {"LaserScan", jsonLaserScan, jsonLaserScanEmpty},
    {"Odomety", jsonOdometry, jsonOdometryEmpty},
    {"Imu", jsonImu, jsonImuEmpty},
    {"IrCode", jsonIrCode, jsonIrCodeEmpty},
    {"Pose", jsonPose, jsonPoseEmpty},
    {"Twist", jsonTwist, jsonTwistEmpty},
    {"ClearComponent", jsonClearComponent, jsonClearComponentEmpty},
    {"Coder", jsonCoder, jsonCoderEmpty},
    {"DevicePower", jsonDevicePower, jsonDevicePowerEmpty},
    {"Debug", jsonDebug, jsonDebugEmpty},
    {"PointCloud", jsonPointCloud, jsonPointCloudEmpty},
    {"Kevt", jsonKevt, jsonKevtEmpty},
};


const char* lcmd_complete_sh = R"(
_lcmd()  
{  
    COMPREPLY=()  
    local cur=${COMP_WORDS[COMP_CWORD]};  
    local cmd=${COMP_WORDS[COMP_CWORD-1]};  
    case $cmd in  
    'lcmd')  
          COMPREPLY=( $(compgen -W '-h -p -m' -- $cur) ) ;;  
    '*')  
          ;;  
    esac  
    if [[ ${COMP_CWORD} -eq 3 ]]; then  
          COMPREPLY=($(compgen -W '%s' -- $cur))  
    fi  
    if [[ "${COMP_WORDS[1]}" == "-p" && ${COMP_CWORD} -eq 4 ]]; then  
    case $cmd in  
          %s  
    esac
    fi
    return 0  
}  
complete -F _lcmd lcmd
)";


static void gen_complete()
{
    char sh[10240] = {0};
    char w[128] = {0};
    for(int i=0; i<sizeof(msgInfo)/sizeof(msgInfo[0]); i++)
    {
        strcat(w, msgInfo[i].msgType);
        strcat(w, " ");
    }

    char pw[4096] = {0};
    int l=0;
    for(int i=0; i<sizeof(msgInfo)/sizeof(msgInfo[0]); i++)
    {
        l += sprintf(pw+l, "\n");
        l += sprintf(pw+l, "'%s')", msgInfo[i].msgType);
        l += sprintf(pw+l, "\n");
        l += sprintf(pw+l, R"(COMPREPLY="'%s'";;)", AddPrefix(msgInfo[i].msgJsonEmpty).c_str());
        l += sprintf(pw+l, "\n");

    }

    sprintf(sh, lcmd_complete_sh, w, pw);

    FILE *fp = fopen("/tmp/lcmd_complete.sh", "w");
    fwrite(sh, strlen(sh), 1, fp);
    fclose(fp);
    //system("bash soucre /tmp/lcmd_complete.sh");
}

static void usage()
{
    printf(
        "\n"
        "usage: lcmd [OPTIONS]\n"
        "\n"
        "lcm messages publish and subscibe debug.\n"
        "\n"
        "  -h     prints this help text and exits\n"
        "  -p [topic] [type] [msg]   publish msg on topic\n"
        "  -m [topic] [type] subscibe msg on topic\n"
        );
    exit(1);
}

class MessageHandler
{
public:
    void OnBumper(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Bumper *msg)
    {
        printf(jsonBumper, msg->timestampMs, msg->mask);
    }
    void OnGridmap(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const GridMap *msg)
    {
        char data[2048] = {0};
        int len = msg->pointCount;
        if(len > 100) len = 100;
        int l = 0;
        for(int i=0; i<len; i++)
        {
            l += sprintf(data + l, "%d", msg->data[i]);
            if(i != len-1)
            {
                l += sprintf(data + l, ", ");
            }
        }
        printf(jsonGridMap, msg->timestampMs, msg->mapLoadTime, msg->resolution, msg->width, msg->height, 
                            msg->origin.pose.x, msg->origin.pose.y, msg->origin.pose.z, 
                            msg->origin.orientation.w, msg->origin.orientation.x, msg->origin.orientation.y, msg->origin.orientation.z,
                            msg->pointCount, data);
    }
    void OnImu(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Imu *msg)
    {
    }
    void OnIrCode(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const IrCode *msg)
    {
        char code[128];
        int l = 0; 
        for(int i=0; i<msg->count; i++)
        {
            l += sprintf(code + l, "%02X ", msg->code[i]);
        }
        printf(jsonIrCode, msg->timestampMs, msg->count, code);
    }
    void OnLaserScan(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const LaserScan *msg)
    {
        char ranges[20480] = {0};
        char intensities[20480] = {0};

        int l = 0;
        for(int i=0; i<msg->count; i++)
        {
            l += sprintf(ranges + l, "%f", msg->ranges[i]);
            if(i != msg->count-1)
            {
                l += sprintf(ranges + l, ", ");
            }
        }

        l = 0;
        for(int i=0; i<msg->count; i++)
        {
            l += sprintf(intensities + l, "%f", msg->intensities[i]);
            if(i != msg->count-1)
            {
                l += sprintf(intensities + l, ", ");
            }
        }

        printf(jsonLaserScan, msg->timestampMs, msg->angleMin, msg->angleMax, msg->angleIncrement,
                                msg->timeIncrement, msg->scanTime, msg->rangeMin, msg->rangeMax,
                                msg->count, ranges, intensities);
    }
    void OnOdometry(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Odometry *msg)
    {
        printf(jsonOdometry, msg->timestampMs, msg->pose.pose.x, msg->pose.pose.y, msg->pose.pose.z,
                                msg->pose.orientation.w, msg->pose.orientation.x, msg->pose.orientation.y, msg->pose.orientation.z,
                                msg->linearVelocity.x, msg->linearVelocity.y, msg->linearVelocity.z,
                                msg->angularVelocity.x, msg->angularVelocity.y, msg->angularVelocity.z);
    }
    void OnPose(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Pose *msg)
    {
        printf(jsonPose, msg->pose.x, msg->pose.y, msg->pose.z, 
                        msg->orientation.w, msg->orientation.x, msg->orientation.y, msg->orientation.z);
    }
    void OnTwist(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Twist *msg)
    {
        printf(jsonTwist, msg->timestampMs, msg->linearVelocity.x, msg->linearVelocity.y, msg->linearVelocity.z,
                            msg->angularVelocity.x, msg->angularVelocity.y, msg->angularVelocity.z);
    }
    void OnClearComponent(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const ClearComponent *msg)
    {
        printf(jsonClearComponent, msg->reply, msg->fanRpm, msg->gtRpm, msg->gtOffTime,
                                    msg->gtOnDegree, msg->gtCycle, msg->gtCleanDegree, msg->rbrushRpm,
                                    msg->mbrushRpm, msg->pumpOnTime, msg->pumpOffTime, msg->pump2OnTime, msg->pump2OffTime);
    }
    void OnCoder(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Coder *msg)
    {
        printf(jsonCoder, msg->coderL, msg->coderR, msg->coderLPerSec, msg->coderRPerSec);
    }
    void OnDevicePower(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const DevicePower *msg)
    {
        printf(jsonDevicePower, msg->deviceName.c_str(), msg->power);
    }
    void OnDebug(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const Debug *msg)
    {
        printf(jsonDebug, msg->cmd.c_str());
    }
    void OnPointCloud(const lcm::ReceiveBuffer *rbuf, const std::string &channel, const PointCloud *msg)
    {
        printf(jsonPointCloud, msg->timestampMs, msg->timestampMs, msg->count, "", "");
    }
};

void not_support(char *s)
{
    printf("Not Support Publish %s\n", s);
}

int main(int argc, char *argv[])
{
    gen_complete();

    if(argc < 4)
    {
        usage();
    }
    lcm::LCM lcm;

    if (!lcm.good())
    {
        printf("lcm is error\n");
        return 1;
    }
    
    if(argc == 4)
    {
        if(strcmp("-m", argv[1]) == 0)
        {
            MessageHandler handler;
            std::string type = argv[3];
            if(type == "Bumper")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnBumper, &handler);
            }
            if(type == "GridMap")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnGridmap, &handler);
            }
            if(type == "Imu")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnImu, &handler);
            }
            if(type == "IrCode")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnIrCode, &handler);
            }
            if(type == "LaserScan")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnLaserScan, &handler);
            }
            if(type == "Odometry")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnOdometry, &handler);
            }
            if(type == "Pose")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnPose, &handler);
            }
            if(type == "Twist")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnTwist, &handler);
            }
            if(type == "ClearComponent")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnClearComponent, &handler);
            }
            if(type == "Coder")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnCoder, &handler);
            }
            if(type == "DevicePower")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnDevicePower, &handler);
            }
            if(type == "Debug")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnDebug, &handler);
            }
            if(type == "PointCloud")
            {
                lcm.subscribe(argv[2], &MessageHandler::OnPointCloud, &handler);
            }
        }
        else 
        {
            usage();
        }
    }

    if(argc == 5)
    {
        if(strcmp("-p", argv[1]) == 0)
        {
            std::string type = argv[3];
            if(type == "Bumper")
            {
                json m = json::parse(argv[4]);
                Bumper bumper;
                bumper.timestampMs = TimeTick::Ms();
                bumper.mask = m["mask"];
                lcm.publish(argv[2], &bumper);
            }
            if(type == "GridMap")
            {
            }
            if(type == "Imu")
            {
                
            }
            if(type == "IrCode")
            {
                json m = json::parse(argv[4]);
                IrCode msg;
                msg.timestampMs = TimeTick::Ms();
                msg.count = m["count"];
                //msg.code = m["code"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "LaserScan")
            {
            }
            if(type == "Odometry")
            {
            }
            if(type == "Pose")
            {
                json m = json::parse(argv[4]);
                Pose msg;
                msg.pose.x = m["pose"]["x"];
                msg.pose.y = m["pose"]["y"];
                msg.pose.z = m["pose"]["z"];
                msg.orientation.w = m["orientation"]["w"];
                msg.orientation.x = m["orientation"]["x"];
                msg.orientation.y = m["orientation"]["y"];
                msg.orientation.z = m["orientation"]["z"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "Twist")
            {
                json m = json::parse(argv[4]);
                Twist msg;
                msg.timestampMs = TimeTick::Ms();
                msg.linearVelocity.x = m["linearVelocity"]["x"];
                msg.linearVelocity.y = m["linearVelocity"]["y"];
                msg.linearVelocity.z = m["linearVelocity"]["z"];
                msg.angularVelocity.x = m["angularVelocity"]["x"];
                msg.angularVelocity.y = m["angularVelocity"]["y"];
                msg.angularVelocity.z = m["angularVelocity"]["z"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "ClearComponent")
            {
                json m = json::parse(argv[4]);
                ClearComponent msg;
                msg.reply = m["reply"];
                msg.fanRpm = m["fanRpm"];
                msg.gtRpm = m["gtRpm"];
                msg.gtOffTime = m["gtOffTime"];
                msg.gtOnDegree = m["gtOnDegree"];
                msg.gtCycle = m["gtCycle"];
                msg.gtCleanDegree = m["gtCleanDegree"];
                msg.rbrushRpm = m["rbrushRpm"];
                msg.mbrushRpm = m["mbrushRpm"];
                msg.pumpOnTime = m["pumpOnTime"];
                msg.pumpOffTime = m["pumpOffTime"];
                msg.pump2OnTime = m["pump2OnTime"];
                msg.pump2OffTime = m["pump2OffTime"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "Coder")
            {
                json m = json::parse(argv[4]);

                Coder msg;
                msg.coderL = m["codeL"];
                msg.coderR = m["codeR"];
                msg.coderLPerSec = m["coderLPerSec"];
                msg.coderRPerSec = m["coderRPerSec"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "DevicePower")
            {
                json m = json::parse(argv[4]);

                DevicePower msg;
                msg.deviceName = m["deviceName"];
                msg.power = m["power"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "Debug")
            {
                json m = json::parse(argv[4]);

                Debug msg;
                msg.cmd = m["cmd"];
                lcm.publish(argv[2], &msg);
            }
            if(type == "Kevt")
            {
                json m = json::parse(argv[4]);

                Event msg;
                std::string s = m["event"];
                msg.event = 0;
                for(int i=0; i<s.length();i++)
                {
                    msg.event += (int32_t)s.at(i)<<((3-i)*8);
                }
                msg.param = m["param"];
                lcm.publish(argv[2], &msg);
            }
        }
        else
        {
            usage();
        }
    }

    while (lcm.handle() == 0)
    {
    }
}