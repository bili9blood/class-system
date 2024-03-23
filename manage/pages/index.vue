<script setup lang="ts">
definePageMeta({
  name: "主页",
});

const hour_now = moment().hour();
const time_type = hour_now < 11 ? "morning" : hour_now < 13 ? "noon" : hour_now < 18 ? "afternoon" : "evening";
const welcome_bg_color = ({
  morning: "bg-yellow-500",
  noon: "bg-orange-500",
  afternoon: "bg-red-500",
  evening: "bg-purple-500",
} as const)[time_type];
const welcome_msg = ({ morning: "早上好", noon: "中午好", afternoon: "下午好", evening: "晚上好" } as const)[time_type];

const $r = useRouter();

if (await useClassStore().password === "")
  $r.push("/auth/login");
</script>

<template>
  <q-card :class="`${welcome_bg_color} q-gutter-sm`">
    <p font-btt select-none text-7 sm:text-9.5>
      {{ welcome_msg }}，欢迎使用班级系统管理端。
    </p>
  </q-card>
</template>
