#include "util.h"

namespace util {

std::string GetStudentNameById(const google::protobuf::RepeatedPtrField<class_system::ClassInfo::Student>& students, const int& id) {
  const auto it = std::find_if(students.begin(), students.end(), [id](const auto& student) { return student.id() == id; });
  return it == students.end() ? "" : it->name();
}

}  // namespace util
