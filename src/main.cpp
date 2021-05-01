#include <stdio.h>

#include "Akinator.h"


int main()
{
    Akinator akinator ("../res/AttribBase.txt");

    int state = akinator.run();

    return state;
}