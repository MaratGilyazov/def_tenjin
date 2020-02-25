#define EXTENSION_NAME Tenjin
#define LIB_NAME "Tenjin"
#define MODULE_NAME "tenjin"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>


#if defined(DM_PLATFORM_IOS)
#include "tenjin.h"

static int init(lua_State* L) {
    const char* api_key = luaL_checkstring(L, 1);
    bool gdpr_consent = lua_toboolean(L, 2);
    
    Tenjin_Init(api_key, gdpr_consent);
    return 0;
}

static int custom_event(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);
    const char* event_name = luaL_checkstring(L, 1);
    Tenjin_CustomEvent(event_name);
    return 0;
}

static int custom_event_with_value(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);
    const char* event_name = luaL_checkstring(L, 1);
    const char* event_value = luaL_checkstring(L, 2);
    Tenjin_CustomEventWithValue(event_name, event_value);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"init", init},
    {"custom_event", custom_event},
    {"custom_event_with_value", custom_event_with_value},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeTenjin(dmExtension::AppParams* params)
{
    dmLogWarning("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeTenjin(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeTenjin(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeTenjin(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

dmExtension::Result AppInitializeTenjin(dmExtension::AppParams* params)
{
    dmLogWarning("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeTenjin(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeTenjin(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeTenjin(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeTenjin, AppFinalizeTenjin, InitializeTenjin, 0, 0, FinalizeTenjin)
