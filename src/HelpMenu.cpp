#include <iostream>

void HelpMenu(){
    std::cout<<"Usage:"<<std::endl;
    #ifdef _WIN32
    std::cout<<"Ita.exe <image_path> <flags>"<<std::endl;
    #else
    std::cout<<"./Ita <image_path> <flags>"<<std::endl;
    #endif
    std::cout<<"\nFlags:"<<std::endl;
    std::cout<<"-d <scale_factor>"<<std::endl;
    std::cout<<"-p \".:@\" - pallete for ascii art"<<std::endl;
    std::cout<<"Example: ./Ita image.jpg -dp 2 \"_-L\""<<std::endl<<std::endl;

    std::cout << "Arguments:" << std::endl;
    std::cout << "  <image_path>    Path to the image file (e.g., Picture.png)" << std::endl;
    std::cout << "  <scale_factor>  Image downscaling factor for correct console output" << std::endl;
    std::cout << "                  (e.g., 6 means the image will be 6 times smaller)" << std::endl;

}