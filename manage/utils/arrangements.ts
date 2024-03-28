import type { CompleteArrangement, PartialArrangement, WeekdayArrangement } from "~/type";

export function DailyArrFromWeekday(arr: WeekdayArrangement) {
  return arr.student_ids[(moment().weekday() - 1) % 5];
}
