#pragma once
#include "JohnsArray.h"

struct FuncAndInstance;
typedef void (CallBackFunction)(void* userData);

class InputManager
{
    JohnsArray<FuncAndInstance> OnMouseClicked;
    
public:
    InputManager();
    void Update();
    int Horizontal;
    int Vertical;
    bool Quit;

    void AddFunctionPointerToMouseButtonClicked(CallBackFunction* func, void* userData);
};

struct FuncAndInstance
{
    CallBackFunction* func;
    void* userData;
    FuncAndInstance(CallBackFunction * function, void* data)
    {
        func = function;
        userData = data;
    }
};
