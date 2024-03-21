<script setup lang="ts">
import { app_name } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

useHead({
  title: app_name,
  link: [{ rel: "icon", href: IconIco, sizes: "any" }],
});

const $r = useRouter();

const { logined } = storeToRefs(useClassStore());

watch(logined, () => {
  if (logined.value === false)
    $r.push("/auth/login");
  else if (logined.value === true)
    $r.push("/");
});
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
</style>
