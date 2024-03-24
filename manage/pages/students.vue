<script setup lang="ts">
definePageMeta({
  name: "学生",
});

const { info } = storeToRefs(useClassStore());
</script>

<template>
  <div>
    <q-card bg-secondary>
      <q-card-section>
        <div grid="~ gap-2 justify-items-center" justify-center class="students-grid">
          <lazy-q-btn v-for="i in info?.students" :key="i.id" flat whitespace-nowrap p-1.5 text-4>
            <span>
              {{ i.inclass_id.toString().padStart(2, "0") }}
              <strong>{{ i.name }}</strong>
            </span>
          </lazy-q-btn>
        </div>
      </q-card-section>
    </q-card>
  </div>
</template>

<style scoped>
.students-grid {
  grid-template-columns: repeat(auto-fill, 4.5rem);
}
.q-badge {
  line-height: unset;
}
</style>
