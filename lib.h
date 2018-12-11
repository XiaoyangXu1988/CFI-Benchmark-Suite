#pragma once

#ifdef EXPORTING_DLL
extern "C" __declspec(dllexport) void increment(int &i);
extern "C" __declspec(dllexport) int exp_null;
#else
extern "C" __declspec(dllimport) void increment(int &i);
extern "C" __declspec(dllimport) int exp_null;
#endif