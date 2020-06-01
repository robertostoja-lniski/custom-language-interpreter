//
// Created by robert on 01.06.2020.
//

#ifndef TKOM_EVALUATIONVISITOR_H
#define TKOM_EVALUATIONVISITOR_H

#include "Visitor.h"
#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include <variant>
#include <string>
#include <cassert>
#include <map>
#include <thread>
#include <zconf.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <sys/wait.h>

struct BaseHandler {
    bool isRegistration {false};
    virtual void run() = 0;
    ~BaseHandler() = default;
};

struct SendRaportHandler : BaseHandler {
    std::string addr;
    std::string type;
    std::string dir;
    void run() override {
        if(addr.empty() || type.empty() || dir.empty()) {
            throw std::runtime_error("Not enough args to run set:\n"
                                     "addr     email address\n"
                                     ",type     raport type\n"
                                     "and       dir to analyze");
        }
        if(type == "file_number") {
            size_t fileNum = 0;
            DIR * dirp;
            struct dirent * entry;

            dirp = opendir(dir.c_str());
            while ((entry = readdir(dirp)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    fileNum++;
                }
            }
            closedir(dirp);

            std::ofstream tmp;
            tmp.open("/tmp/mail");
            tmp << "In dir " + dir + " there are " + std::to_string(fileNum).c_str() + " files.\n";
            tmp.close();

            std::string command = "sendmail " + addr + " < /tmp/mail";
            system(command.c_str());
        }
    }
};

struct BackupHandler : BaseHandler {
    std::string dest;
    std::string dir;
    void run() override {
        if(dest.empty() || dir.empty()) {
            throw std::runtime_error("Not enough args to run");
        }
        std::string command = "cp -R " + dest + " " + dir;
        system(command.c_str());
    }
};

struct CheckSystemHandler : BaseHandler {
    std::string output;
    std::string type;
    std::string freq;
    void run() override {
        if(output.empty() || type.empty() || freq.empty()) {
            throw std::runtime_error("Not enough args to run. Set:\n"
                                     "output    file to store raport"
                                     "type      raport type"
                                     "freq      frequency of raports");
        }
        if(type == "file_number") {
            while(true) {
                size_t fileNum = 0;
                DIR * dirp;
                struct dirent * entry;

                dirp = opendir("/usr");
                while ((entry = readdir(dirp)) != nullptr) {
                    if (entry->d_type == DT_REG) {
                        fileNum++;
                    }
                }
                closedir(dirp);

                std::ofstream tmp;
                tmp.open(output);
                tmp << "In usr there are " << fileNum << " files.\n";
                tmp.close();
                usleep(std::stoi(freq) * 1000000);
            }
        }
    }
};

struct RunHandler : BaseHandler {
    std::string path;
    void run() override {
        if(path.empty()) {
            throw std::runtime_error("Not enough args to run. Set\n"
                                     "path      script to run");
        }
        system(path.c_str());
    }
    void update(std::shared_ptr<RunHandler> toUpdate) {
        if(!toUpdate->path.empty()) {
            path = toUpdate->path;
        }
    }
};

struct EvaluationVisitor : Visitor {
    struct SystemHandlerInfo {
        std::shared_ptr<BaseHandler> handler;
        pid_t handlerPid;
        SystemHandlerInfo() = default;
        SystemHandlerInfo(std::shared_ptr<BaseHandler> handler)
                : handler(handler) {}
        void run() {
            pid_t currentHandlerPid = fork();
            if(currentHandlerPid == 0) {
                handler->run();
            } else {
                handlerPid = currentHandlerPid;
                wait(NULL);
            }
        }
        void stop() {
            auto msg = "kill -9 " + std::to_string(handlerPid);
            system(msg.c_str());
        }
    };
    struct Context {
        enum class Specifiers {INT, FLOAT, STRING, SYSTEM_HANDLER};
        std::map<std::string, std::variant<int, double, std::string>> variableAssignmentMap;
        std::map<std::string, std::string> declarationMap;
        std::map<std::string, FunctionExpression*> functionDeclarationMap;
        std::map<std::string, std::shared_ptr<SystemHandlerInfo>> systemHandlerDeclarations;
        std::deque<std::variant<int, double, std::string>> operands;
        Context() = default;
        auto getOperandAndPopFromContext() {
            auto ret = operands.back();
            operands.pop_back();
            return ret;
        }
        bool isVariableAssigned(std::string variableToCheck) {
            return variableAssignmentMap.find(variableToCheck) != variableAssignmentMap.end();
        }
        auto getAssignedValue(std::string variableToGet) {
            return variableAssignmentMap[variableToGet];
        }

        bool isSystemHandlerAssigned(std::string name) {
            return systemHandlerDeclarations.find(name) != systemHandlerDeclarations.end();
        }
    };

