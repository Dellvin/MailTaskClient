//
// Created by Daniil Tchyorny on 03.09.2020.
//

#include "ui.h"

#include <utility>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

UI::UI(std::string &&ServerIP, uint32_t ServerPort) : ip(std::move(ServerIP)), port(ServerPort) {}

int UI::start() {
    uint8_t errorCode=init();
    if(errorCode)return errorCode;
    eventLoop();
}

int UI::init() {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (!inet_aton(ip.c_str(), &(addr.sin_addr))) {
        std::cerr << "Invalid Ip address" << std::endl;
        return (1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket error" << std::endl;
        return (2);
    }
    if (connect(sock, (sockaddr *) &addr, sizeof(addr))) {
        std::cerr << "Connection error" << std::endl;
        return (3);
    }
    std::cout << "You successfully connected to server!" << std::endl;
}

void UI::eventLoop() {
    int res;
    buffer msg;
    fd_set readfds;
    msg.buf_used = 0;//this func exist only for non blocking read
    for (;;) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(sock, &readfds);
        res = select(sock + 1, &readfds, nullptr, nullptr, nullptr);
        if (res < 1) {
            if (errno != EINTR) {
                perror("select");
                exit(1);
            }
            continue;
        }
        if (FD_ISSET(0, &readfds)) {
            if (!sender()) {
                break;
            }
        }
        if (FD_ISSET(sock, &readfds)) {
            if (!getMessage(&msg)) {
                break;
            }
        }
    }
}

void UI::move(buffer *ptr, int pos) {
    int i, j = 0;
    for (i = pos + 1; i < ptr->buf_used; i++) {
        ptr->buf[j] = ptr->buf[i];
        j++;
    }
    ptr->buf_used -= (pos + 1);
}

void UI::checkEOM(buffer *ptr) {
    int pos, i;
    for (;;) {
        pos = -1;
        for (i = 0; i < ptr->buf_used; i++) {
            if (ptr->buf[i] == '\n') {
                pos = i;
                break;
            }
        }
        if (pos == -1)
            return;
        write(1, ptr->buf, pos + 1);
        move(ptr, pos);
    }
}

int UI::getMessage(buffer *ptr) {
    int busy, rc;
    busy = ptr->buf_used;
    rc = read(sock, ptr->buf + busy, INBUFSIZE - busy);
    if (rc <= 0)
        return 0;
    ptr->buf_used += rc;
    checkEOM(ptr);
    if (ptr->buf_used >= INBUFSIZE) {
        ptr->buf_used = 0;
        std::cerr<<"Buffer overflow"<<std::endl;
    }
    return 1;
}

bool UI::sender() {
    int rc;
    char buf[OUTBUFSIZE];
    rc = read(0, buf, OUTBUFSIZE);
    if (rc <= 0)
        return false;
    write(sock, buf, rc);
    return true;
}