#include <string>
#include <filesystem>
#include <rVal/rVal.hpp>
#include <evaluable/rValConst.hpp>

class Bootstrap{
    public:
    static std::string bootstrapArray();
    static std::shared_ptr<RVal> bridgeFunction(std::shared_ptr<RVal>, std::string, RValPointerArray&);
    static std::shared_ptr<RVal> arrayBridgeFunction(RValPointerArray&, std::string, RValPointerArray&);
};