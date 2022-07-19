#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
#include<Windows.h>

typedef class TimeCounter
{
public:
    TimeCounter(void)
    {
        QueryPerformanceFrequency(&CPUClock);
    }

private:
    LARGE_INTEGER startTime;

    LARGE_INTEGER endTime;

    LARGE_INTEGER CPUClock;

public:
    double timeInterval;

public:
    void start()
    {
        QueryPerformanceCounter(&startTime);
    }
    void end()
    {
        QueryPerformanceCounter(&endTime);

        timeInterval = ((double)endTime.QuadPart - (double)startTime.QuadPart) / (double)CPUClock.QuadPart;
    }
}TC;




void S_change(unsigned int sbox_input, unsigned int& sbox_output);
void split_int256(unsigned int int256[], unsigned int re[]);
void split_sbox_input(unsigned int sbox_input, unsigned int re[]);
void join_sbox_output(unsigned int sbox_output_arr[], unsigned int& sbox_out);
void cycle_shift_left(unsigned int target, unsigned int step, unsigned int& re);
void SM4_cycle(unsigned int x0x1x2x3[], unsigned int key32);
void key_cycle(unsigned int k0k1k2k3[], unsigned int re[], unsigned int i);
void key_generate(unsigned int key[], unsigned int re[]);
void join_output(unsigned int x0x1x2x3[], unsigned int output[]);
void SM4_encrypt(unsigned int rki[], unsigned int plaintext[], unsigned int output[]);
unsigned int string_to_int(char* a);
