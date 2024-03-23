<script setup lang="ts">
definePageMeta({ layout: "auth" });

interface LoginForm {
  class_id?: number;
  password?: string;
}

const $r = useRouter();
const $q = useQuasar();

const form_data = ref<LoginForm>({});
const classes = (await useFetch("/api/classes")).data?.value?.data;

async function HandleSubmit() {
  const { class_id, password } = form_data.value;
  if (!class_id || !password)
    return;

  try {
    await useClassStore().login(class_id, password);
  }
  catch (e) {
    $q.notify({
      message: `登录失败： ${e}`,
      color: "negative",
    });
    return;
  }
  $r.push("/");
}

onBeforeMount(() => {
  form_data.value = {};
});
</script>

<template>
  <q-card>
    <q-card-section>
      <div text="8 center dark" font-btt select-none>
        登录
      </div>
    </q-card-section>

    <q-card-section>
      <q-form class="q-gutter-md" @submit="HandleSubmit">
        <q-select
          v-model="form_data.class_id"
          filled
          label="选择班级"
          :options="classes?.map(({ id }) => id)"
          :option-label="(_id) => classes?.find(({ id }) => _id === id)?.name"
        />
        <q-input
          v-model="form_data.password"
          filled
          label="六位数字密码"
          type="password"
          mask="######"
          :rules="[
            (val) => val?.length === 6 || '请输入六位数字密码',
          ]"
        />
        <q-btn type="submit" color="primary">
          <i i-carbon-login />
          &nbsp;
          登录
        </q-btn>
      </q-form>
    </q-card-section>
  </q-card>
</template>
