#include <stdio.h>

#include "Akinator.h"


int main()
{
    Akinator akinator (ATTRIB_BASE_FILE_PATH);

    int state = akinator.run();

    return state;
}