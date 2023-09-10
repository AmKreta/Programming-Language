#pragma once

#include<rVal/rVal.hpp>
#include<evaluable/rValConst.hpp>

class Console{
    private:
        static void logNumberConst(std::shared_ptr<NumberConst>);

        static void logStringConst(std::shared_ptr<StringConst>);

        static void logArrayConst(std::shared_ptr<ArrayConst>);

        static void logMapConst(std::shared_ptr<MapConst>);

        static void logBoolean(std::shared_ptr<BooleanConst>);

        static void logNull();
        
        static void logUndefined();

        static void logFunction(std::shared_ptr<FunctionConst>);
        
    public:
        static void log(std::shared_ptr<RVal>);
};