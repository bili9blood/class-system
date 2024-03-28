<script setup lang="ts">
const props = defineProps<{ idx: number }>();
defineEmits([...useDialogPluginComponent.emits]);

const { dialogRef, onDialogHide, onDialogOK } = useDialogPluginComponent();
const { info } = storeToRefs(useClassStore());

const arr = computed(() => info.value?.weekday_arr[props.idx]);
const weekday_map = ["周一", "周二", "周三", "周四", "周五"];

function HandleSubmit() {
  onDialogOK();
}
</script>

<template>
  <q-dialog ref="dialogRef" persistent @hide="onDialogHide">
    <q-card max-w-80vh w-160>
      <q-card-section text="6 center">
        <q-icon name="edit" />
        编辑安排 | {{ arr?.job }}
      </q-card-section>
      <q-card-section>
        <q-form class="q-gutter-md" @submit="HandleSubmit">
          <div v-for="ids, wd in arr?.student_ids" :key="ids.toString()">
            <span font-bold>{{ weekday_map[wd] }}&nbsp;</span>
            <div inline-flex="~" flex-wrap>
              <q-badge
                v-for="id, idx in ids"
                :key="id" m-0.5
                color="primary"
              >
                <q-select
                  v-model="ids[idx]"
                  :options="info?.students.map((s) => s.inclass_id)"
                  :option-label="(id) => StudentDisplayString(info?.students.find((s) => s.inclass_id === id))"
                  dense flat bg-transparent
                />
                <q-btn icon="close" flat dense round @click="ids.splice(idx, 1)" />
              </q-badge>
              <q-btn icon="add" dense outline @click="ids.push(0)" />
            </div>
          </div>

          <div flex="~ gap-2" justify-end>
            <q-btn type="submit" color="primary">
              确认
            </q-btn>
          </div>
        </q-form>
      </q-card-section>
    </q-card>
  </q-dialog>
</template>
