
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stack>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "libco/co_routine.h"
#include "bytebuf.h"

namespace vmqtt
{

struct task_t
{
  stCoRoutine_t *co;
  int fd;
  time_t keep_alive;
};

class MqttController
{

public:
  void test();
  bool protocol_handler(task_t *co, char *buf, size_t nbyte);
};

} // namespace vmqtt