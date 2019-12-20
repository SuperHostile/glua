// GLuaExtension.cpp : Define las funciones exportadas de la aplicación DLL.

/*
	This extension provides low-level bindings to Lua.
*/


/*#include <stdio.h>
#include <string.h>
#include <windows.h>*/

// Include lua stuff
/*extern "C" {
	#include "lua535/include/lua.h"
	#include "lua535/include/lualib.h"
	#include "lua535/include/lauxlib.h"
}

#ifdef _WIN32
#pragma comment(lib, "lua535/liblua53.a")
#endif*/

/*extern "C" {
	#include "lua535/include/lua.h"
	#include "lua535/include/lauxlib.h"
	#include "lua535/include/lualib.h"
}*/

#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<cmath>
#include<stdio.h>
#include<windows.h>
#include<iterator> 
#include<map> 
#include <stack> 

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

//#include "CrossStackElement.h"

// LUA EXTENSIONS

#define fn_export extern "C" __declspec (dllexport)

bool initialised = false;
lua_State *L;
char temp_name[50];

fn_export double GLuaInit() {

	//LoadLibraryA("lua535/lua53.dll");

	initialised = true;

	L = luaL_newstate();

	//luaL_openlibs(L);

	return 0;
}

fn_export double GLuaQuit() {
	initialised = false;

	return 0;
}

fn_export bool gl_get_init() {
	return initialised;
}

//extern "C" __declspec (dllexport) double gl_run_trough(char* code, double num) {
fn_export double gl_process_number(char* code, double num) {
	double d1 = 0;

	//return d1;
	int status = luaL_loadstring(L, code);

	if (status) {
		return 0;
	}

	lua_pushnumber(L, num);

	lua_setglobal(L, "x");

	int result = lua_pcall(L, 0, LUA_MULTRET, 0);

	if (!result) {
		return lua_tonumber(L, -1);
	}
	else {
		return 0;
	}
}

// Returns a lua_State pointer
fn_export lua_State* gl_create_state() {
	lua_State *L = luaL_newstate();

	luaL_openlibs(L);

	return L;
}


// INTERFACES TO LUA

fn_export void gl_open_libs() {
	luaL_openlibs(L);
}

// PUSHES TO STACK
fn_export void gl_push_number(double num) {
	lua_pushnumber(L, num);
}

fn_export void gl_push_string(const char* s) {
	lua_pushstring(L, s);
}

fn_export void gl_push_boolean(double bo) {
	lua_pushboolean(L, bo);
}

fn_export double gl_is_number(double index) {
	return lua_isnumber(L, index);
}

fn_export double gl_is_string(double index) {
	return lua_isstring(L, index);
}

fn_export double gl_is_table(double index) {
	return lua_istable(L, index);
}

fn_export double gl_is_function(double index) {
	return lua_isfunction(L, index);
}

fn_export void gl_new_table() {
	lua_newtable(L);
}

fn_export void gl_get_table(double index) {
	lua_gettable(L,index);
};

// POPS FROM STACK
fn_export void gl_pop(double amount) {
	lua_pop(L, amount);
}

fn_export double gl_to_number(double index) {
	return lua_tonumber(L, index);
}

fn_export const char* gl_to_string(double index) {
	return lua_tostring(L, index);
}

fn_export double gl_to_boolean(double index) {
	return lua_toboolean(L, index);
}

fn_export double gl_check_number(double index) {
	return luaL_checknumber(L, index);
}

fn_export const char* gl_check_string(double index) {
	return luaL_checkstring(L, index);
}

// GLOBAL
fn_export void gl_set_global(const char* name) {
	lua_setglobal(L, name);
}

fn_export void gl_get_global(const char* name) {
	lua_getglobal(L, name);
}
// CODE
fn_export short gl_call(const char* code) {
	int status = luaL_loadstring(L, code);
	if (status) { return 0; }
	lua_call(L, 0, 1);
}

fn_export double gl_pcall(double nargs, double nresults) {
	return lua_pcall(L, nargs, nresults, 0);
}

fn_export void gl_do_file(const char* name) {
	luaL_dofile(L, name);
}

fn_export void gl_get_field(double index, const char* k) {
	lua_getfield(L, index, k);
}

fn_export void gl_set_field(double index, const char *k) {
	lua_setfield(L, index, k);
};

// END LOL

/*
	FUNCTIONS THAT ARE ALREADY IMPLEMENTED BUT NOT FORWARDED
		-- DONE: 
		gl_do_file
		gl_get_field
		gl_check_number
		gl_check_string
		gl_new_table
		gl_get_table
		gl_open_libs
		-- NOT DONE

	FUNCTIONS TO BE IMPLEMENTED
	DONE : Let the user decide if to use lua_openlibs
	DONE : lua_new*
		- Mainly for table manipulation.
		- At least have it create tables and setting/getting.
	
*/
