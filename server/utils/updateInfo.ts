import type { InputInfo } from "~/type";

function objectEquals<O extends Record<string, any>>(lhs: O | undefined, rhs: O | undefined) {
  if (lhs === void 0 || rhs === void 0)
    return false;
  return Object.keys(lhs).every(key => lhs[key] === rhs[key]);
}

export async function updateInfo(class_id: number, input: InputInfo) {
  const db = useDatabase();
  const prevInfo = await getInfo(class_id);

  if (input.students) {
    const newStudents = input.students.filter(student => !prevInfo.students.some(prev => prev.id === student.id));
    await db.student.createMany({ data: newStudents.map((student) => { delete student.id; return { ...student, class_id }; }) });

    const deletedStudentIds = prevInfo.students
      .filter(prev => !input.students?.some(student => student.id === prev.id))
      .map(({ id }) => id);
    await db.student.deleteMany({ where: { id: { in: deletedStudentIds } } });

    input.students.filter(student => prevInfo.students.some(prev => prev.id === student.id)).forEach(async (student) => {
      if (!objectEquals(student, prevInfo.students.find(prev => prev.id === student.id))) {
        await db.student.updateMany({
          where: { id: student.id ?? 0 },
          data: student,
        });
      }
    });
  }

  if (input.events) {
    const newEvents = input.events.filter(event => !prevInfo.events.some(prev => prev.id === event.id));
    await db.event.createMany({ data: newEvents.map((event) => { delete event.id; return { ...event, class_id }; }) });

    const deletedEventIds = prevInfo.events
      .filter(prev => !input.events?.some(event => event.id === prev.id))
      .map(({ id }) => id);
    await db.event.deleteMany({ where: { id: { in: deletedEventIds } } });

    input.events.filter(event => prevInfo.events.some(prev => prev.id === event.id)).forEach(async (event) => {
      if (!objectEquals(event, prevInfo.events.find(prev => prev.id === event.id))) {
        await db.event.updateMany({
          where: { id: event.id ?? 0 },
          data: event,
        });
      }
    });
  }

  if (input.notices) {
    const newNotices = input.notices.filter(notice => !prevInfo.notices.some(prev => prev.id === notice.id));
    await db.notice.createMany({ data: newNotices.map((notice) => { delete notice.id; return { ...notice, class_id }; }) });

    const deletedNoticesIds = prevInfo.notices
      .filter(prev => !input.notices?.some(notice => notice.id === prev.id))
      .map(({ id }) => id);
    await db.notice.deleteMany({ where: { id: { in: deletedNoticesIds } } });

    input.notices.filter(notices => prevInfo.notices.some(prev => prev.id === notices.id)).forEach(async (notice) => {
      if (!objectEquals(notice, prevInfo.notices.find(prev => prev.id === notice.id))) {
        await db.notice.updateMany({
          where: { id: notice.id ?? 0 },
          data: notice,
        });
      }
    });
  }

  if (input.lessons) {
    const newLessons = input.lessons.filter(lesson => !prevInfo.lessons.some(prev => prev.id === lesson.id));
    await db.lesson.createMany({
      data: newLessons.map(({ lessons, startTm, endTm }, lesson_number) => {
        return ({
          mon: lessons[0],
          tue: lessons[1],
          wed: lessons[2],
          thu: lessons[3],
          fri: lessons[4],
          lesson_number,
          start_tm: startTm,
          end_tm: endTm,
          class_id,
        });
      }),
    });

    const deletedLessonIds = prevInfo.lessons
      .filter(prev => !input.lessons?.some(lesson => lesson.id === prev.id))
      .map(({ id }) => id);
    await db.lesson.deleteMany({ where: { id: { in: deletedLessonIds } } });

    input.lessons.filter(lesson => prevInfo.lessons.some(prev => prev.id === lesson.id)).forEach(async (lesson, idx) => {
      if (!objectEquals(lesson, prevInfo.lessons.find(prev => prev.id === lesson.id))) {
        await db.lesson.updateMany({
          where: { id: lesson.id ?? 0 },
          data: {
            mon: lesson.lessons[0],
            tue: lesson.lessons[1],
            wed: lesson.lessons[2],
            thu: lesson.lessons[3],
            fri: lesson.lessons[4],
            lesson_number: idx,
            start_tm: lesson.startTm,
            end_tm: lesson.endTm,
            class_id,
          },
        });
      }
    });
  }

  if (input.complete_arr) {
    const newCompleteArr = input.complete_arr.filter(completeArr => !prevInfo.complete_arr.some(prev => prev.id === completeArr.id));
    await db.complete_arr.createMany({
      data: newCompleteArr.map((arr) => {
        delete arr.id;
        return {
          ...arr,
          class_id,
        };
      }),
    });

    const deletedCompleteArrIds = prevInfo.complete_arr
      .filter(prev => !input.complete_arr?.some(completeArr => completeArr.id === prev.id))
      .map(({ id }) => id);
    await db.complete_arr.deleteMany({ where: { id: { in: deletedCompleteArrIds } } });

    input.complete_arr.filter(completeArr => prevInfo.complete_arr.some(prev => prev.id === completeArr.id)).forEach(async (completeArr) => {
      if (!objectEquals(completeArr, prevInfo.complete_arr.find(prev => prev.id === completeArr.id))) {
        await db.complete_arr.updateMany({
          where: { id: completeArr.id ?? 0 },
          data: completeArr,
        });
      }
    });
  }

  if (input.partial_arr) {
    const newPartialArr = input.partial_arr.filter(partialArr => !prevInfo.partial_arr.some(prev => prev.id === partialArr.id));
    await db.partial_arr.createMany({
      data: newPartialArr.map((arr) => {
        delete arr.id;
        return {
          ...arr,
          class_id,
        };
      }),
    });

    const deletedPartialArrIds = prevInfo.partial_arr
      .filter(prev => !input.partial_arr?.some(partialArr => partialArr.id === prev.id))
      .map(({ id }) => id);
    await db.partial_arr.deleteMany({ where: { id: { in: deletedPartialArrIds } } });

    input.partial_arr.filter(partialArr => prevInfo.partial_arr.some(prev => prev.id === partialArr.id)).forEach(async (partialArr) => {
      if (!objectEquals(partialArr, prevInfo.partial_arr.find(prev => prev.id === partialArr.id))) {
        await db.partial_arr.updateMany({
          where: { id: partialArr.id ?? 0 },
          data: partialArr,
        });
      }
    });
  }

  if (input.weekday_arr) {
    const newWeekdayArr = input.weekday_arr.filter(weekdayArr => !prevInfo.weekday_arr.some(prev => prev.id === weekdayArr.id));
    await db.weekday_arr.createMany({
      data: newWeekdayArr.map((arr) => {
        delete arr.id;
        return {
          job: arr.job,
          mon_student_ids: arr.student_ids[0],
          tue_student_ids: arr.student_ids[1],
          wed_student_ids: arr.student_ids[2],
          thu_student_ids: arr.student_ids[3],
          fri_student_ids: arr.student_ids[4],
          class_id,
        };
      }),
    });

    const deletedWeekdayArrIds = prevInfo.weekday_arr
      .filter(prev => !input.weekday_arr?.some(weekdayArr => weekdayArr.id === prev.id))
      .map(({ id }) => id);
    await db.weekday_arr.deleteMany({ where: { id: { in: deletedWeekdayArrIds } } });

    input.weekday_arr.filter(weekdayArr => prevInfo.weekday_arr.some(prev => prev.id === weekdayArr.id)).forEach(async (weekdayArr) => {
      if (!objectEquals(weekdayArr, prevInfo.weekday_arr.find(prev => prev.id === weekdayArr.id))) {
        await db.weekday_arr.updateMany({
          where: { id: weekdayArr.id ?? 0 },
          data: {
            job: weekdayArr.job,
            mon_student_ids: weekdayArr.student_ids[0],
            tue_student_ids: weekdayArr.student_ids[1],
            wed_student_ids: weekdayArr.student_ids[2],
            thu_student_ids: weekdayArr.student_ids[3],
            fri_student_ids: weekdayArr.student_ids[4],
            class_id,
          },
        });
      }
    });
  }

  const info = await getInfo(class_id);
  noticeInfo(class_id, info);
  return createResp(info);
}
