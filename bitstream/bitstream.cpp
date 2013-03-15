#include "bitstream.h"

#include <cstring>
//#include <cmath>

Bitstream::Bitstream(int size) : m_size(size)
{
    m_position = 0;
    m_data = new bs_raw[size];
    memset(m_data, 0, size);
}

Bitstream::~Bitstream()
{
    delete[] m_data;
}

bs_raw* Bitstream::getCurrentByte()
{
    return m_data + m_position / 8;
}

int Bitstream::getBitOffset()
{
    return m_position % 8;
}

void Bitstream::writeBit(int bit)
{
    bs_raw* byte = getCurrentByte();
    int offset = getBitOffset();
    *byte |= (bit<<offset);
    m_position++;
}

void Bitstream::write(bs_raw* data, int nBits)
{
    for (int i = 0; i < nBits; i++) {
        // ...
    }
}
