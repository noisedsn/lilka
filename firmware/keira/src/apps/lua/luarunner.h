#pragma once

#include <Arduino.h>
#include <lua.hpp>
#include "app.h"

// Abstract Lua runner app. Sets up Lua VM and provides a method to run Lua code.
// Does not implement the run method.
class AbstractLuaRunnerApp : public App {
public:
    AbstractLuaRunnerApp(const char* name);

protected:
    void luaSetup(const char* dir);
    void luaTeardown();
    int execute();
    lua_State* L;
};

// Lua runner app that runs a file.
class LuaFileRunnerApp : public AbstractLuaRunnerApp {
public:
    LuaFileRunnerApp(String path);

private:
    void run();
    String path;
};

// Lua runner app that runs a string.
class LuaLiveRunnerApp : public AbstractLuaRunnerApp {
public:
    LuaLiveRunnerApp();

private:
    void run();
    void execSource(String source);
};

class LuaReplApp : public AbstractLuaRunnerApp {
public:
    LuaReplApp();

private:
    void run();
};
