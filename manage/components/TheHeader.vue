<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";

defineProps<{ nav: boolean }>();
</script>

<template>
  <QHeader
    height-hint="98"
    elevated
    text-primary-content
  >
    <QToolbar>
      <QToolbarTitle select-none>
        <q-avatar square>
          <img :src="IconIco" :draggable="false">
        </q-avatar>
        &nbsp;
        <span font-btt select-text text-6>{{ appName }}</span>
      </QToolbarTitle>

      <QTabs v-if="$props.nav" align="right" hidden sm:block>
        <QRouteTab to="/">
          主页
        </QRouteTab>
        <QRouteTab to="/students">
          学生
        </QRouteTab>
        <QRouteTab to="/lessons">
          课程
        </QRouteTab>
        <QRouteTab to="/arrangements">
          安排
        </QRouteTab>
        <QRouteTab to="/noticesAndEvents">
          公告·事件
        </QRouteTab>
      </QTabs>
    </QToolbar>
  </QHeader>
</template>
