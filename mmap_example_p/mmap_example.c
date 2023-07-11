#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SUCCESS 0
#define FAILURE -1

int main(int argc, char *argv[])
{
    const char *file_path;
    int file_desc;
    struct stat file_stat={0};
    char *mem_ptr=NULL;
    char *buf="This part of mapped memory is overwritten from this program\n";
    if (argc < 2) {
        printf("please mention file path\n");
        return FAILURE;
    }
    //const char *file_path=argv[1];
    file_path=argv[1];
    /*open file*/
    file_desc = open(file_path, O_RDWR);
    if (file_desc < 0) {
        printf("error in opening file=[%s]\n", file_path);
        return FAILURE;
    }
    if (0 < fstat(file_desc, &file_stat)) {
        printf("fstat failied for [%s]\n", file_path);
        close(file_desc);
        return FAILURE;
    }
    //printf("st_size=[%ld]\n", file_stat.st_size);
    /*do memory map of this file*/
    mem_ptr = mmap(NULL, file_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_desc, 0);
    if (MAP_FAILED == mem_ptr) {
        printf("memory map failed\n");
        close(file_desc);
        return FAILURE;
    }
    /*close the file here*/
    close(file_desc);

    /*read the memory mapped file's content*/
    printf("reading from mapped file:\n");
    write(1, mem_ptr, file_stat.st_size);

    /*Write to the mapped file*/
    memcpy(mem_ptr, buf, strlen(buf));
    printf("over written to the mapped file\n");

    /*read from the mappped file again after writting in above line*/
    printf("reading from mapped file:\n");
    write(1, mem_ptr, file_stat.st_size);

    /*unmap the file*/
    if (0 != munmap(mem_ptr, file_stat.st_size)) {
        printf("munmap failed\n");
        return FAILURE;
    }

    return SUCCESS;
}
