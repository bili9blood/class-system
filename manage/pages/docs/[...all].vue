<script setup lang="ts">
definePageMeta({
  layout: "docs",
});

const $r = useRouter();

const { data: content } = await useAsyncData("content", () => queryContent($r.currentRoute.value.path).findOne());
</script>

<template>
  <content-renderer v-if="content?.body" :value="content" />
  <div v-else font-bold text="8 center">
    页面不存在！
  </div>
</template>
