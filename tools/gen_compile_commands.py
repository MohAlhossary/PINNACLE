#!/usr/bin/env python3
"""Regenerate compile_commands.json for CLion (or any compdb-based IDE).

Run this after adding/removing source files or upgrading the PROS toolchain:
    python tools/gen_compile_commands.py

It mirrors the compiler invocation that common.mk builds (same defines, same
-mcpu/-mfpu/-mfloat-abi, same include dirs, same standard) and names the real
arm-none-eabi-gcc/g++ as the driver. CLion's Compilation Database loader needs
to actually invoke whatever compiler is named in each entry to probe its
builtin macros/dialect, so a driver name (e.g. bare "clang++") that isn't
resolvable on this machine makes CLion fail to load the project entirely.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOLCHAIN_BIN = os.environ.get(
    "PROS_TOOLCHAIN_BIN", r"C:/Users/moham/PROS_TOOLCHAIN/usr/bin"
)
GCC = os.path.join(TOOLCHAIN_BIN, "arm-none-eabi-gcc.exe")
GXX = os.path.join(TOOLCHAIN_BIN, "arm-none-eabi-g++.exe")

SRCDIR = os.path.join(ROOT, "src")
INCDIR = "include"
CEXTS = ["c"]
CXXEXTS = ["cpp", "c++", "cc"]

MFLAGS = ["-mcpu=cortex-a9", "-mfpu=neon-fp16", "-mfloat-abi=hard", "-Os", "-g", "-mthumb"]
GCCFLAGS = ["-ffunction-sections", "-fdata-sections", "-fdiagnostics-color", "-funwind-tables"]
WARNFLAGS = ["-Wno-psabi"]
BASE_DEFINES = [
    "-D_POSIX_THREADS",
    "-D_UNIX98_THREAD_MUTEX_ATTRIBUTES",
    "-D_POSIX_TIMERS",
    "-D_POSIX_MONOTONIC_CLOCK",
]


def read_standard(varname, default):
    common_mk = os.path.join(ROOT, "common.mk")
    with open(common_mk, "r") as f:
        text = f.read()
    m = re.search(rf"^{varname}\?=(\S+)", text, re.MULTILINE)
    return m.group(1) if m else default


C_STANDARD = read_standard("C_STANDARD", "gnu23")
CXX_STANDARD = read_standard("CXX_STANDARD", "gnu++26")


def lvgl_defines():
    defines = []
    if os.path.exists(os.path.join(ROOT, INCDIR, "liblvgl", "llemu.h")):
        defines.append("-D_PROS_INCLUDE_LIBLVGL_LLEMU_H")
    if os.path.exists(os.path.join(ROOT, INCDIR, "liblvgl", "llemu.hpp")):
        defines.append("-D_PROS_INCLUDE_LIBLVGL_LLEMU_HPP")
    return defines


def find_sources(exts):
    found = []
    for dirpath, _, filenames in os.walk(SRCDIR):
        for name in filenames:
            ext = name.rsplit(".", 1)[-1] if "." in name else ""
            if ext in exts:
                full = os.path.join(dirpath, name)
                found.append(os.path.relpath(full, ROOT).replace(os.sep, "/"))
    return sorted(found)


def make_entry(src_rel, driver, standard, defines):
    subdir = os.path.dirname(os.path.relpath(src_rel, "src"))
    subdir = "" if subdir in (".", "") else subdir + "/"
    obj = "bin/" + src_rel[len("src/"):] + ".o"
    args = [driver, "-c"]
    args += [f"-iquote./{INCDIR}", f"-iquote./{INCDIR}/{subdir}."]
    args += MFLAGS + defines + WARNFLAGS + GCCFLAGS
    args += [f"--std={standard}"]
    args += ["-o", obj, src_rel]
    return {"arguments": args, "directory": ROOT.replace("/", "\\"), "file": src_rel}


def main():
    if not (os.path.exists(GCC) and os.path.exists(GXX)):
        print(f"error: toolchain not found at {TOOLCHAIN_BIN}", file=sys.stderr)
        sys.exit(1)

    defines = BASE_DEFINES + lvgl_defines()

    entries = []
    for src in find_sources(CXXEXTS):
        entries.append(make_entry(src, GXX, CXX_STANDARD, defines))
    for src in find_sources(CEXTS):
        entries.append(make_entry(src, GCC, C_STANDARD, defines))

    out_path = os.path.join(ROOT, "compile_commands.json")
    with open(out_path, "w") as f:
        json.dump(entries, f, indent=4)
        f.write("\n")
    print(f"wrote {len(entries)} entries to {out_path}")


if __name__ == "__main__":
    main()
