<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

defineProps<{ nav: boolean }>();
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
        <span font-btt select-text text-6>{{ appName }}</span>
      </q-toolbar-title>

      <q-tabs v-if="$props.nav" align="right" hidden sm:block>
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
      </q-tabs>
      <q-btn></q-btn>
    </q-toolbar>
  </q-header>
</template>
