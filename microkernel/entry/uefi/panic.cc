#include <entry/public/panic.hh>
#include <entry/public/logging.hh>

#include <common/string.hh>
#include <efi/global.hh>
#include <arch/x86_64/wrappers.hh>
#include <arch/x86_64/register_dumps.hh>

using namespace sharedarch;

#define LogRegister(dump, reg) \
    LogRegImpl(#reg, dump->reg)

const char* gPanicBanner = \
"               )\\._.,--....,'``.      \n"
" .b--.        /;   _.. \\   _\\  (`._ ,.\n"
"`=,-,-'~~~   `----(,_..'--(,_..'`-.;.'\n"
"-----!PANIC!-----\n";

namespace skyline::entry
{
    void LogRegImpl(const char* name, umax value, umax labelSize = 5)
    {
        char buff[512];
        auto end = string::Append(buff, name);
        end = string::Append(end, ":");

        while (end - buff < labelSize)
            *end++ = ' ';
        *end = '\0';

        end = string::AppendHexadecimal(end, value, sizeof(char) * (sizeof(umax) * 2));


        while (end - buff < labelSize + (16 + 2))
            *end++ = ' ';
        *end = '\0';

        EarlyLog(buff); \
    }

    void PrintStackTrace(sharedarch::StackFrame* stackFrame)
    {
        auto i = 0;

        char buff[512];
        for (auto i = 0; i < 16; i++)
        {
            auto end = string::Append(buff, "  - Func: ");
            end = string::AppendHexadecimal(end, stackFrame->Entries[i].ReturnAddress, 16);
            end = string::Append(end, "\n");
            EarlyLog(buff);

            end = string::Append(buff, "  - Next Frame: ");
            end = string::AppendHexadecimal(end, stackFrame->Entries[i].NextFrame, 16);
            end = string::Append(end, "\n");
            EarlyLog(buff);

            if (stackFrame->Entries[i].NextFrame == 0) break;
        }
    }

    void EarlyPanic(const char* message, debug::PanicDump* dump, const char* function, const char* fileName, int lineNumber)
    {
        EarlyLog(gPanicBanner);
        EarlyLog("Reason: \"");
        EarlyLog(message);
        EarlyLog("\"\n");

        char infoBuffer[512];
        auto end = string::Append(infoBuffer, "Function: \"");
        end = string::Append(end, function);
        end = string::Append(end, "\"\n");
        end = string::Append(end, "Location: ");
        end = string::Append(end, fileName);
        end = string::Append(end, ":");
        end = string::AppendDecimal(end, lineNumber);
        end = string::Append(end, "\n");

        EarlyLog(infoBuffer);
        EarlyLog("Register Dump:\n");

        LogRegister(dump->GP, RAX);
        LogRegister(dump->GP, RBX);
        LogRegister(dump->GP, RCX);
        LogRegister(dump->GP, RDX);
        EarlyLog("\n");

        LogRegister(dump->GP, RSI);
        LogRegister(dump->GP, RDI);
        LogRegister(dump->GP, RBP);
        LogRegister(dump->GP, RSP);
        EarlyLog("\n");

        LogRegister(dump->GP, R8);
        LogRegister(dump->GP, R9);
        LogRegister(dump->GP, R10);
        LogRegister(dump->GP, R11);
        EarlyLog("\n");
        LogRegister(dump->GP, R12);
        LogRegister(dump->GP, R13);
        LogRegister(dump->GP, R14);
        LogRegister(dump->GP, R15);
        EarlyLog("\n");

        EarlyLog("Stack Trace:\n");
        PrintStackTrace(&dump->StackFrame);

        EarlyLog("-----!PANIC!-----\n");
        EarlyLog("Halting...\n");
        x86_64::_hlt();
    }
}
