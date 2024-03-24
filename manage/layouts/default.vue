<script setup lang="ts">
const bg_img_url = (await useFetch("/api/daily_image")).data;
const $r = useRouter();

const page_name = computed(() => $r.currentRoute.value.meta.name);
</script>

<template>
  <div h-screen w-screen>
    <div
      position-fixed hidden
      h-full w-full sm:block
    >
      <div :style="{ background: `url(${bg_img_url?.data})` }" class="bg-img" :draggable="false" object-cover />
    </div>

    <q-layout h-full>
      <the-header nav />

      <q-page-container h-full>
        <div h-full w-full flex items-center justify-center>
          <div sm:w="65%" flex-2 min-h-full w-full overflow-auto bg-white px-10 py-6 sm:px-4>
            <div text="center 8" font-btt mb-2>
              {{ page_name }}
            </div>
            <slot />
            <br select-none>
            <q-separator />
            <page-footer />
          </div>
        </div>
      </q-page-container>

      <TheFooter />
    </q-layout>
  </div>
</template>

<style scoped>
.bg-img {
  z-index: -1;
  filter: brightness(50%) blur(5px);
  background-size: 100%;
  background-repeat: no-repeat;
  background-position: center;
  width: 120%;
  height: 120%;
  position: relative;
  left: -10%;
  top: -10%;
  padding: 10%;
}
</style>
