<script setup lang="ts">
import { app_name } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

defineProps<{ nav: boolean;title?: string }>();
defineSlots<{ tabs?: () => any }>();

const $r = useRouter();
const $q = useQuasar();

const routes = $r.getRoutes().filter(r => r.meta.name).sort(
  (lhs, rhs) =>
    lhs.meta.name === "主页"
      ? -1
      : rhs.meta.name === "主页"
        ? 1
        : lhs.meta.name!.localeCompare(rhs.meta.name!),
);

const tab = ref("/");

watch(tab, () => {
  if (tab.value === "logout")
    Logout();
});

function Logout() {
  const { class_id, password, logined } = storeToRefs(useClassStore());
  class_id.value = 0;
  password.value = "";
  logined.value = false;
  $q.notify({
    message: "已退出登录",
    color: "positive",
  });
}

tab.value = $r.currentRoute.value.path;
</script>

<template>
  <q-header
    height-hint="98"
    elevated
    text-dark
  >
    <q-toolbar>
      <q-toolbar-title select-none>
        <q-avatar square>
          <img :src="IconIco" :draggable="false">
        </q-avatar>
        &nbsp;
        <span font-btt select-text text-6>{{ $props.title ?? app_name }}</span>
      </q-toolbar-title>

      <q-tabs v-if="$props.nav && !$slots.tabs" v-model="tab" align="right" hidden sm:block>
        <q-route-tab
          v-for="route in routes"
          :key="route.path" :to="route.path" :name="route.path"
        >
          {{ route.meta.name }}
        </q-route-tab>

        <q-separator vertical />

        <q-route-tab to="/docs">
          使用文档
        </q-route-tab>
        <q-tab name="logout">
          退出登录
        </q-tab>
      </q-tabs>
      <template v-else>
        <slot name="tabs" />
      </template>

      <q-btn v-if="$props.nav" flat icon="menu" round flex sm:hidden>
        <q-menu auto-close>
          <q-list>
            <q-item v-for="route in routes" :key="route.path" clickable :to="route.path">
              {{ route.meta.name }}
            </q-item>

            <q-separator />
            <q-item clickable @click="Logout">
              退出登录
            </q-item>
          </q-list>
        </q-menu>
      </q-btn>
    </q-toolbar>
  </q-header>
</template>

<style scoped>
.q-header {
  background: linear-gradient(90deg, var(--q-primary) 0%, #01fced 100%);
}
</style>
