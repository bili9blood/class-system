<script setup lang="ts">
import { app_name } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

const $r = useRouter();

const page_name = computed(() => $r.currentRoute.value.meta.name);

const { logined } = storeToRefs(useClassStore());

useHead({
  title: computed(() => page_name.value ? `${app_name} | ${page_name.value}` : app_name),
  link: [{ rel: "icon", href: IconIco, sizes: "any" }],
});

watch(logined, () => {
  if (logined.value === false)
    $r.push("/auth/login");
  else if (logined.value === true && $r.currentRoute.value.path === "/auth/login")
    $r.push("/");
}, { immediate: true });
</script>

<template>
  <NuxtLayout text-dark>
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
.q-table th {
  font-size: unset;
  font-weight: unset;
}
</style>
