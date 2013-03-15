#include <iostream>
#include <cstdio>
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

int main()
{
    test01Constructor();
    test02WriteBit();
    test03WriteBit2();
    test04Write();
    cout << "GREEN (" << ASSERTS_RUN << " asserts)" << endl;
    return 0;
}

