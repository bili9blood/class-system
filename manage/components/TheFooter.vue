<script setup lang="ts">
const class_store = useClassStore();
</script>

<template>
  <q-footer
    height-hint="68"
    elevated
    bg-primary
    flex="~ gap-2"
    p-2 text-dark
  >
    <q-btn flat icon="save">
      保存
    </q-btn>
    <q-separator vertical />
    <q-btn flat icon="undo" @click="class_store.undo()">
      撤销
    </q-btn>
    <q-btn flat icon="redo" @click="class_store.redo()">
      重做
    </q-btn>
  </q-footer>
</template>
