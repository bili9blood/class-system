<script setup lang="ts">
import type { Student } from "~/type";

defineEmits([...useDialogPluginComponent.emits]);

const { dialogRef, onDialogHide, onDialogOK, onDialogCancel } = useDialogPluginComponent();
const { info } = storeToRefs(useClassStore());

const student = ref({ id: 0, inclass_id: "", name: "" });

function HandleSubmit() {
  onDialogOK({
    ...student.value,
    inclass_id: Number.parseInt(student.value.inclass_id),
  });
}
</script>

<template>
  <q-dialog ref="dialogRef" persistent @hide="onDialogHide">
    <q-card max-w-80vh w-80>
      <q-card-section text="6 center">
        <q-icon name="add" />
        添加学生
      </q-card-section>
      <q-card-section>
        <q-form class="q-gutter-md" @submit="HandleSubmit">
          <q-input
            v-model="student.inclass_id"
            label="学号"
            :rules="[
              (val) => val > 0 || '请输入大于 0 的学号',
              (val) => !info?.students.find((s) => s.inclass_id === Number.parseInt(val)) || '该学号已存在',
            ]"
          />
          <q-input
            v-model="student.name"
            label="姓名"
            :rules="[
              (val) => !!val || '请输入姓名',
            ]"
          />

          <q-btn @click="onDialogCancel">
            取消
          </q-btn>
          <q-btn type="submit" color="primary">
            确认
          </q-btn>
        </q-form>
      </q-card-section>
    </q-card>
  </q-dialog>
</template>
