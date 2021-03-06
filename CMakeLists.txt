#Based on a template provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
project(yagi)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(Pluma-1.1)
get_filename_component(PLUMA_INCLUDE_DIR "Pluma-1.1/include" ABSOLUTE)
include_directories(${PLUMA_INCLUDE_DIR})

find_package(ANTLR REQUIRED)

include_directories("src")
include_directories(${ANTLR_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/tclap-1.2.1/include)
include_directories($ENV{ASRAEL_INCLUDE})

set(CMAKE_BUILD_TYPE Debug)
set(CPP11_EXTRA_FLAGS "")

#Auto-generated code induces compile warnings, which we disable here for these files.
set_source_files_properties(src/front-end/autoGenerated/YAGILexer.h PROPERTIES COMPILE_FLAGS -Wno-tautological-compare)
set_source_files_properties(src/front-end/autoGenerated/YAGILexer.h PROPERTIES COMPILE_FLAGS -Wno-parentheses-equality)
set_source_files_properties(src/front-end/autoGenerated/YAGIParser.c PROPERTIES COMPILE_FLAGS -Wno-unused-function)
set_source_files_properties(src/front-end/autoGenerated/YAGITreeWalker.c PROPERTIES COMPILE_FLAGS -Wno-unused-function)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -pthread  ${CPP11_EXTRA_FLAGS} ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-pthread ${CMAKE_EXE_LINKER_FLAGS} ${CPP11_EXTRA_FLAGS}")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(Sqlite REQUIRED)
include_directories( ${SQLITE_INCLUDE_DIR} )


add_library(yagiSignalInterface SHARED src/back-end/Signals/IYAGISignalHandler.cpp)
install(TARGETS yagiSignalInterface DESTINATION lib)

add_library(yagiExogenousEventInterface SHARED src/back-end/ExogenousEvents/IExogenousEventProducer.cpp)
install(TARGETS yagiExogenousEventInterface DESTINATION lib)

# ======================================================================
# begin Plugin section
# ======================================================================
# Cin/Cout plugin
add_library(CinCoutBackend SHARED
 src/back-end/Backends/CinCout/Connector.cpp
 src/back-end/Backends/CinCout/CinCoutBackend.cpp
 src/back-end/Backends/CinCout/CoutCinSignalHandler.cpp
 src/back-end/Backends/CinCout/FileExogenousEventProducer.cpp)
target_link_libraries(CinCoutBackend pluma yagiSignalInterface yagiExogenousEventInterface readline)
install(TARGETS CinCoutBackend DESTINATION lib)

# Asrael plugin
find_library(ASRAEL_C++ asrael-c++ /usr/local/lib)
find_library(LIB_XML_RPC++ xmlrpc++ /usr/lib)
find_library(LIB_XML_RPC_CLIENT++ xmlrpc_client++ /usr/lib)

if(ASRAEL_C++)
add_library(AsraelBackend SHARED
 src/back-end/Backends/Asrael/Connector.cpp
 src/back-end/Backends/Asrael/AsraelBackend.cpp
 src/back-end/Backends/Asrael/AsraelSignalHandler.cpp)
target_link_libraries(AsraelBackend pluma yagiSignalInterface yagiExogenousEventInterface ${ASRAEL_C++} ${LIB_XML_RPC++} ${LIB_XML_RPC_CLIENT++} readline)
install(TARGETS AsraelBackend DESTINATION lib)
endif()

find_package(Fawkes COMPONENTS core blackboard interface navgraph protobuf_comm SkillerInterface)
if (Fawkes_FOUND)
  add_library(FawkesBackend SHARED
    src/back-end/Backends/Fawkes/Connector.cpp
    src/back-end/Backends/Fawkes/FawkesBackend.cpp
    src/back-end/Backends/Fawkes/FawkesSignalHandler.cpp
    src/back-end/Backends/Fawkes/FawkesExogenousEventProducer.cpp
    src/back-end/Backends/Fawkes/yagi_protobuf.cpp)

  # This is necessary due to some hacks regarding LLSF processing
  # in the FawkesBackend. This should go away once YAGI message
  # processing has been upgrade.
  list(APPEND Fawkes_LIBRARIES "llsf_msgs")

  set_target_properties(FawkesBackend PROPERTIES
    INCLUDE_DIRECTORIES "${PLUMA_INCLUDE_DIR};${Fawkes_INCLUDE_DIRS}"
    COMPILE_FLAGS "${Fawkes_CFLAGS}"
    LINK_FLAGS "${Fawkes_LFLAGS}"
    LINK_LIBRARIES "${Fawkes_LIBRARIES}"
    INSTALL_RPATH "${Fawkes_LIBRARY_DIRS}"
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_WITH_INSTALL_RPATH TRUE)
  message(STATUS "Building Fawkes backend plugin")
else()
  message(STATUS "Fawkes not found, cannot build Fawkes plugin")
endif()

# Wumpus plugin
add_library(WumpusBackend SHARED
src/back-end/Backends/Wumpus/Connector.cpp
src/back-end/Backends/Wumpus/WumpusBackend.cpp
src/back-end/Backends/Wumpus/WumpusSignalHandler.cpp
src/back-end/Backends/Wumpus/WumpusExogenousEventProducer.cpp)
target_link_libraries(WumpusBackend pluma yagiSignalInterface yagiExogenousEventInterface boost_system)
install(TARGETS WumpusBackend DESTINATION lib)


# ======================================================================
# end Plugin section
# ======================================================================

set(yagi-front-end
src/front-end/astVisitors/ToStringVisitor.cpp
src/front-end/astClasses/ASTBuilder.cpp
src/front-end/astClasses/YAGICallbackConnector.h
src/front-end/cppInterfaceClasses/CToCppBridge.h
src/front-end/autoGenerated/YAGILexer.c
src/front-end/autoGenerated/YAGIParser.c
src/front-end/autoGenerated/YAGITreeWalker.c
src/front-end/ANTLRParser.cpp
src/front-end/astVisitors/TypeCheckVisitor.cpp
)

set(yagi-back-end
src/back-end/ASTVisitors/MainInterpretationVisitor.cpp
src/back-end/Database/SQLiteConnector.cpp
src/back-end/Database/DatabaseConnectorBase.h
src/back-end/Database/DatabaseManager.cpp
src/back-end/SQLGenerator.cpp
src/back-end/ASTVisitors/ActionProcedureInterpretationVisitor.cpp
src/back-end/ExecutableElementsContainer.cpp
src/back-end/Formulas/FormulaEvaluator.cpp
src/back-end/Formulas/IFormulaEvaluator.cpp
src/back-end/BackendFactory.cpp
src/back-end/Backend.cpp
src/back-end/Variables/VariableTable.cpp
src/back-end/Variables/VariableTableManager.cpp
src/back-end/TreeHelper.cpp
src/back-end/ASTVisitors/RewritingVisitor.cpp
src/back-end/Database/DBHelper.cpp
src/back-end/ExogenousEvents/IExogenousEventConsumer.cpp
src/back-end/ExogenousEvents/DefaultExogenousEventProducer.cpp
src/back-end/ExogenousEvents/ExoEventNotifier.cpp
src/back-end/BfsDataContainer.cpp
src/back-end/Formulas/NumericStringCompare.h
)

set(yagi-common
src/common/ASTNodeTypes/Expressions/NodeSetExpression.cpp
src/common/ASTNodeTypes/Expressions/NodeExpressionOperator.cpp
src/common/ASTNodeTypes/Statements/NodeAssignmentOperator.cpp
src/common/ASTNodeTypes/Expressions/NodeValueExpression.cpp
src/common/ASTNodeTypes/Statements/NodeIDAssignment.cpp
src/common/ASTNodeTypes/Statements/NodeVariableAssignment.cpp
src/common/ASTNodeTypes/Variables/NodeVariable.cpp
src/common/ASTNodeTypes/Variables/NodeVarList.cpp
src/common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.cpp
src/common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.cpp
src/common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.cpp
src/common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.cpp
src/common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.cpp
src/common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.cpp
src/common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.cpp
src/common/ASTNodeTypes/Statements/NodePick.cpp
src/common/ASTNodeTypes/Statements/NodeChoose.cpp
src/common/ASTNodeTypes/Statements/NodeConditional.cpp
src/common/ASTNodeTypes/Statements/NodeStatementBase.cpp
src/common/ASTNodeTypes/Statements/NodeWhileLoop.cpp
src/common/ASTNodeTypes/Statements/NodeTest.cpp
src/common/ASTNodeTypes/Statements/NodeSearch.cpp
src/common/ASTNodeTypes/Statements/NodeForLoop.cpp
src/common/ASTNodeTypes/Statements/NodeBlock.cpp
src/common/ASTNodeTypes/ProgramStructure/NodeProgram.cpp
src/common/ASTNodeTypes/Set/NodeSet.cpp
src/common/ASTNodeTypes/Formula/NodeQuantifiedFormula.cpp
src/common/ASTNodeTypes/Formula/NodeFormulaBase.cpp
src/common/ASTNodeTypes/Formula/NodeAtom.cpp
src/common/ASTNodeTypes/Formula/NodeConstant.cpp
src/common/ASTNodeTypes/Formula/NodeAtomConnective.cpp
src/common/ASTNodeTypes/Formula/NodeOperatorIn.cpp
src/common/ASTNodeTypes/Formula/NodeNegation.cpp
src/common/ASTNodeTypes/Formula/NodeCompoundFormula.cpp
src/common/ASTNodeTypes/Formula/NodeFormulaConnective.cpp
src/common/ASTNodeTypes/Identifier/NodeID.cpp
src/common/ASTNodeTypes/Domains/NodeDomainStringElements.cpp
src/common/ASTNodeTypes/Domains/NodeDomainString.cpp
src/common/ASTNodeTypes/DataTypes/NodeString.cpp
src/common/ASTNodeTypes/DataTypes/NodeValueList.cpp
src/common/ASTNodeTypes/DataTypes/NodePatternMatching.cpp
src/common/ASTNodeTypes/Tuple/NodeTuple.cpp
src/common/ASTNodeTypes/ASTNodeBase.h
src/common/ASTNodeTypes/Domains/NodeDomainBase.h
src/common/ASTNodeVisitorBase.h
src/common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.cpp
src/common/ASTNodeTypes/Statements/NodeProcExecution.cpp
src/common/ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.cpp
src/common/ASTNodeTypes/Statements/NodeFluentQuery.cpp
src/common/ASTNodeTypes/Declarations/SensingDecl/NodeSensingDecl.cpp
src/common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.cpp
src/common/ASTNodeTypes/ProgramStructure/NodeInclude.cpp
)

set(yagi-utils
src/utils/make_unique.h
src/utils/Any.h
src/utils/fileExists.h
src/utils/CustomComparers.cpp
src/utils/SetOperations.cpp
src/utils/ToStringHelper.cpp
src/utils/DateTimeHelper.cpp
src/utils/RandomNumberGenerator.cpp
src/utils/CommandLineArgsContainer.cpp
src/utils/StringManipulationHelper.h
)

add_library(yagi-interpreter SHARED
${yagi-front-end}
${yagi-back-end}
${yagi-common}
${yagi-utils}
src/front-end/YAGIInterpreter.cpp
)
target_link_libraries(yagi-interpreter ${ANTLR_LIBRARIES} readline ncurses ${SQLITE_LIBRARIES} pluma yagiSignalInterface yagiExogenousEventInterface)

add_executable(yagi
src/front-end/YAGIMain.cpp
)

target_link_libraries(yagi yagi-interpreter)

# install yagi libs and executable
install(TARGETS yagi-interpreter DESTINATION lib)
install(TARGETS yagi DESTINATION bin)

# install include files used for interpreter
install(FILES src/front-end/cppInterfaceClasses/CToCppBridge.h DESTINATION include/yagi/front-end/cppInterfaceClasses)
install(FILES src/front-end/astClasses/YAGICallbackConnector.h DESTINATION include/yagi/front-end/astClasses)
install(FILES src/front-end/astClasses/ASTBuilder.h DESTINATION include/yagi/front-end/astClasses)
install(FILES src/front-end/YAGIInterpreter.h DESTINATION include/yagi/front-end)
install(FILES src/back-end/BackendFactory.h src/back-end/Backend.h DESTINATION include/yagi/back-end)
install(FILES src/back-end/ExogenousEvents/IExogenousEventProducer.h DESTINATION include/yagi/back-end/ExogenousEvents)
install(FILES src/back-end/Signals/IYAGISignalHandler.h src/back-end/Backend.h DESTINATION include/yagi/back-end/Signals)
install(FILES src/utils/CommandLineArgsContainer.h DESTINATION include/yagi/utils)
install(FILES src/utils/Any.h DESTINATION include/yagi/utils)
install(DIRECTORY src/common DESTINATION include/yagi FILES_MATCHING PATTERN "*.h")
