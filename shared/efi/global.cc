#include <efi/global.hh>

namespace efi
{
    SystemTable* gSystemTable           = nullptr;
    BootServices* gBootServices         = nullptr;
    RuntimeServices* gRuntimeServices   = nullptr;
    SimpleTextOutputProtocol* gStdOut   = nullptr;
    SimpleTextOutputProtocol* gStdErr   = nullptr;
    handle gImageHandle                 = nullptr;
}
