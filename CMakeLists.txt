cmake_minimum_required(VERSION 3.22)
project(AES_mini C)

set(CMAKE_C_STANDARD 11)


set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
enable_language(ASM_NASM)
# Create a compile option that operates on ASM_NASM files
# If the target has a property NASM_OBJ_FORMAT, use it, otherwise
# use the environment variable CMAKE_ASM_NASM_OBJECT_FORMAT
add_compile_options(
        "$<$<COMPILE_LANGUAGE:ASM_NASM>:-f $<IF:$<BOOL:$<TARGET_PROPERTY:NASM_OBJ_FORMAT>>, \
    $<TARGET_PROPERTY:NASM_OBJ_FORMAT>, ${CMAKE_ASM_NASM_OBJECT_FORMAT}>>"
)

add_executable(AES_mini
        main.c
        encrypt.s
        decrypt.s)

set_target_properties(AES_mini PROPERTIES NASM_OBJ_FORMAT elf64)