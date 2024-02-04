#include <dbng.hpp>
#include <sqlite.hpp>

inline ormpp::dbng<ormpp::sqlite> sqlite;

class _DbRAII {
 public:
  _DbRAII() {
    sqlite.connect("class_system.db");
  }

  _DbRAII(const _DbRAII&)             = delete;
  _DbRAII& operator=(const _DbRAII&)  = delete;
  _DbRAII(const _DbRAII&&)            = delete;
  _DbRAII& operator=(const _DbRAII&&) = delete;

  ~_DbRAII() {
    sqlite.disconnect();
  }
  // NOLINTNEXTLINE
} static __g_db_raii;
