#ifndef UTILS
#define UTILS
float GetMeanValue(const unsigned char* data, int width, int height, int i, int j, int f, int desired_size);
int GetNum(const char * str);
void HelpMenu();
bool CheckFlags(int & desired_size, std::string & pallete,  char ** arg);
#endif