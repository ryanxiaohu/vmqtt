#pragma once

#include <stdlib.h>
#include <vector>
#include <string.h>
#include <exception>

using namespace std;

namespace vmqtt
{

class ByteBuf
{

public:
    ByteBuf();
    ByteBuf(int capacity);
    ~ByteBuf(void);

public:
    void writeByte(char value);
    void writeShort(short value);
    void writeInt(int value);
    void writeBytes(char *, int srcIndex, int length);
    void writeBytes(ByteBuf *buffer, int srcIndex, int length);
    void writeString(const char *str, int length);
    int getWriteIndex();

    void flush();
    void release();

public:
    char readByte();
    short readShort();
    int readInt();
    int readBytes(char *out, int length);
    int getReadIndex();
    int getReadableBytes();

private:
    void checkRead(int length);

private:
    int readIndex;
    int writeIndex;
    vector<char> dataList;
};

} // namespace vmqtt