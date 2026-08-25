#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#define STBI_NO_GIF
#define USEPALLETE

// #define DEBUG

#include "stb_image.h"
#include <iostream>
#include <string>
#include <cctype>

int GetNum(char * str){
    int finalvalue = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            finalvalue = (finalvalue * 10) + (str[i] - '0');
        }
    }
    return finalvalue;
}

float GetMeanValue(const unsigned char* data, int width, int i, int j, int desired_size) {
    int totalvalue = 0;
    
    int start_x = i * desired_size;
    int start_y = j * (desired_size * 2);

    int desired_size_y = desired_size * 2;

    for (int y = 0; y < desired_size_y; y++) {
        for (int x = 0; x < desired_size; x++) {

            int pixel_x = start_x + x;
            int pixel_y = start_y + y;

            int pixel_index = pixel_y * width + pixel_x;

            totalvalue += (int)data[pixel_index];
        }
    }

    int pixels_count = desired_size * desired_size_y;
    return (float)totalvalue / pixels_count;
}

void HelpMenu(){
    std::cout<<"Usage:"<<std::endl;
    #ifdef _WIN32
    std::cout<<"Ita.exe <image_path> <scale_factor>"<<std::endl;
    #else
    std::cout<<"./Ita <image_path> <scale_factor>"<<std::endl;
    #endif
    std::cout << "Arguments:" << std::endl;
    std::cout << "  <image_path>    Path to the image file (e.g., Picture.png)" << std::endl;
    std::cout << "  <scale_factor>  Image downscaling factor for correct console output" << std::endl;
    std::cout << "                  (e.g., 6 means the image will be 6 times smaller)" << std::endl;
    std::cout << "                  Recommended scale:" << std::endl;
    std::cout << "                    - 6-10 : for small console windows" << std::endl;
    std::cout << "                    - 3-5  : for large images / fullscreen" << std::endl;
}
int main(int argc, char ** argv){

    std::string palette = " .:-=+*#%@";
    int width, height, chanels;
    unsigned char * data;
    int desired_size;

    switch (argc)
    {
    case 2:
        data = stbi_load( argv[1], &width, &height, &chanels, 1 );
        desired_size = 6;
        break;

    case 3:
        data = stbi_load( argv[1], &width, &height, &chanels, 1 );
        desired_size = GetNum(argv[2]);
        break;

    default:
        HelpMenu();
        return 0;
    }
    if (!data)
    {
        std::cerr << "Error: Could not open or decode the image '" << argv[1] << "'" << std::endl;
        std::cerr << "Supported formats: JPG, PNG, BMP, TGA, GIF, PSD, HDR" << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return -1;   
    }
   
    system("cls");
    int new_width = width / desired_size;
    int new_height = height / (desired_size * 2);

for (size_t j = 0; j < new_height; j++)
{
    for (size_t i = 0; i < new_width; i++)
    {
        #ifdef USEPALLETE
        std::cout<<palette[(int)((GetMeanValue(data, width, i, j, desired_size) / 255)*9)];
        #else
        if(GetMeanValue(data, width, i, j, desired_size) <= 128){
            std::cout<<"@";
        }
        else std::cout<<" ";
        #endif
    }
    std::cout<<std::endl;
}

    stbi_image_free(data);
    return 0;

}