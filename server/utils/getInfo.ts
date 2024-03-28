import type { Event, Info, Notice } from "~/type";

async function updateByDate(_events: Event[], _notices: Notice[]) {
  const todayStr = moment().format("YYYYMMDD");
  const db = useDatabase();

  const events = _events.filter(({ date }) => date >= todayStr);
  await db.event.deleteMany({ where: { id: { notIn: events.map(e => e.id) } } });

  const notices = _notices.filter(({ date }) => date === "FOREVER" || date >= todayStr);
  await db.notice.deleteMany({ where: { id: { notIn: notices.map(e => e.id) } } });

  return { events, notices };
}

export async function getInfo(class_id: number) {
  const info: Info = <Info>{};
  info.class_id = class_id;
  const db = useDatabase();
  info.class_name
    = ((
      await
      db.class_.findUnique({ where: { id: class_id }, select: { name: true } })
    ) ?? { name: "" }
    ).name;

  info.students = await db.student.findMany({
    where: { class_id },
    orderBy: { inclass_id: "asc" },
  });

  info.events = await db.event.findMany({
    where: { class_id },
  });
  info.notices = await db.notice.findMany({
    where: { class_id },
  });
  const updated = await updateByDate(info.events, info.notices);
  info.events = updated.events;
  info.notices = updated.notices;

  info.lessons = (await db.lesson.findMany({
    where: { class_id },
    orderBy: { lesson_number: "asc" },
  })).map(l => ({ id: l.id, lessons: [l.mon, l.tue, l.wed, l.thu, l.fri], startTm: l.start_tm, endTm: l.end_tm }));

  info.complete_arr = await db.complete_arr.findMany({
    where: { class_id },
  });

  // @ts-expect-error JsonValue -> number[]
  info.partial_arr = (await db.partial_arr.findMany({
    where: { class_id },
  }));

  // @ts-expect-error JsonValue -> number[]
  info.weekday_arr = (await db.weekday_arr.findMany({
    where: { class_id },
  })).map(
    ({ id, job, mon_student_ids, tue_student_ids, wed_student_ids, thu_student_ids, fri_student_ids }) =>
      ({ id, job, student_ids: [mon_student_ids, tue_student_ids, wed_student_ids, thu_student_ids, fri_student_ids] }),
  );

  info.sentences = await db.sentence.findMany();

  return info;
}
