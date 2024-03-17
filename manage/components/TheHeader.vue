<script setup lang="ts">
import { appName } from "~/constants";
import IconIco from "~/resources/images/icon.ico";
</script>

<template>
  <QHeader
    height-hint="98"
    elevated
    text-primary-content
  >
    <QToolbar>
      <QToolbarTitle>
        <q-avatar square>
          <img :src="IconIco">
        </q-avatar>
        {{ appName }}
      </QToolbarTitle>

      <QTabs align="right" hidden sm:block>
        <QRouteTab to="/">
          主页
        </QRouteTab>
        <QRouteTab to="/students">
          学生
        </QRouteTab>
      </QTabs>
    </QToolbar>
  </QHeader>
</template>
