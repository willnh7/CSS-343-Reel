#include <iostream> 
#include <string>
#include <cstdint>

// namespaces for the flags used
namespace BreakUps {
    const std::uint32_t ITS_NOT_YOU_ITS_ME = 1;
    const std::uint32_t I_NEED_TO_FOCUS_ON_MYSELF = 1 << 1;
    const std::uint32_t THIS_IS_BETTER_FOR_EVERYONE = 1 << 2;
    const std::uint32_t I_DONT_DESERVE_YOU_NEVER_HAVE = 1 << 3;
    const std::uint32_t ESCORT_OUT_IMMEDIATE = 1 << 4;
    const std::uint32_t ZAP_WITH_LAZER = 1 << 5;
}
// Called before the rest so I don't have to type the BreakUps:: everytime
using namespace BreakUps;
// The terminate, using bitwise, on and off switch. 
void terminate (const std::string& name, const std::uint32_t flags) {
    std::cout << "Sorry " << name << ". ";
    if(flags & ITS_NOT_YOU_ITS_ME) {
        std::cout << "It's not you it's me. ";
    }
    if(flags & I_NEED_TO_FOCUS_ON_MYSELF) {
        std::cout << "I need to focus on myself. ";
    }
    if(flags & THIS_IS_BETTER_FOR_EVERYONE) {
        std::cout << "This is better for everyone. ";
    }
    if(flags & I_DONT_DESERVE_YOU_NEVER_HAVE) {
        std::cout << "I don't deserve you, never have. ";
    }
    if(flags & ESCORT_OUT_IMMEDIATE) {
        std::cout << "ESCORT OUT IMMEDIATELY! ";
    }
    if(flags & ZAP_WITH_LAZER) {
        std::cout << "ZAP WITH LAZAR!!!";
    }
    std::cout << "\n";
}
int main() {
    terminate("Billy", 
        ITS_NOT_YOU_ITS_ME 
        | THIS_IS_BETTER_FOR_EVERYONE);
    terminate("Obama", 
        ITS_NOT_YOU_ITS_ME 
        | THIS_IS_BETTER_FOR_EVERYONE 
        | I_NEED_TO_FOCUS_ON_MYSELF);
    terminate("Soccer moms", 
        I_DONT_DESERVE_YOU_NEVER_HAVE 
        | THIS_IS_BETTER_FOR_EVERYONE 
        | ESCORT_OUT_IMMEDIATE 
        | ZAP_WITH_LAZER);
    terminate("Stranger", 
        I_DONT_DESERVE_YOU_NEVER_HAVE 
        | THIS_IS_BETTER_FOR_EVERYONE 
        | ESCORT_OUT_IMMEDIATE 
        | ZAP_WITH_LAZER);
}