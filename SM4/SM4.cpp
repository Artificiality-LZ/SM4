
#include "SM4.h"

using namespace std;



unsigned int SBOX[] = {
                0xD6, 0x90, 0xE9, 0xFE, 0xCC, 0xE1, 0x3D, 0xB7, 0x16, 0xB6, 0x14, 0xC2, 0x28, 0xFB, 0x2C, 0x05, 0x2B, 0x67, 0x9A,
                0x76, 0x2A, 0xBE, 0x04, 0xC3, 0xAA, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99, 0x9C, 0x42, 0x50, 0xF4, 0x91, 0xEF,
                0x98, 0x7A, 0x33, 0x54, 0x0B, 0x43, 0xED, 0xCF, 0xAC, 0x62, 0xE4, 0xB3, 0x1C, 0xA9, 0xC9, 0x08, 0xE8, 0x95, 0x80,
                0xDF, 0x94, 0xFA, 0x75, 0x8F, 0x3F, 0xA6, 0x47, 0x07, 0xA7, 0xFC, 0xF3, 0x73, 0x17, 0xBA, 0x83, 0x59, 0x3C, 0x19,
                0xE6, 0x85, 0x4F, 0xA8, 0x68, 0x6B, 0x81, 0xB2, 0x71, 0x64, 0xDA, 0x8B, 0xF8, 0xEB, 0x0F, 0x4B, 0x70, 0x56, 0x9D,
                0x35, 0x1E, 0x24, 0x0E, 0x5E, 0x63, 0x58, 0xD1, 0xA2, 0x25, 0x22, 0x7C, 0x3B, 0x01, 0x21, 0x78, 0x87, 0xD4, 0x00,
                0x46, 0x57, 0x9F, 0xD3, 0x27, 0x52, 0x4C, 0x36, 0x02, 0xE7, 0xA0, 0xC4, 0xC8, 0x9E, 0xEA, 0xBF, 0x8A, 0xD2, 0x40,
                0xC7, 0x38, 0xB5, 0xA3, 0xF7, 0xF2, 0xCE, 0xF9, 0x61, 0x15, 0xA1, 0xE0, 0xAE, 0x5D, 0xA4, 0x9B, 0x34, 0x1A, 0x55,
                0xAD, 0x93, 0x32, 0x30, 0xF5, 0x8C, 0xB1, 0xE3, 0x1D, 0xF6, 0xE2, 0x2E, 0x82, 0x66, 0xCA, 0x60, 0xC0, 0x29, 0x23,
                0xAB, 0x0D, 0x53, 0x4E, 0x6F, 0xD5, 0xDB, 0x37, 0x45, 0xDE, 0xFD, 0x8E, 0x2F, 0x03, 0xFF, 0x6A, 0x72, 0x6D, 0x6C,
                0x5B, 0x51, 0x8D, 0x1B, 0xAF, 0x92, 0xBB, 0xDD, 0xBC, 0x7F, 0x11, 0xD9, 0x5C, 0x41, 0x1F, 0x10, 0x5A, 0xD8, 0x0A,
                0xC1, 0x31, 0x88, 0xA5, 0xCD, 0x7B, 0xBD, 0x2D, 0x74, 0xD0, 0x12, 0xB8, 0xE5, 0xB4, 0xB0, 0x89, 0x69, 0x97, 0x4A,
                0x0C, 0x96, 0x77, 0x7E, 0x65, 0xB9, 0xF1, 0x09, 0xC5, 0x6E, 0xC6, 0x84, 0x18, 0xF0, 0x7D, 0xEC, 0x3A, 0xDC, 0x4D,
                0x20, 0x79, 0xEE, 0x5F, 0x3E, 0xD7, 0xCB, 0x39, 0x48
};


unsigned int FK[] = { 0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc };
unsigned int CK[] = {
        0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
        0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
        0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
        0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
        0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
        0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
        0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
        0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
};



//S盒
void S_change(unsigned int sbox_input, unsigned int& sbox_output)
{
    sbox_output = SBOX[sbox_input];
}



//分割为32bit 四个X 四个K
//实际上是拼接
void split_int256(unsigned int int256[], unsigned int re[])
{
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            re[i] = re[i] << 8;
            re[i] += int256[i * 4 + j];
        }
    }
}

//分割成8bit S盒输入
void split_sbox_input(unsigned int sbox_input, unsigned int re[])
{
    for (int i = 0; i < 4; i++)
    {
        re[3 - i] = sbox_input & 0xff;
        sbox_input = (unsigned int)sbox_input >> 8;
    }
}


//S盒的输出，合并为一个数
void join_sbox_output(unsigned int sbox_output_arr[], unsigned int& sbox_out)
{
    sbox_out = 0;
    for (int i = 0; i < 4; i++)
    {
        sbox_out = sbox_out << 8;
        sbox_out += sbox_output_arr[i];
    }
}

//循环左移函数
void cycle_shift_left(unsigned int target, unsigned int step, unsigned int& re)
{

    unsigned int head = target >> (32 - step);
    re = (target << step) | head;
}



