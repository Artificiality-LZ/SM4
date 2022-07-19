#include "SM4.h"
using namespace std;

int main_test()
{
    ifstream in;
    ofstream out;

    string a = "12";
    char b[32];
    char c[2];
    in.open("C:\\Users\\Artificiality-LZ\\PycharmProjects\\想到就用这个\\123.txt");


    unsigned int ou = string_to_int(c);

    unsigned int key[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

    unsigned int plaintext[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

    unsigned int output[16] = { 0 };

    unsigned int rki[32] = { 0 };

    int en = 0;

    for (int i = 0; i < 16; i++)
    {

        in.read(c, 2);

        plaintext[i] = string_to_int(c);


        if (in.eof())
        {
            en = i;
            break;
        }
    }
    for (int i = en; i < 16; i++)
    {
        plaintext[i] = 0;
    }
    for (int i = 0; i < 16; i++)
        cout << hex << plaintext[i] << endl;
    // cout << hex<<ou;

    in.close();
    return 0;
}
int main()
{
    unsigned int key[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

    unsigned int plaintext[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

    unsigned int output[16] = { 0 };

    unsigned int rki[32] = { 0 };

    TC TC1;
    TC1.start();



    key_generate(key, rki);


    SM4_encrypt(rki, plaintext, output);


    TC1.end();

    cout << "时间:" << TC1.timeInterval << endl;
    cout << "加密结果:";
    for (int i = 0; i < 16; i++)
    {
        cout << hex << output[i] << " ";
    }
    return 0;
}