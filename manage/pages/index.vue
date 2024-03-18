<script setup lang="ts">
const hourNow = moment().hour();
const timeType = hourNow < 11 ? "morning" : hourNow < 13 ? "noon" : hourNow < 18 ? "afternoon" : "evening";
const welcomeBgColor = ({
  morning: "bg-yellow-500",
  noon: "bg-orange-500",
  afternoon: "bg-red-500",
  evening: "bg-purple-500",
} as const)[timeType];
const welcomeMsg = ({ morning: "早上好", noon: "中午好", afternoon: "下午好", evening: "晚上好" } as const)[timeType];
</script>

<template>
  <div :class="`${welcomeBgColor}`" rounded-4 px-1.5>
    <p font-btt select-none text-10>
      {{ welcomeMsg }}，欢迎使用班级系统管理端。
    </p>
  </div>
</template>
