<script setup lang="ts">
import { app_name } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

const $r = useRouter();

const page_name = computed(() => $r.currentRoute.value.meta.name);

const { logined } = storeToRefs(useClassStore());

useHead({
  title: computed(() => `${app_name} | ${page_name.value}`),
  link: [{ rel: "icon", href: IconIco, sizes: "any" }],
});

watch(logined, () => {
  if (logined.value === false)
    $r.push("/auth/login");
  else if (logined.value === true)
    $r.push("/");
}, { immediate: true });
</script>

<template>
  <NuxtLayout>
    <NuxtPage />
  </NuxtLayout>
</template>

<style>
html,
body,
#__nuxt {
  height: 100vh;
  margin: 0;
  padding: 0;
}
.q-card__section {
  padding: 0.5rem !important;
}
</style>
