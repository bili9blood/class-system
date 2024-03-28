<script setup lang="ts">
import EditWeekdayArr from "~/manage/components/dialogs/EditWeekdayArr.vue";

const $q = useQuasar();

const { info } = storeToRefs(useClassStore());

function HandleRemoveArr(idx: number) { info.value?.weekday_arr.splice(idx, 1); }
function HandleInsertArr(idx: number) {
  info.value?.weekday_arr.splice(idx + 1, 0, { id: 0, job: "", student_ids: [[], [], [], [], []] });
}

function HandleEditArr(idx: number) {
  $q.dialog({
    component: EditWeekdayArr,
    componentProps: { idx },
  });
}
</script>

<template>
  <q-btn icon="add" outline @click="HandleInsertArr(-1)">
    添加工作日安排
  </q-btn>
  <q-markup-table separator="cell" flat min-w-160 justify-center bg-transparent>
    <thead font-bold>
      <tr>
        <th>职位</th>
        <th>今日安排</th>
        <th>操作</th>
      </tr>
    </thead>
    <tbody>
      <tr v-for="weekday_arr, idx in info?.weekday_arr" :key="weekday_arr.id">
        <td justify-center>
          <q-input v-model="weekday_arr.job" outlined dense />
        </td>

        <td>
          <div flex="~ gap-2">
            <div v-for="daily in DailyArrFromWeekday(weekday_arr)" :key="daily">
              {{ StudentDisplayString(info?.students.find(s => s.inclass_id === daily)) }}
            </div>
          </div>
        </td>

        <td>
          <div flex justify-center>
            <q-btn flat dense label="编辑" @click="HandleEditArr(idx)" />
            <q-btn flat dense label="删除" @click="HandleRemoveArr(idx)" />
            <q-btn flat dense label="插入" @click="HandleInsertArr(idx)" />
          </div>
        </td>
      </tr>
    </tbody>
  </q-markup-table>
</template>
