cmake_minimum_required(VERSION 3.22)
project(AES_test C ASM_NASM)
set(CMAKE_C_STANDARD 11)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

add_executable(AES_test
        encrypt.asm
        decrypt.asm
        main.c)