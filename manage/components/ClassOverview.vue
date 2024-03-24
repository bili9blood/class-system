<script setup lang="ts">
const { info } = storeToRefs(useClassStore());
</script>

<template>
  <div grid="~ gap-4" text-5 class="overview-grid">
    <div>
      <q-badge>学生</q-badge>
      {{ info?.students.length }} 人
      <q-btn outline label="详情" to="/students" />
    </div>
    <div>
      <q-badge>课程</q-badge>
      每日 {{ info?.lessons.length }} 节
      <q-btn outline label="详情" to="/lessons" />
    </div>
    <div>
      <q-badge>安排</q-badge>
      &nbsp;
      <q-btn outline label="详情" to="/arrangements" />
    </div>
    <div>
      <q-badge>公告</q-badge>
      {{ info?.notices.length }} 条
      <q-btn outline label="详情" to="/notices_and_events" />
    </div>
    <div>
      <q-badge>事件</q-badge>
      {{ info?.events.length }} 个
      <q-btn outline label="详情" to="/notices_and_events" />
    </div>
  </div>
</template>

<style scoped>
.overview-grid {
  grid-template-columns: repeat(auto-fill, 14rem);
}
.q-badge {
  font-size: unset;
  line-height: unset;

  user-select: none;
  -moz-user-select: none;
  -webkit-user-select: none;
}
</style>
