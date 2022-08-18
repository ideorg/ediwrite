//
// Created by Andrzej Borucki on 2022-08-17
//

#ifndef EDITWRITE_WIN_H
#define EDITWRITE_WIN_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>

class Win {
    Display *display;
    Window root;
    Window w;
    bool tryGetCurrentWorkspace(const char *prop_name, uint& result);
    void xclientSend(const char *msg, long data);
public:
    explicit Win(Window w);
    ~Win();
    uint getCurrentWorkspace();
    void fetch();
    void activate();
};

#endif //EDITWRITE_WIN_H
