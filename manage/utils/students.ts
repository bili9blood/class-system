import type { Student } from "~/type";

export function StudentDisplayString(stu: Student | undefined) {
  if (!stu)
    return "";
  return `${stu.inclass_id.toString().padStart(2, "0")}${stu.name}`;
}
