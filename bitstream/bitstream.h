#ifndef BITSTREAM_H
#define BITSTREAM_H

#define BITSTREAM_DEFAULT_SIZE 65536

typedef unsigned char bs_raw;

class Bitstream
{
public:
    Bitstream(int size=BITSTREAM_DEFAULT_SIZE);
    virtual ~Bitstream();
    int getSize() { return m_size; };
    int getPosition() { return m_position; };
    void write(bs_raw* data, int nBits);
    const bs_raw* getData() { return (const bs_raw*)m_data; };

    void writeBit(int bit);

protected:
    bs_raw* getCurrentByte();
    int getBitOffset();


private:
    int m_size;
    int m_position;
    bs_raw *m_data;

};

#endif // BITSTREAM_H
