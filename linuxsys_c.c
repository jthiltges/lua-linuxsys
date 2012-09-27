#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <sys/mount.h>

#include "lua.h"
#include "lauxlib.h"

#define LUA_ADDCONST(L, name) \
	lua_pushnumber(L, name); \
	lua_setfield(L, -2, #name);

static int linuxsys_chroot(lua_State *L)
{
	lua_pushnumber(L, chroot(
		luaL_checkstring(L, 1)      /* path */
	));
	return 1; /* number of results */
}

static int linuxsys_mount(lua_State *L)
{
	lua_pushnumber(L, mount(
		luaL_optstring(L, 1, NULL), /* source */
		luaL_checkstring(L, 2),     /* target */
		luaL_optstring(L, 3, NULL), /* type */
		luaL_optlong(L, 4, 0),      /* flags */
		luaL_optstring(L, 5, NULL)  /* data */
	));
	return 1; /* number of results */
}

static int linuxsys_umount(lua_State *L)
{
	lua_pushnumber(L, umount2(
		luaL_checkstring(L, 1),     /* target */
		luaL_optlong(L, 2, 0)       /* flags */
	));
	return 1; /* number of results */
}

static int linuxsys_unshare(lua_State *L)
{
	lua_pushnumber(L, unshare(
		luaL_checkinteger(L, 1) /* flags */
	));
	return 1; /* number of results */
}

static const struct luaL_Reg linuxsys_lib [] = {
	{ "chroot",  linuxsys_chroot },
	{ "mount",   linuxsys_mount },
	{ "umount",  linuxsys_umount },
	{ "unshare", linuxsys_unshare },
	{ NULL, NULL }  /* sentinel */
};

/*
 * Open library
 */
int luaopen_linuxsys_c (lua_State *L)
{
	/* Register functions in library */
	luaL_register(L, "linuxsys", linuxsys_lib);

	/* Register constants in library */
	/* unshare(2) constants from sched.h */
	LUA_ADDCONST(L, CLONE_VM);
	LUA_ADDCONST(L, CLONE_FS);
	LUA_ADDCONST(L, CLONE_FILES);
	LUA_ADDCONST(L, CLONE_SIGHAND);
	LUA_ADDCONST(L, CLONE_PTRACE);
	LUA_ADDCONST(L, CLONE_VFORK);
	LUA_ADDCONST(L, CLONE_PARENT);
	LUA_ADDCONST(L, CLONE_THREAD);
	LUA_ADDCONST(L, CLONE_NEWNS);
	LUA_ADDCONST(L, CLONE_SYSVSEM);
	LUA_ADDCONST(L, CLONE_SETTLS);
	LUA_ADDCONST(L, CLONE_PARENT_SETTID);
	LUA_ADDCONST(L, CLONE_CHILD_CLEARTID);
	LUA_ADDCONST(L, CLONE_DETACHED);
	LUA_ADDCONST(L, CLONE_UNTRACED);
	LUA_ADDCONST(L, CLONE_CHILD_SETTID);
	LUA_ADDCONST(L, CLONE_NEWUTS);
	LUA_ADDCONST(L, CLONE_NEWIPC);
	LUA_ADDCONST(L, CLONE_NEWUSER);
	LUA_ADDCONST(L, CLONE_NEWPID);
	LUA_ADDCONST(L, CLONE_NEWNET);
	LUA_ADDCONST(L, CLONE_IO);
	/* mount(2) constants from sys/mount.h */
	LUA_ADDCONST(L, MS_RDONLY);
	LUA_ADDCONST(L, MS_NOSUID);
	LUA_ADDCONST(L, MS_NODEV);
	LUA_ADDCONST(L, MS_NOEXEC);
	LUA_ADDCONST(L, MS_SYNCHRONOUS);
	LUA_ADDCONST(L, MS_REMOUNT);
	LUA_ADDCONST(L, MS_MANDLOCK);
	LUA_ADDCONST(L, MS_DIRSYNC);
	LUA_ADDCONST(L, MS_NOATIME);
	LUA_ADDCONST(L, MS_NODIRATIME);
	LUA_ADDCONST(L, MS_BIND);
	LUA_ADDCONST(L, MS_MOVE);
	LUA_ADDCONST(L, MS_REC);
	LUA_ADDCONST(L, MS_SILENT);
	LUA_ADDCONST(L, MS_POSIXACL);
	LUA_ADDCONST(L, MS_UNBINDABLE);
	LUA_ADDCONST(L, MS_PRIVATE);
	LUA_ADDCONST(L, MS_SLAVE);
	LUA_ADDCONST(L, MS_SHARED);
	LUA_ADDCONST(L, MS_RELATIME);
	LUA_ADDCONST(L, MS_KERNMOUNT);
	LUA_ADDCONST(L, MS_I_VERSION);
	LUA_ADDCONST(L, MS_STRICTATIME);
	LUA_ADDCONST(L, MS_ACTIVE);
	LUA_ADDCONST(L, MS_NOUSER);
	/* umount(2) constants from sys/mount.h */
	LUA_ADDCONST(L, MNT_FORCE);
	LUA_ADDCONST(L, MNT_DETACH);
	LUA_ADDCONST(L, MNT_EXPIRE);
	LUA_ADDCONST(L, UMOUNT_NOFOLLOW);

	return 1;
}
