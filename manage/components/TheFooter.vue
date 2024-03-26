<script setup lang="ts">
const class_store = useClassStore();

const saving = ref(false);

async function HandleSaveClicked() {
  saving.value = true;
  await class_store.putInfo();
  saving.value = false;
}
</script>

<template>
  <q-footer
    height-hint="68"
    elevated
    bg-primary
    flex="~ gap-2"
    p-2 text-dark
  >
    <q-btn flat icon="save" :disable="saving" @click="HandleSaveClicked">
      <template v-if="saving">
        <q-spinner-dots />
      </template>
      <template v-else>
        保存
      </template>
    </q-btn>
    <q-separator vertical />
    <q-btn flat icon="undo" @click="class_store.undo">
      撤销
    </q-btn>
    <q-btn flat icon="redo" @click="class_store.redo">
      重做
    </q-btn>
  </q-footer>
</template>
