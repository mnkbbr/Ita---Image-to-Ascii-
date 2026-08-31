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
#include <fstream>

#include "utils.h"




int main(int argc, char ** argv){

    std::string palette = " .:-=+*#%@";
    int palettesize = palette.size() - 1;
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
//                                                          Image writing
//-------------------------------------------------------------------------------------------------------------------------------------------

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
                    data = stbi_load_from_memory(rawdata, filelen, &width, &height, &chanels, 1 );
                }

                delete [] rawdata;

            }
            else{
                std::cerr<<"Error: the file("<<argv[1]<<") is corrupted or cannot be opened.  "<<std::endl;
                std::cerr<<"Check the name and access permissions."<<std::endl;
                return -1;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------
        
    if (!data)
    {
        std::cerr << "Error: Could not open or decode the image '" << argv[1] << "'" << std::endl;
        std::cerr << "Supported formats: JPG, PNG, BMP, TGA, GIF, PSD, HDR" << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return -1;   
    }

    desired_size = (width / 120) < 1 ?  1 : (width / 120);

    if (argc == 3){
        desired_size = GetNum(argv[2]);
    }
   
    int new_width = width / desired_size;
    int new_height = height / (desired_size * 2);

//                                                          Frame drawing
//-------------------------------------------------------------------------------------------------------------------------------------------
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
                std::cout<<palette[(int)((GetMeanValue(data, width, height, i, j, f, desired_size) / 255)*palettesize)];
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
//-------------------------------------------------------------------------------------------------------------------------------------------

    stbi_image_free(data);
        if (is_gif && delays)
        {
            stbi_image_free(delays);
        }
        
        return 0;
}