#include <iostream>

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