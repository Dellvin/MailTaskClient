//
// Created by Daniil Tchyorny on 03.09.2020.
//

#ifndef ENTERINGTASK_CLIENT_UI_H
#define ENTERINGTASK_CLIENT_UI_H

#include <iostream>

constexpr uint16_t INBUFSIZE = 1024;
constexpr uint16_t OUTBUFSIZE = 128;

class UI {
public:
    struct buffer{
        char buf[INBUFSIZE];
        int buf_used;
    };

    explicit UI(std::string &&ServerIP, uint32_t ServerPort);

    int start();

private:
    int init();
    void eventLoop();
    static void move(buffer *ptr,int pos);
    static void checkEOM(buffer *ptr);
    int getMessage(buffer *ptr);
    bool sender();
private:
    uint32_t port;
    std::string ip;
    int sock;
};


#endif //ENTERINGTASK_CLIENT_UI_H