//循环函数
void SM4_cycle(unsigned int x0x1x2x3[], unsigned int key32)
{
    unsigned int xi = x0x1x2x3[0];
    //sbox_input=xi+1⊕xi+2⊕xi+3⊕rki
    unsigned int sbox_input = x0x1x2x3[1] ^ x0x1x2x3[2] ^ x0x1x2x3[3] ^ key32;

    unsigned int sbox_input_arr[4] = { 0 };

    split_sbox_input(sbox_input, sbox_input_arr);

    unsigned int sbox_output_arr[4] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        S_change(sbox_input_arr[i], sbox_output_arr[i]);
    }

    unsigned int sbox_output = 0;
    join_sbox_output(sbox_output_arr, sbox_output);

    unsigned int y2 = 0, y10 = 0, y18 = 0, y24 = 0;

    cycle_shift_left(sbox_output, 2, y2);
    cycle_shift_left(sbox_output, 10, y10);
    cycle_shift_left(sbox_output, 18, y18);
    cycle_shift_left(sbox_output, 24, y24);


    // xi+4=sbox_output⊕y2⊕y10⊕y18⊕y24⊕xi

    unsigned int xi_4 = sbox_output ^ y2 ^ y10 ^ y18 ^ y24 ^ xi;

    x0x1x2x3[0] = x0x1x2x3[1];
    x0x1x2x3[1] = x0x1x2x3[2];
    x0x1x2x3[2] = x0x1x2x3[3];
    x0x1x2x3[3] = xi_4;
}

//密钥生成主循环
void key_cycle(unsigned int k0k1k2k3[], unsigned int re[], unsigned int i)
{
    unsigned int k0 = k0k1k2k3[0];
    unsigned int k1 = k0k1k2k3[1];
    unsigned int k2 = k0k1k2k3[2];
    unsigned int k3 = k0k1k2k3[3];

    unsigned int ki = k0;
    //sbox_input=ki+1⊕ki+2⊕ki+3⊕cki
    unsigned int sbox_input = k1 ^ k2 ^ k3 ^ CK[i];

    unsigned int sbox_input_arr[4] = { 0 };

    split_sbox_input(sbox_input, sbox_input_arr);

    unsigned int sbox_output_arr[4] = { 0 };
    for (int j = 0; j < 4; j++)
    {
        S_change(sbox_input_arr[j], sbox_output_arr[j]);
    }

    unsigned int sbox_output = 0;
    join_sbox_output(sbox_output_arr, sbox_output);


    unsigned int y13 = 0, y23 = 0;

    cycle_shift_left(sbox_output, 13, y13);
    cycle_shift_left(sbox_output, 23, y23);

    //rki=ki+4=sbox_output⊕y13⊕y23⊕ki

    unsigned int ki_4 = sbox_output ^ y13 ^ y23 ^ ki;

    re[i] = ki_4;

    k0k1k2k3[0] = k0k1k2k3[1];
    k0k1k2k3[1] = k0k1k2k3[2];
    k0k1k2k3[2] = k0k1k2k3[3];
    k0k1k2k3[3] = ki_4;


}

//密钥生成
void key_generate(unsigned int key[], unsigned int re[])
{
    unsigned int k0k1k2k3[4] = { 0 };
    split_int256(key, k0k1k2k3);
    k0k1k2k3[0] = k0k1k2k3[0] ^ FK[0];
    k0k1k2k3[1] = k0k1k2k3[1] ^ FK[1];
    k0k1k2k3[2] = k0k1k2k3[2] ^ FK[2];
    k0k1k2k3[3] = k0k1k2k3[3] ^ FK[3];


    for (int i = 0; i < 32; i++)
    {
        key_cycle(k0k1k2k3, re, i);
    }
}

//最终结果合并
void join_output(unsigned int x0x1x2x3[], unsigned int output[])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[15 - 4 * i - j] = x0x1x2x3[i] & 0xff;
            x0x1x2x3[i] = (unsigned int)x0x1x2x3[i] >> 8;
        }
    }
}

//加密函数
void SM4_encrypt(unsigned int rki[], unsigned int plaintext[], unsigned int output[])
{

    //生成密钥
    /*int rki[32] = { 0 };
    key_generate(key, rki);*/

    unsigned int x0x1x2x3[4] = { 0 };
    split_int256(plaintext, x0x1x2x3);

    for (int i = 0; i < 32; i++)
    {
        SM4_cycle(x0x1x2x3, rki[i]);
    }

    join_output(x0x1x2x3, output);
}


void SM4( unsigned int key[], unsigned int plaintext[], unsigned int output[], unsigned int rki[])
{
    key_generate(key, rki);
    SM4_encrypt(rki, plaintext, output);
    cout << "加密结果:";
    for (int i = 0; i < 16; i++)
    {
        cout << hex << output[i] << " ";
    }
}


unsigned int string_to_int(char *a)
{
    istringstream is(a);
    unsigned int re = 0;
    is >> hex >> re;
    return re;
}


