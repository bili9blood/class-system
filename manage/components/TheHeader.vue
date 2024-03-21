<script setup lang="ts">
import { app_name } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

defineProps<{ tabs: boolean }>();

const $q = useQuasar();

// const { class_id } = storeToRefs(useClassStore());
// const classes = (await useFetch("/api/classes")).data;
// const class_name = computed(() => classes?.value?.data.find(c => c.id === class_id.value)?.name);

const tab = ref("/");

watch(tab, () => {
  if (tab.value === "logout") {
    const { class_id, password, logined } = storeToRefs(useClassStore());
    class_id.value = 0;
    password.value = "";
    logined.value = false;
    $q.notify({
      message: "已退出登录",
      color: "positive",
    });
  }
});
</script>

<template>
  <q-header
    height-hint="98"
    elevated
    text-primary-content
  >
    <q-toolbar>
      <q-toolbar-title select-none>
        <q-avatar square>
          <img :src="IconIco" :draggable="false">
        </q-avatar>
        &nbsp;
        <span font-btt select-text text-6>{{ app_name }}</span>
      </q-toolbar-title>

      <q-tabs v-if="$props.tabs" v-model="tab" align="right" hidden sm:block>
        <q-route-tab to="/">
          主页
        </q-route-tab>
        <q-route-tab to="/students">
          学生
        </q-route-tab>
        <q-route-tab to="/lessons">
          课程
        </q-route-tab>
        <q-route-tab to="/arrangements">
          安排
        </q-route-tab>
        <q-route-tab to="/notices_and_events">
          公告·事件
        </q-route-tab>
        <q-separator vertical />
        <q-tab name="logout">
          退出登录
        </q-tab>
      </q-tabs>
    </q-toolbar>
  </q-header>
</template>
