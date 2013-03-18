#include <iostream>
#include <cstdio>
#include <cstring>
#include "bitstream.h"

using namespace std;

int g_nAssertions = 0;
#define ASSERT(C, E) { g_nAssertions++; if (!(C)) { \
    cout << __FILE__ << ":" << __LINE__ << " " << (E) << endl; exit(-1); \
    } }
#define ASSERTS_RUN g_nAssertions

void test01Constructor()
{
    Bitstream b(1024);
    ASSERT(b.getData() != 0, "data should hold a valid pointer");
    ASSERT(b.getSize() == 1024, "Bitstream's size should be 1024");
}

void test02WriteBit()
{
    Bitstream b(1024);
    ASSERT(b.getData()[0] == 0, "data should be zero-initialized");
    for (int i = 0; i < 8; i++) {
        b.writeBit(1);
    }
    ASSERT(b.getData()[0] == 0xFF, "should have written 8 1s");
}


void test03WriteBit2()
{
    Bitstream b(1024);
    ASSERT(b.getData()[0] == 0, "data should be zero-initialized");
    for (int i = 0; i < 8; i++) {
        b.writeBit(i%2);
    }
    ASSERT(b.getData()[0] == 0xAA, "should have written 0s and 1s");
}

void test04Write()
{
    Bitstream b(1024);
    bs_raw c = 0x0A;
    b.write(&c, 4);
    b.write(&c, 4);
    ASSERT(b.getData()[0] == 0xAA, "should have written 2 0xAs");
}

void test05WriteMultibyte()
{
    Bitstream b(1024);
    bs_raw bs[3] = { 0x5, 0x6, 0x7 };
    bs_raw expct[2] = { 0xBB, 0x80 };
    b.write(&bs[0], 3);
    b.write(&bs[1], 3);
    b.write(&bs[2], 3);
    const bs_raw* data = b.getData();
    bool res = data[0] == 0xF5 && data[1] == 0x01;
    ASSERT(res, "should have written 0xF5 0x01");
}

int main()
{
    test01Constructor();
    test02WriteBit();
    test03WriteBit2();
    test04Write();
    test05WriteMultibyte();
    cout << "GREEN (" << ASSERTS_RUN << " asserts)" << endl;
    return 0;
}

