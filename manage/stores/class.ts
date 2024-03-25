import { acceptHMRUpdate, defineStore } from "pinia";
import { Md5 } from "ts-md5";
import type { PiniaPluginContext } from "pinia";
import type { Info } from "~/type";

async function HandleAfterRestore(ctx: PiniaPluginContext) {
  const store = ctx.store as ReturnType<typeof useClassStore>;
  try {
    await store.login(store.class_id, store.password, true);
  }
  catch {
    storeToRefs(store).logined.value = false;
    return;
  }
  storeToRefs(store).logined.value = true;
}

export const useClassStore = defineStore("class", () => {
  const class_id = ref(0);
  const password = ref("");
  const logined = ref<boolean>();
  const info = ref<Info>();

  async function login(_class_id: number, _password: string, hashed: boolean = false) {
    const hashed_password = hashed ? _password : Md5.hashStr(_password + moment().format("YYYYMMDD")).toString();
    const result = await $fetch("/api/login", {
      body: {
        class_id: _class_id,
        password: hashed_password,
      },
      method: "POST",
    });

    if (result.code !== 200)
      throw result.message;

    class_id.value = _class_id;
    password.value = hashed_password;
    await fetchInfo();
  }

  async function fetchInfo() {
    const result = await $fetch("/api/info/get", {
      body: {
        class_id: class_id.value,
        long: false,
      },
      method: "POST",
    });

    info.value = result.data!;
  }

  async function putInfo() {
    const result = await $fetch("/api/info/put", {
      body: {
        info: info.value,
        class_id: class_id.value,
        password: password.value,
      },
      method: "POST",
    });

    if (result.code === 401) {
      logined.value = false;
      return;
    }
    if (result.code !== 200) {
      Notify.create({
        message: `保存失败：${result.message}`,
        color: "negative",
      });
      return;
    }
    Notify.create({
      message: "保存成功",
      color: "positive",
    });
  }

  return {
    class_id,
    password,
    logined,
    info,

    login,
    fetchInfo,
    putInfo,
  };
}, {
  persist: {
    afterRestore: HandleAfterRestore,
    paths: ["class_id", "password"],
  },
  undo: {
    omit: ["class_id", "password", "logined"],
  },
});

if (import.meta.hot)
  import.meta.hot.accept(acceptHMRUpdate(useClassStore, import.meta.hot));
