import type { CompleteArrangement, PartialArrangement, WeekdayArrangement } from "~/type";

export function DailyArrFromWeekday(arr: WeekdayArrangement) {
  const w = moment().weekday();
  return w - 1 < 5 ? arr.student_ids[(w - 1) % 5] : [];
}
