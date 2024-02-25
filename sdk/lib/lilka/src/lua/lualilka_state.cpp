#include "lualilka_state.h"

namespace lilka {

int lualilka_state_load(lua_State* L, const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        return 1;
    }

    int count = 0;

    // Create state table
    lua_newtable(L);
    // Read state table
    char key[256];
    while (fscanf(file, "%s", key) != EOF) {
        if (strcmp(key, "number") == 0) {
            // Read number
            double value;
            fscanf(file, "%lf", &value);
            serial_log("lua: state: load number %s = %lf", key, value);
            lua_pushnumber(L, value);
            count++;
        } else if (strcmp(key, "string") == 0) {
            // Read string
            char value[256];
            fscanf(file, "%s", value);
            String valueStr = value;
            valueStr.replace("\\n", "\n");
            valueStr.replace("\\r", "\r");
            serial_log("lua: state: load string %s = %s", key, valueStr.c_str());
            lua_pushstring(L, valueStr.c_str());
            count++;
        } else if (strcmp(key, "boolean") == 0) {
            // Read boolean
            int value;
            fscanf(file, "%d", &value);
            serial_log("lua: state: load boolean %s = %d", key, value);
            lua_pushboolean(L, value);
            count++;
        } else if (strcmp(key, "nil") == 0) {
            // Read nil
            serial_log("lua: state: load nil %s", key);
            lua_pushnil(L);
            count++;
        } else {
            // Skip unsupported types
        }
        // Read next key
        fscanf(file, "%s", key);
        // Set value in state table
        lua_setfield(L, -2, key);
    }

    serial_log("lua: state: loaded %d values", count);

    // Set state table to global
    lua_setglobal(L, "state");

    fclose(file);
    return 0;
}

int lualilka_state_save(lua_State* L, const char* path) {
    FILE* file = fopen(path, "w");
    if (!file) {
        return 1;
    }

    int count = 0;

    // Get state global
    lua_getglobal(L, "state");
    // Iterate over state table
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        // Get key
        const char* key = lua_tostring(L, -2);
        fprintf(file, "%s\n", key);
        // Get value type
        int type = lua_type(L, -1);
        if (type == LUA_TNUMBER) {
            // Write number
            double value = lua_tonumber(L, -1);
            serial_log("lua: state: save number %s = %lf", key, value);
            fprintf(file, "number\n%lf\n", value);
            count++;
        } else if (type == LUA_TSTRING) {
            // Write string
            const char* value = lua_tostring(L, -1);
            String valueStr = value;
            valueStr.replace("\n", "\\n");
            valueStr.replace("\r", "\\r");
            serial_log("lua: state: save string %s = %s", key, valueStr.c_str());
            fprintf(file, "string\n%s\n", value);
            count++;
        } else if (type == LUA_TBOOLEAN) {
            // Write boolean
            int value = lua_toboolean(L, -1);
            serial_log("lua: state: save boolean %s = %d", key, value);
            fprintf(file, "boolean\n%d\n", value);
            count++;
        } else if (type == LUA_TNIL) {
            // Write nil
            serial_log("lua: state: save nil %s", key);
            fprintf(file, "nil\n");
            count++;
        } else {
            // Skip unsupported types
        }
        // Remove value from stack
        lua_pop(L, 1);
    }

    serial_log("lua: state: saved %d values", count);

    fclose(file);
    return 0;
}

} // namespace lilka
