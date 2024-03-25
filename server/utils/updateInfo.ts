import type { InputInfo } from "~/type";

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

    for (const student of input.students.filter(student => prevInfo.students.some(prev => prev.id === student.id))) {
      await db.student.updateMany({
        where: { id: student.id },
        data: student,
      });
    }
  }

  if (input.events) {
    const newEvents = input.events.filter(event => !prevInfo.events.some(prev => prev.id === event.id));
    await db.event.createMany({ data: newEvents.map((event) => { delete event.id; return { ...event, class_id }; }) });

    const deletedEventIds = prevInfo.events
      .filter(prev => !input.events?.some(event => event.id === prev.id))
      .map(({ id }) => id);
    await db.event.deleteMany({ where: { id: { in: deletedEventIds } } });

    for (const event of input.events.filter(event => prevInfo.events.some(prev => prev.id === event.id))) {
      await db.event.updateMany({
        where: { id: event.id },
        data: event,
      });
    }
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
      await db.lesson.updateMany({
        where: { id: lesson.id },
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

    for (const completeArr of input.complete_arr.filter(completeArr => prevInfo.complete_arr.some(prev => prev.id === completeArr.id))) {
      await db.complete_arr.updateMany({
        where: { id: completeArr.id },
        data: completeArr,
      });
    }
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

    for (const partialArr of input.partial_arr.filter(partialArr => prevInfo.partial_arr.some(prev => prev.id === partialArr.id))) {
      await db.partial_arr.updateMany({
        where: { id: partialArr.id },
        data: partialArr,
      });
    }
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

    for (const weekdayArr of input.weekday_arr.filter(weekdayArr => prevInfo.weekday_arr.some(prev => prev.id === weekdayArr.id))) {
      await db.weekday_arr.updateMany({
        where: { id: weekdayArr.id },
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
  }

  if (input.sentences) {
    const newSentences = input.sentences.filter(sentence => !prevInfo.sentences.some(prev => prev.id === sentence.id));

    await db.sentence.createMany({
      data: newSentences.map((sentence) => { delete sentence.id; return sentence; }),
    });

    const deletedSentencesIds = prevInfo.sentences
      .filter(prev => !input.sentences?.some(sentence => sentence.id === prev.id))
      .map(({ id }) => id);
    await db.sentence.deleteMany({ where: { id: { in: deletedSentencesIds } } });

    for (const sentence of input.sentences.filter(sentence => prevInfo.sentences.some(prev => prev.id === sentence.id))) {
      await db.sentence.updateMany({
        where: { id: sentence.id },
        data: sentence,
      });
    }
  }

  const info = await getInfo(class_id);
  noticeInfo(class_id, info);
  return createResp(info);
}
