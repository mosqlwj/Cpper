#include "python_vm/util/BufferedInputStream.h"

using namespace pvm;

int main(int argc, char* argv[]) {
    BufferedInputStream bis(argv[1]);    
    printf("magic number is 0x %x \n", bis.ReadInt());
    return 0;
}