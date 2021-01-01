#include "MethodInfo.hpp"

Object_Layout::MethodInfo::MethodInfo(Object_Layout::ScopeType scopeType, Object_Layout::ReturnType returnType) {
	this->_scopeType = scopeType;
	this->_returnType = returnType;
}
Object_Layout::MethodInfo::MethodInfo() : MethodInfo(Object_Layout::ScopeType::Dynamic, Object_Layout::ReturnType::Normal) {}