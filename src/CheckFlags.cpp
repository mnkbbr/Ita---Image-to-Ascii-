#include <string>
#include "utils.h"
bool CheckFlags(int & desired_size, std::string & pallete,  char ** arg){
    if (arg[2][0] != '-')
    {
        HelpMenu();
        return false;
    }
    if (arg[2][1] == 'd')
    {
        desired_size = GetNum(arg[3]);
    }
    else if (arg[2][1] == 'p'){
        pallete = arg[3];
    }

    if (arg[2][2] == 'd')
    {
        desired_size = GetNum(arg[4]);
    }
    else if (arg[2][2] == 'p'){
        pallete = arg[4];
    }
    return true;
    

}