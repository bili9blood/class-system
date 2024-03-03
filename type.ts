import type { infer as zInfer } from "zod";

export interface Info {
  class_id: number;
  class_name: string;

  students: Student[];
  events: Event[];
  notices: Notice[];
  lessons: Lesson[];

  complete_arr: CompleteArrangement[];
  partial_arr: PartialArrangement[];
  weekday_arr: WeekdayArrangement[];

  sentences: Sentence[];
}

export interface Student {
  id: number;
  name: string;
  inclass_id: number;
}

export interface Event {
  id: number;
  title: string;
  date: string;
  important: boolean;
}

export interface Notice {
  id: number;
  title: string;
  date: string;
  text: string;
}

export interface Lesson {
  id: number;
  lessons: [string, string, string, string, string];
  startTm: string;
  endTm: string;
};

interface BasicArrangement { id: number; job: string }

interface RolledArrangement extends BasicArrangement {
  start_idx: number;
  start_date: string;
  days_one_step: number;
  students_one_step: number;
}

export interface CompleteArrangement extends RolledArrangement {}

export interface PartialArrangement extends RolledArrangement {
  student_ids: number[];
}

export interface WeekdayArrangement extends BasicArrangement {
  student_ids: [number[], number[], number[], number[], number[]];
}

export interface Sentence {
  id: number;
  text: string;
  author: string;
}

/* ---------------------------------------------------------------- */
/*                            Zod Parsers                           */
/* ---------------------------------------------------------------- */

export type InputInfo = zInfer<typeof inputInfoParser>;

export const studentParser = z.object({
  id: z.number().optional(),
  name: z.string(),
  inclass_id: z.number(),
});

export const eventParser = z.object({
  id: z.number().optional(),
  title: z.string(),
  date: z.string(),
  important: z.boolean(),
});

export const noticeParser = z.object({
  id: z.number().optional(),
  title: z.string(),
  date: z.string(),
  text: z.string(),
});

export const lessonParser = z.object({
  id: z.number().optional(),
  lessons: z.tuple([
    z.string(),
    z.string(),
    z.string(),
    z.string(),
    z.string(),
  ]),
  startTm: z.string().length(4),
  endTm: z.string().length(4),
});

export const basicArrParser = z.object({ id: z.number().optional(), job: z.string() });

export const rolledArrParser = z.object({
  ...basicArrParser.shape,
  start_idx: z.number(),
  start_date: z.string(),
  days_one_step: z.number(),
  students_one_step: z.number(),
});

export const completeArrParser = rolledArrParser;

export const partialArrParser = z.object({
  ...rolledArrParser.shape,
  student_ids: z.array(z.number()),
});

export const weekdayArrParser = z.object({
  ...basicArrParser.shape,
  student_ids: z.tuple([
    z.array(z.number()),
    z.array(z.number()),
    z.array(z.number()),
    z.array(z.number()),
    z.array(z.number()),
  ]),
});

export const sentenceParser = z.object({
  id: z.number().optional(),
  text: z.string(),
  author: z.string(),
});

export const inputInfoParser = z.object({
  students: z.array(studentParser).optional(),
  events: z.array(eventParser).optional(),
  notices: z.array(noticeParser).optional(),
  lessons: z.array(lessonParser).optional(),

  complete_arr: z.array(completeArrParser).optional(),
  partial_arr: z.array(partialArrParser).optional(),
  weekday_arr: z.array(weekdayArrParser).optional(),

  sentences: z.array(sentenceParser).optional(),
});