    auto getSystemHandlerReferenceByName(std::string name) {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->isSystemHandlerAssigned(name)) {
                return currentCtx->systemHandlerDeclarations[name];
            }
        }
        throw std::runtime_error("No value is assigned");
    }

    auto getAssignedValueFromNearestContext(std::string varName) {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->isVariableAssigned(varName)) {
                return currentCtx->getAssignedValue(varName);
            }
        }
        throw std::runtime_error("No value is assigned");
    }

    auto moveLocalOperandFromNearestContext() {
        auto& currentContext = ctx.back();
        return currentContext.getOperandAndPopFromContext();
    }

    void updateHandler(std::string sign, std::string op, std::shared_ptr<SystemHandlerInfo> handlerRef) {
        auto isSend = std::dynamic_pointer_cast<SendRaportHandler>(handlerRef->handler);
        auto isBackup = std::dynamic_pointer_cast<BackupHandler>(handlerRef->handler);
        auto isRun = std::dynamic_pointer_cast<RunHandler>(handlerRef->handler);
        auto isCheckSys = std::dynamic_pointer_cast<CheckSystemHandler>(handlerRef->handler);
        // removes outer quotes
        sign = (sign).substr(1,(sign).size()-2);
        if(op == "raport_type") {
            if(isSend) {
                isSend->type = sign;
                return;
            }
            if(isCheckSys) {
                isCheckSys->type = sign;
                return;
            }
        }
        if(op == "mail") {
            if(isSend) {
                isSend->addr = sign;
                return;
            }
        }
        if(op == "dir") {
            if(isSend) {
                isSend->dir = sign;
                return;
            }
            if(isBackup) {
                isBackup->dir = sign;
                return;
            }
        }
        if(op == "path") {
            if(isRun) {
                isRun->path = sign;
                return;
            }
            if(isCheckSys) {
                isCheckSys->output = sign;
                return;
            }
        }
        if(op == "freq") {
            if(isCheckSys) {
                isCheckSys->freq = sign;
                return;
            }
        }
        if(op == "dest") {
            if(isBackup) {
                isBackup->dest = sign;
                return;
            }
        }
    }
    void registerHandler(std::string type, std::shared_ptr<SystemHandlerInfo> handlerRef) {
        if(type == "check_system") {
            handlerRef->handler = std::make_unique<CheckSystemHandler>();
        } else if(type == "send_raport") {
            handlerRef->handler = std::make_unique<SendRaportHandler>();
        } else if(type == "backup") {
            handlerRef->handler = std::make_unique<BackupHandler>();
        } else if(type == "run") {
            handlerRef->handler = std::make_unique<RunHandler>();
        }
    }
    void updateSystemHandler(std::string handlerName, std::string fieldReference) {
        auto wasHandlerDeclared = [](std::string varName, const std::deque<Context> ctx) -> bool {
            for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
                if(currentCtx->systemHandlerDeclarations.find(varName) != currentCtx->systemHandlerDeclarations.end()) {
                    return true;
                }
            }
            return false;
        };

        auto toSign = moveLocalOperandFromNearestContext();
        if(!wasHandlerDeclared(handlerName, ctx)) {
            throw std::runtime_error("Handler not declared");
        }

        if(const auto toSignStr (std::get_if<std::string>(&toSign)); toSignStr) {
            auto handlerRef = getSystemHandlerReferenceByName(handlerName);
            if(fieldReference == "register") {
                registerHandler(*toSignStr, handlerRef);
                return;
            }
            updateHandler(*toSignStr, fieldReference, handlerRef);
        }
    }

    class OperatorHandler {
    private:
        std::string op;
        template<typename L, typename R>
        auto add(L left, R right) {
            return left + right;
        }
        template<typename L, typename R>
        auto multiply(L left, R right) {
            return left * right;
        }
        template<typename L, typename R>
        auto divide(L left, R right) {
            return left / right;
        }
        template<typename L, typename R>
        auto eq(L left, R right) {
            return (int)(left == right);
        }
        template<typename L, typename R>
        auto geq(L left, R right) {
            return (int)(left >= right);
        }
        template<typename L, typename R>
        auto leq(L left, R right) {
            return (int)(left <= right);
        }
        template<typename L, typename R>
        auto l(L left, R right) {
            return (int)(left < right);
        }
        template<typename L, typename R>
        auto g(L left, R right) {
            return (int)(left > right);
        }
        template<typename L, typename R>
        auto boolAnd(L left, R right) {
            return (int)(left && right);
        }
        template<typename L, typename R>
        auto boolOr(L left, R right) {
            return (int)(left || right);
        }
        template<typename L, typename R>
        std::variant<int,double,std::string> count(L left, R right) {
            // could not make map of functions
            // because they are function templates
            if(op == "+") {
                return add(left, right);
            }
            if(op == "-") {
                return add(left, right * (-1));
            }
            if(op == "*") {
                return multiply(left, right);
            }
            if(op == "/") {
                return divide(left, right);
            }
            if(op == "==") {
                return eq(left, right);
            }
            if(op == ">=") {
                return geq(left, right);
            }
            if(op == "<=") {
                return leq(left, right);
            }
            if(op == "<") {
                return l(left, right);
            }
            if(op == ">") {
                return g(left, right);
            }
            if(op == "&") {
                return boolAnd(left, right);
            }
            if(op == "|") {
                return boolOr(left, right);
            }
        }
    public:
        OperatorHandler(std::string op) : op(op) {}
        auto addResToCtx(std::variant<int, double, std::string> leftOperand,
                         std::variant<int, double, std::string> rightOperand, std::deque<Context> &context) {

            if (const auto l (std::get_if<int>(&leftOperand)); l) {
                if (const auto r (std::get_if<double>(&rightOperand)); r) {
                    std::variant<int, double, std::string> countResult = count(*l,*r);
                    context.back().operands.push_back(countResult);
                }
            }

            if (const auto l (std::get_if<int>(&leftOperand)); l) {
                if (const auto r (std::get_if<int>(&rightOperand)); r) {
                    std::variant<int, double, std::string> countResult = count(*l,*r);
                    context.back().operands.push_back(countResult);
                }
            }

            if (const auto l (std::get_if<double>(&leftOperand)); l) {
                if (const auto r (std::get_if<int>(&rightOperand)); r) {
                    std::variant<int, double, std::string> countResult = count(*l,*r);
                    context.back().operands.push_back(countResult);
                }
            }

            if (const auto l (std::get_if<double>(&leftOperand)); l) {
                if (const auto r (std::get_if<double>(&rightOperand)); r) {
                    std::variant<int, double, std::string> countResult = count(*l,*r);
                    context.back().operands.push_back(countResult);
                }
            }
        }
    };

    void handleOperation(std::string operation) {
        auto leftOperand = moveLocalOperandFromNearestContext();
        auto rightOperand = moveLocalOperandFromNearestContext();

        // substitude value for varName
        if (const auto varName (std::get_if<std::string>(&leftOperand)); varName) {
            leftOperand = getAssignedValueFromNearestContext(*varName);
        }
        if (const auto varName (std::get_if<std::string>(&rightOperand)); varName) {
            rightOperand = getAssignedValueFromNearestContext(*varName);
        }

        OperatorHandler operatorHandler(operation);
        operatorHandler.addResToCtx(leftOperand, rightOperand, ctx);
    }

    template<typename T>
    void addToCurrentContext(T t) {
        ctx.back().operands.push_back(t);
    }

    // front is most global
    // back is most local
    std::deque<Context> ctx;

    void visit(StringExpression* stringExpression) override;
    void visit(IntExpression* intExpression) override;
    void visit(FloatExpression* floatExpression) override;
    void visit(VarNameExpression* varNameExpression)  override;
    void visit(DoubleArgsExpression* doubleArgsExpression) override;
    void visit(AdditionExpression* additionExpression) override;
    void visit(MultiplyExpression* multiplyExpression)  override;
    void visit(DivideExpression* divideExpression) override;
    void visit(AssignExpression* assignExpression) override;
    void visit(RootExpression* rootExpression) override;
    void visit(VarDeclarationExpression* varDeclarationExpression) override;
    void visit(TypeSpecifierExpression* typeSpecifierExpression) override;
    void visit(BooleanAndExpression* booleanAndExpression) override;
    void visit(BooleanOrExpression* booleanOrExpression) override;
    void visit(BooleanOperatorExpression* booleanOrExpression) override;
    void visit(FunctionArgExpression* functionArgExpression) override;
    void visit(FunctionExpression* functionExpression) override;
    void visit(NoArgFunctionExpression* noArgFunctionExpression) override;
    void visit(NewLineExpression* newLineExpression) override;
    void visit(BodyExpression* bodyExpression) override;
    void visit(IfExpression* ifExpression) override;
    void visit(ElseExpression* elseExpression) override;
    void visit(WhileExpression* whileExpression) override;
    void visit(DoExpression* doExpression) override;
    void visit(FileExpression* fileExpression) override;
    void visit(FieldReferenceExpression* fieldReferenceExpression) override;
    void visit(FunctionCallExpression* functionCallExpression) override;
    void visit(PutExpression* putExpression) override;
    void visit(RetExpression* retExpression) override;
    void visit(SystemHandlerExpression* systemHandlerExpression) override;
    void visit(SystemHandlerDeclExpression* systemHandlerDeclExpression) override;
};

#endif //TKOM_EVALUATIONVISITOR_H
