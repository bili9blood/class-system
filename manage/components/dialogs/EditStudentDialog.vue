<script setup lang="ts">
import type { Student } from "~/type";

const props = defineProps<{ inclassId: number }>();
defineEmits([...useDialogPluginComponent.emits]);

const $q = useQuasar();

const { dialogRef, onDialogHide, onDialogOK, onDialogCancel } = useDialogPluginComponent();
const { info } = storeToRefs(useClassStore());

const student = computed(() => info.value?.students.find(s => s.inclass_id === props.inclassId));
const editing = ref<Partial<Omit<Student, "id">>>(useCloned(student.value ?? {}).cloned.value);

function HandleRemove() {
  $q.dialog({
    title: "确认删除此学生？",
    cancel: true,
    persistent: true,
  }).onOk(() => {
    if (student.value)
      info.value?.students.splice(info.value?.students.indexOf(student.value), 1);
    onDialogOK();
  });
}

function HandleSubmit() {
  if (student.value && editing.value.name)
    student.value.name = editing.value.name;

  onDialogOK();
}
</script>

<template>
  <q-dialog ref="dialogRef" persistent @hide="onDialogHide">
    <q-card max-w-80vh w-80>
      <q-card-section text="6 center">
        <q-icon name="edit" />
        编辑学生
      </q-card-section>
      <q-card-section>
        <q-form class="q-gutter-md" @submit="HandleSubmit">
          <q-input v-model="editing.inclass_id" label="学号（仅供查看，不可编辑）" disable />
          <q-input v-model="editing.name" label="姓名" />

          <div flex="~ gap-2" justify-end>
            <q-btn @click="onDialogCancel">
              取消
            </q-btn>
            <q-btn color="negative" @click="HandleRemove">
              删除
            </q-btn>
            <q-btn type="submit" color="primary">
              确认
            </q-btn>
          </div>
        </q-form>
      </q-card-section>
    </q-card>
  </q-dialog>
</template>
