add_library(evaluable STATIC 
unaryOperation.cpp 
binaryOperation.cpp 
rValConst.cpp 
rValConstFactory.cpp 
arrayAst.cpp 
mapAst.cpp 
conditionalOperation.cpp 
variable.cpp 
indexing.cpp 
function.cpp 
functionCall.cpp 
classDecleration.cpp
new.cpp
instance.cpp
dotOperator.cpp
bridgeFnExpr.cpp)
target_include_directories(evaluable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)