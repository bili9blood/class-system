#pragma once

namespace file {
void ForeachDir(const QDir &dir, const std::function<void(const QFileInfo &)> &func);

[[nodiscard]] QString RelativePath(const QFileInfo &info, const QDir &base_dir);
}  // namespace file
