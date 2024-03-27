<script setup lang="ts">
import type { Lesson } from "~/type";

definePageMeta({
  name: "课程",
});

const { info } = storeToRefs(useClassStore());

function FormatTime(time: string) {
  return time.replace(/(\d\d)(\d\d)/, "$1:$2");
}

function HandleRemoveLessonLine(idx: number) {
  info.value?.lessons.splice(idx, 1);
}

function HandleInsertLessonLine(idx: number) {
  info.value?.lessons.splice(idx + 1, 0, { id: 0, lessons: ["", "", "", "", ""], startTm: "0000", endTm: "0000" });
}
</script>

<template>
  <div>
    <q-card w-full overflow-x-auto bg-secondary>
      <q-card-section min-w-170>
        <q-markup-table flat justify-center bg-transparent>
          <thead>
            <tr>
              <th>星期一</th>
              <th>星期二</th>
              <th>星期三</th>
              <th>星期四</th>
              <th>星期五</th>
              <th>上课时间</th>
              <th>下课时间</th>
              <th>操作</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="line, line_idx in info?.lessons" :key="line.id">
              <td v-for="_, le_idx in line.lessons" :key="le_idx">
                <q-input v-model="line.lessons[le_idx]" outlined dense />
              </td>

              <td>
                <div flex="~ items-center" align-middle text-black>
                  <q-icon name="access_time" cursor-pointer>
                    <q-popup-proxy cover transition-show="scale" transition-hide="scale">
                      <q-time v-model="line.startTm" mask="HHmm">
                        <div class="row items-center justify-end">
                          <q-btn v-close-popup label="关闭" color="primary" flat />
                        </div>
                      </q-time>
                    </q-popup-proxy>
                  </q-icon>
                  {{ FormatTime(line.startTm) }}
                </div>
              </td>

              <td>
                <div flex="~ items-center" text-center text-black>
                  <q-icon name="access_time" cursor-pointer>
                    <q-popup-proxy cover transition-show="scale" transition-hide="scale">
                      <q-time v-model="line.endTm" mask="HHmm">
                        <div class="row items-center justify-end">
                          <q-btn v-close-popup label="关闭" color="primary" flat />
                        </div>
                      </q-time>
                    </q-popup-proxy>
                  </q-icon>
                  {{ FormatTime(line.endTm) }}
                </div>
              </td>

              <td>
                <div flex>
                  <q-btn flat dense label="删除" @click="HandleRemoveLessonLine(line_idx)" />
                  <q-btn flat dense label="插入" @click="HandleInsertLessonLine(line_idx)" />
                </div>
              </td>
            </tr>
          </tbody>
        </q-markup-table>
      </q-card-section>
    </q-card>
  </div>
</template>
