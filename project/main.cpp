#include <iostream>
#include "./UI/ui.h"

int main(int argc, char **argv) {
    int port;
    if (argc!=3){
        std::cerr<<"Wrong amount of arguments"<<std::endl;
        return 1;
    }
    try {
        port=std::atoi(argv[2]);
    }catch (std::exception &ex){
        std::cerr<<ex.what()<<std::endl;
        return 1;
    }
    UI cli(argv[1],port);
    cli.start();
    return 0;
}
