<script setup lang="ts">
import AddStudentDialog from "../components/dialogs/AddStudentDialog.vue";
import EditStudentDialog from "~/manage/components/dialogs/EditStudentDialog.vue";
import type { Student } from "~/type";

definePageMeta({
  name: "学生",
});

const $q = useQuasar();

const { info } = storeToRefs(useClassStore());

function HandleStudentClicked(inclassId: number) {
  $q.dialog({
    component: EditStudentDialog,
    componentProps: {
      inclassId,
    },
  });
}

function HandleAddStudentClicked() {
  $q.dialog({
    component: AddStudentDialog,
  }).onOk((new_stu: Student) => {
    info.value?.students.push(new_stu);
  });
}
</script>

<template>
  <div>
    <q-card bg-secondary>
      <q-card-section text="center white">
        点击学生姓名进行更改，滑至下面添加学生
      </q-card-section>
      <q-card-section text-black>
        <div grid="~ gap-2 justify-items-center" justify-center class="students-grid">
          <lazy-q-btn
            v-for="stu in info?.students" :key="stu.id" flat dense whitespace-nowrap text-4
            @click="HandleStudentClicked(stu.inclass_id)"
          >
            {{ StudentDisplayString(stu) }}
          </lazy-q-btn>
          <q-btn
            icon="add"
            px-2 text-3 outline
            @click="HandleAddStudentClicked"
          >
            添加学生
          </q-btn>
        </div>
      </q-card-section>
    </q-card>
  </div>
</template>

<style scoped>
.students-grid {
  grid-template-columns: repeat(auto-fill, 5rem);
}
.q-badge {
  line-height: unset;
}
</style>
