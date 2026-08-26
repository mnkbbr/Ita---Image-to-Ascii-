#define STBI_MAX_DIMENSIONS 1<<30

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#define USEPALLETE

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "stb_image.h"
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>


int GetNum(char * str){
    int finalvalue = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            finalvalue = (finalvalue * 10) + (str[i] - '0');
        }
    }
    return finalvalue;
}

float GetMeanValue(const unsigned char* data, int width, int height, int i, int j, int f, int desired_size) {
    int totalvalue = 0;
    int desired_size_y = desired_size * 2;
    int frame = f * (width * height);

    int start_x =  i * desired_size;
    int start_y =  j * desired_size_y;

    for (int y = 0; y < desired_size_y; y++) {
        for (int x = 0; x < desired_size; x++) {

            int pixel_x = start_x + x;
            int pixel_y = start_y + y;

            if (pixel_x >= width || pixel_y >= height) continue;

            int pixel_index = frame + (pixel_y * width + pixel_x);

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
    unsigned char * data = nullptr;
    int desired_size;

    bool is_gif = false;

    int number_of_frames = 1;
    int * delays = nullptr;


    if (argc<2 || argc>3){
        HelpMenu();
        return 0;
    }

            std::ifstream file(argv[1], std::ios::binary);
            if (file.is_open()){

                int filelen;
                file.seekg(0, std::ios::end);
                filelen = file.tellg();
                file.seekg(0, std::ios::beg);
                
                unsigned char * rawdata = new unsigned char [filelen];

                file.read((char*)rawdata, filelen);
                file.close();

                if (filelen > 6 && rawdata[0] =='G' && rawdata[1] == 'I' && rawdata[2] == 'F')
                {
                    data = stbi_load_gif_from_memory(rawdata, filelen, &delays, &width, &height, &number_of_frames, &chanels, 1);
                    is_gif = true;
                }
                else {
                    data = stbi_load( argv[1], &width, &height, &chanels, 1 );
                }

                desired_size = 6;
                delete [] rawdata;

            }
            else{
                std::cerr<<"Error: Could not open or decode the image "<<argv[1]<<std::endl;
                return -1;
            }

    if (argc == 3){
        desired_size = GetNum(argv[2]);
    }
        
    if (!data)
    {
        std::cerr << "Error: Could not open or decode the image '" << argv[1] << "'" << std::endl;
        std::cerr << "Supported formats: JPG, PNG, BMP, TGA, GIF, PSD, HDR" << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return -1;   
    }
   
    int new_width = width / desired_size;
    int new_height = height / (desired_size * 2);

for (size_t f = 0; f < number_of_frames; f++)
{
    if (is_gif)
    {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }

       for (size_t j = 0; j < new_height; j++){
        for (size_t i = 0; i < new_width; i++){

            #ifdef USEPALLETE
            std::cout<<palette[(int)((GetMeanValue(data, width, height, i, j, f, desired_size) / 255)*9)];
            #else
            if (GetMeanValue(data, width, height, i, j, f, desired_size) <= 128){
                std::cout<<"@";
            }
            else std::cout<<" ";
            #endif
    }
    std::cout<<std::endl;
}

if (is_gif)
{
    #ifdef _WIN32
        Sleep(delays[f]);
    #else
        usleep(delays[f]*1000);
    #endif
}
}
    stbi_image_free(data);

    if (is_gif && delays)
    {
        stbi_image_free(delays);

    }
    
    return 0;
}