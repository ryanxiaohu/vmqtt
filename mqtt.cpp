

#include "mqtt.h"

namespace vmqtt
{

void MqttController::test()
{
}

bool MqttController::protocol_handler(task_t *co, char *buf, size_t nbyte)
{
    int fd = co->fd;
    int ret = read(fd, buf, nbyte);
    if (ret > 0)
    {
        char a = buf[0];
        bool retain = (a & 1) > 0;
        int qosLevel = (a & 0x06) >> 1;
        bool dupFlags = (a & 0x08) > 0;
        char msgType = (a >> 4) & 0x0F;

        printf("retain: %d, qosLevel: %d, dupFlag: %d, msgType: %d\n", retain, qosLevel, dupFlags, msgType);

        if (msgType == 0x01)
        {
            char ack[4];
            ack[0] = 0x02 << 4;
            ack[1] = 0x02;
            ack[2] = 0x00;
            ack[3] = 0x00;
            ret = write(fd, ack, sizeof(ack));
        }
        else if (msgType == 0x0C)
        {
            co->keep_alive = time(NULL);
            char ack[2];
            ack[0] = 0x0D << 4;
            ack[1] = 0x00;
            ret = write(fd, ack, sizeof(ack));
        }
    }

    printf("write ret: %d, errno: %d\n", ret, errno);
    return ret > 0 || (-1 == ret && EAGAIN == errno);
}

}