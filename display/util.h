#pragma once
#include <proto/ClassInfo.pb.h>

namespace util {

std::string GetStudentNameById(const google::protobuf::RepeatedPtrField<class_system::ClassInfo::Student>& students, const int& id);
}
