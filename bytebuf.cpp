

#include "bytebuf.h"

namespace vmqtt
{

#define BYTE_BUFFER_SIZE 512

ByteBuf::ByteBuf()
{
    this->readIndex = 0;
    this->writeIndex = 0;
    this->dataList.reserve(BYTE_BUFFER_SIZE);
}

ByteBuf::ByteBuf(int capacity)
{
    this->readIndex = 0;
    this->writeIndex = 0;
    this->dataList.reserve(capacity);
}

ByteBuf::~ByteBuf() {}

void ByteBuf::flush()
{
    this->dataList.erase(this->dataList.begin(), this->dataList.begin() + this->readIndex);
    this->writeIndex -= this->readIndex;
    this->readIndex = 0;
}

void ByteBuf::release() {}

void ByteBuf::writeByte(char ch)
{
    this->dataList.push_back(ch);
    this->writeIndex += 0x01;
}

void ByteBuf::writeShort(short value)
{
    this->dataList.push_back(static_cast<char>(value >> 8));
    this->dataList.push_back(static_cast<char>(value));
    this->writeIndex += 0x02;
}

void ByteBuf::writeInt(int value)
{
    for (int i = 3; i >= 0; --i)
    {
        this->dataList.push_back(static_cast<char>(value >> (i * 8)));
    }
    this->writeIndex += 0x04;
}

void ByteBuf::writeBytes(char *str, int srcIndex, int length)
{
    for (int i = 0; i < length; ++i)
    {
        this->dataList.push_back(str[srcIndex + i]);
    }
    this->writeIndex += length;
}

void ByteBuf::writeBytes(ByteBuf *buf, int srcIndex, int length)
{
    for (int i = 0; i < length; ++i)
    {
        this->dataList.push_back(buf->dataList[srcIndex + i]);
    }
    this->writeIndex += length;
    buf->release();
}

void ByteBuf::writeString(const char *str, int length)
{
    for (int i = 0; i < length; ++i)
    {
        this->dataList.push_back(str[i]);
    }
    this->writeIndex += length;
}

int ByteBuf::getReadIndex()
{
    return this->readIndex;
}

int ByteBuf::getWriteIndex()
{
    return this->writeIndex;
}

int ByteBuf::readInt()
{
    checkRead(4);
    int value = 0;
    for (int i = 0; i < 4; ++i)
    {
        value <<= 8;
        value |= this->dataList[this->readIndex + i];
    }
    this->readIndex += 4;
    return value;
}

short ByteBuf::readShort()
{
    checkRead(2);
    int value = 0;
    for (int i = 0; i < 2; ++i)
    {
        value <<= 8;
        value |= this->dataList[this->readIndex + i];
    }
    this->readIndex += 2;
    return value;
}

char ByteBuf::readByte()
{
    checkRead(1);
    char value = this->dataList[this->readIndex];
    this->readIndex += 1;
    return value;
}

int ByteBuf::getReadableBytes()
{
    int size = this->writeIndex - this->readIndex;
    return size > 0 ? size : 0;
}

int ByteBuf::readBytes(char *out, int length)
{
    checkRead(length);
    int readEnd = this->readIndex + length;
    for (int i = this->readIndex; i < readEnd; ++i)
    {
        *out++ = this->dataList[i];
    }
    this->readIndex += length;
    return length;
}

void ByteBuf::checkRead(int length)
{
    if (length > this->getReadableBytes())
    {
        throw std::exception();
    }
}

} // namespace vmqtt